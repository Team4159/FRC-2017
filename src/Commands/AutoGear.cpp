#include "AutoGear.h"
#include "../VisionMethods.h"
#include "../RobotMap.h"
AutoGear::AutoGear() {
    Requires(drivetrain.get());
    Requires(gearBox.get());
    Requires(gyro.get());
    oldTime = 0.0;
    currentX = 0.0;
    a = 1.0;
    b = 1.0;
    c = 1.0;
    d = 1.0;
    e = 1.0;
    f = 1.0;
    m = 1.0;
    oldAngle = 1.0;
    oldSpeed = 0.0;
    pathlength = 1.0; //dummy values, will change
    radiansPerSec = 7.0;
    turnClockwise = false; //Whether to turn clockwise or counterclockwise
}


// Called just before this Command runs the first time

void AutoGear::Initialize() {
	//Figures out which of the contours seen by the camera. The ratio of width to height
	//of an actual vision target is 2:5.
    double bestratio = 99999.0;
    double secondbestratio = 99999.0;
    isGearing = true;
    cv::Point bestDist;       //The distance from the robot to the best vision target candidate
    cv::Point secondbestDist; //and second best vision target candidate respectively.
    int bestx = -1;          //The x-coordinate of the best vision target candidate
    int secondbestx = -1;    //and second best vision target candidate respectively.

    std::vector<std::vector<cv::Point>> contours = filteredContours(CAMERA_PORT); //Grabs the contours from the image

    for(int c=0; c<contours.size();c++) {
    	if(contourArea(contours[c]) > 700) { //The contours must be bigger than 700 pixels to be considered
    		cv::Rect rectangle = boundingRect(contours[c]); //Uses the bounding rectangle to get top-left and bottom-right coords
    		double rat = (rectangle.br().x-rectangle.tl().x)/(rectangle.tl().y-rectangle.br().y); //calculates ratio
    		if(abs(rat-0.4) < abs(bestratio-0.4)) {
    			secondbestratio = bestratio;
    			bestratio = rat;
    			secondbestDist = bestDist;  //If the ratio is the best so far, update the variables
    			bestDist = distFromContour(contours[c]);
    			secondbestx = bestx;
    			bestx = centerOfContour(contours[c]).x;
    		}
    		else if(abs(rat-0.4) < abs(secondbestratio-0.4)) {
    			secondbestratio = rat;      //If it's the second best, update the variables
    			secondbestDist = distFromContour(contours[c]);
    			secondbestx = centerOfContour(contours[c]).x;
    		}
    	}
    }

    if(bestx == -1 || secondbestx == -1) { //Stop the program if we can't find both vision targets.
    	isGearing = false;
    }

    /* At this point we know the distances from the robot to the two vision targets.
     * Now, we use the intersection of the circles to find the robot's location.
     * Note: All coordinates are in inches. The gear peg is at (0,0), and the vision
     * targets are at (-4.125, 0) and (4.125, 0) respectively (see the game manual.)
     */

    double robotx, roboty;
    if(bestx>secondbestx) {
    	robotx = (secondbestx*secondbestx-bestx*bestx)/16.5;
    	roboty = sqrt(secondbestx*secondbestx-(robotx+4.125)*(robotx+4.125));
    }
    else {
    	robotx = (bestx*bestx-secondbestx*secondbestx)/16.5;
    	roboty = sqrt(bestx*bestx-(robotx+4.125)*(robotx+4.125));
    }



    /* We switch to a different coordinate scheme for convenience. The robot starts at (0,0),
     * and the gear peg is at (a,b). Since this is just a translation of the old coordinate
     * system, we already know the values of a and b.
     */

    a = abs(robotx);
    b = abs(roboty);

    /* NOTE: If we are on the right side of the gear peg, we invert the x-direction of the
     * coordinate system. Everything else stays the same.
     */

    if(robotx>0) {turnClockwise = true;}

    m = atan(gyro->GetAngle());

    /* The robot's path has the form -ln(cos(cx+d))+f, where c, d, and f are constants.
     * I chose this path because then the robot's angle is changing at close to a constant rate.
     * The angle of the robot is given by the arctangent of the derivative of the robot's path,
     * so if the equation was -ln(cos(x)), the angle would just be x, so the rate of change of the angle
     * would just be 1, which is constant. Adding in the constants c, d, and f makes the robot's angle
     * change not quite linearly, but it is close to linear.
     *
     * Also, the derivative of -ln(cos(x)) approaches infinity as x approaches pi/2. We want the robot to eventually
     * be going straight with respect to the gear peg, so this is what we want.
     *
     * In this next section of code, we solve for c, d, and f. I couldn't do it by hand, so
     * we use binary search. I did a lot of algebra that I won't comment on here, ask me if
     * you have questions. (I don't expect you to recreate all I did in your head. If you can,
     * you have the right to call yourself the new Art Benjamin.)
     */

    double e = 2.7182818284590452353602874713526625;
    double left = 0.000001;
    double right = 1.0;
    double middle = (left+right)/2.0;
    double eval = pow(e,b) * (middle*cos(m*a*middle/(sqrt(1-middle*middle))) - sqrt(1-middle*middle) * sin(m*a*middle/(sqrt(1-middle*middle)))) - middle;
    for(int count=0;count<40;count++) {
    	if(eval*(pow(e,b) * (left*cos(m*a*left/(sqrt(1-left*left))) - sqrt(1-left*left) * sin(m*a*left/(sqrt(1-left*left)))) - left) > 0) {
    		left = middle;
    	}
    	else {
    		right = middle;
    	}
    	middle = (left+right)/2.0;
    	eval = pow(e,b) * (middle*cos(m*a*middle/(sqrt(1-middle*middle))) - sqrt(1-middle*middle) * (m*a*middle/(sqrt(1-middle*middle)))) - middle;
    }

    double f = log(middle);
    double d = acos(middle);
    double c = m*middle/sqrt(1-middle*middle);

    /* We want to figure out the total length of the robot's path. In general, that would be the
     * integral from 0 to a of sqrt(1+(dy/dx)^2) dx, so in this case it's the integral from 0 to
     * a of sqrt(1+c^2 * tan^2(cx+d)) dx. This integral is nasty, so I use the trapezoid approximation
     * with 10000 intervals to get an estimate.
     */

    double pathlength = sqrt(1 + c*c*tan(d)*tan(d)) + sqrt(1+c*c*tan(a*c+d)*tan(a*c+d));
    for(int count=1; count<10000; count++) {
    	pathlength += sqrt(1+count*count*tan(a*count/10000.0)*tan(a*count/10000.0));
    }
    pathlength /= 10000.0;

    oldAngle = atan(m);

    tim = Timer(); tim.Reset(); tim.Start();
}

// Called repeatedly when this Command is scheduled to run
void AutoGear::Execute() {
	double timetocompletion = 7.5; //The number of seconds it'll take for us to get to the gear peg
                                   //This is an estimate: please try different values during testing
								   //(This value is used to figure out how fast the robot should be going)



	/* We are now figuring out where the robot is on its path. We have this equation:
	 * integral from 0 to (current x-coord) of sqrt(1+c^2 * tan^2(cx+d)) dx is equal to
	 * (current time/timetocompletion) * pathlength. We move everything to the left hand side
	 * and again use binary search to figure out solutions.
	 */

	currentX += oldSpeed*acos(oldAngle)*(tim.Get()-oldTime);

/*

    double left = 0.0;
    double right = a;
    double middle = a/2.0;
    double eval = sqrt(1+c*c*tan(d+a*c/2)*tan(d+a*c/2))/2 - tim.Get()*pathlength/timetocompletion;
    double neweval;
    for(int count = 1; count < 10000; count++) {
    	eval += sqrt(1+c*c*tan(d+c*a*count/20000.0)*tan(d+c*a*count/20000.0));
    }
    for(int c=0;c<40;c++) {
    	if(eval < 0) {
    		left = middle;
    	}
    	else {
    		right = middle;
    	}
    	middle = (left+right)/2.0;
    	eval = sqrt(1+c*c*tan(d+middle*c)*tan(d+middle*c))/2 - tim.Get()*pathlength/timetocompletion;
        for(int count = 1; count < 10000; count++) {
        	eval += sqrt(1+c*c*tan(d+c*middle*count/10000.0)*tan(d+c*middle*count/10000.0));
        }
    }

*/
    /* We now have that the rate of change of angle is
     * the derivative of the arctangent of the derivative of the path equation, or
     * c*sec^2(c*middle+d)/(1+(c*tan(c*middle+d))^2)
     *
     * Note: "middle" is the current value of x.
     *
     * I'm not so sure how to finish this last step, or setting the motors. My
     * hypothesis is that the rate of change of the angle is directly proportional
     * to the difference between the left and right motor values, but I really don't
     * know. I'll write the last few lines based on that hypothesis, but if it's wrong
     * please let me know.
     */

    //Given that when the difference is 2, the angular speed is radiansPerSec,
    //to get the angular speed we want, call it A, we set the motors to 1.0 and
    //1 - 2A/radiansPerSec.

    if(turnClockwise) {
    	drivetrain->Set(1.0, 1.0-2*(c/((pow(cos(c*currentX+d),2)*(1+pow(c*tan(c*currentX+d),2)))))/radiansPerSec);
    }
    else {
    	drivetrain->Set(1.0-2*(c/((pow(cos(c*currentX+d),2)*(1+pow(c*tan(c*currentX+d),2)))))/radiansPerSec,1.0);
    }
    oldSpeed = pathlength * (1-(c/((pow(cos(c*currentX+d),2)*(1+pow(c*tan(c*currentX+d),2))))))/timetocompletion;
    oldTime = tim.Get();
    oldAngle = atan(c*tan(c*currentX+d));
}

// Make this return true when this Command no longer needs to run execute()
bool AutoGear::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AutoGear::End() {
	tim.Reset();
    gearBox->SetLifter(true);
    gearBox->SetGripper(false);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoGear::Interrupted() {
    tim.Reset();
}
