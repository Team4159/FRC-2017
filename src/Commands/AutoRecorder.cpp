#include "AutoRecorder.h"

#include <json/json.hpp>
using json = nlohmann::json;

#include <fstream>
#include <Preferences.h>
// #include <algorithm>

#include "CommandBase.h"

AutoRecorder::AutoRecorder ( bool r = false ) : CommandBase ( "AutoRecorder" )
{
    recording = r;

    if ( recording ) {
        boolSources = new std::vector<BoolSource>();
        doubleSources = new std::vector<DoubleSource>();

        AddSource ( "leftStick", &OI::GetLeftJoystick );
        AddSource ( "rightStick", &OI::GetRightJoystick );
        AddSource ( "shifter", &OI::GetShift );
        AddSource ( "intake", &OI::GetIntake );
        AddSource ( "lifter", &OI::GetLifter );
        AddSource ( "gripper", &OI::GetGripper );
    } else {
        boolDrivetrainOutputs = new std::vector<BoolDrivetrainOutput>();
        doubleDrivetrainOutputs = new std::vector<DoubleDrivetrainOutput>();
        boolGearBoxOutputs = new std::vector<BoolGearBoxOutput>();
        doubleGearBoxOutputs = new std::vector<DoubleGearBoxOutput>();

        AddOutput ( "leftStick", &Drivetrain::SetLeftRaw );
        AddOutput ( "rightStick", &Drivetrain::SetRightRaw );
        AddOutput ( "shifter", &Drivetrain::Shift );
        AddOutput ( "intake", &GearBox::Set );
        AddOutput ( "lifter", &GearBox::SetLifter );
        AddOutput ( "gripper", &GearBox::SetGripper );
    }
}

void AutoRecorder::Initialize()
{
    CommandBase::drivetrain->DisablePID();

    if ( recording ) {
        recordedData = json::object();
    } else {
        std::string in = frc::Preferences::GetInstance()->GetString ( "AutoRecorder" );
        // Alright so as it turns out, frc::Preferences likes to convert doublequotes
        // to backslashes so let's convert it back so the json doesn't break.
        std::replace ( in.begin(), in.end(), '\\', '\"' );
        recordedData = json::parse ( in );
    }

    currentFrame = 0;
}

//TODO: less shitty templates for structs

void AutoRecorder::Execute()
{
    if ( recording ) {
        for ( BoolSource source : *boolSources ) {
            recordedData["frames"][currentFrame][source.name] = ( ( CommandBase::oi.get() )->*source.callback ) ();
        }

        for ( DoubleSource source : *doubleSources ) {
            recordedData["frames"][currentFrame][source.name] = ( ( CommandBase::oi.get() )->*source.callback ) ();
        }
    } else {
        for ( DoubleDrivetrainOutput out : *doubleDrivetrainOutputs ) {
            ( ( CommandBase::drivetrain.get() )->*out.callback ) ( recordedData["frames"][currentFrame][out.name] );
        }
        for ( BoolDrivetrainOutput out : *boolDrivetrainOutputs ) {
            ( ( CommandBase::drivetrain.get() )->*out.callback ) ( recordedData["frames"][currentFrame][out.name] );
        }

        for ( DoubleGearBoxOutput out : *doubleGearBoxOutputs ) {
            ( ( CommandBase::gearBox.get() )->*out.callback ) ( recordedData["frames"][currentFrame][out.name] );
        }
        for ( BoolGearBoxOutput out : *boolGearBoxOutputs ) {
            ( ( CommandBase::gearBox.get() )->*out.callback ) ( recordedData["frames"][currentFrame][out.name] );
        }
    }

    currentFrame++;
}

bool AutoRecorder::IsFinished()
{
    if ( !recording ) {
        return currentFrame >= recordedData["total"];
    }
    return false;
}

void AutoRecorder::End()
{
    if ( recording ) {
        recordedData["total"] = currentFrame;
        std::cout << recordedData.dump() << '\n';
        frc::Preferences::GetInstance()->PutString ( "AutoRecorder", recordedData.dump() );
    } else {
        CommandBase::drivetrain->SetRaw ( 0, 0 );
        CommandBase::gearBox->Set ( 0 );
    }
    CommandBase::drivetrain->DisablePID();
}

void AutoRecorder::Interrupted()
{
    End();
}

void AutoRecorder::AddSource ( std::string name, bool ( OI::*callback ) () )
{
    BoolSource value = BoolSource ( name, callback );
    boolSources->push_back ( value );
}

void AutoRecorder::AddSource ( std::string name, double ( OI::*callback ) () )
{
    DoubleSource value = DoubleSource ( name, callback );
    doubleSources->push_back ( value );
}

void AutoRecorder::AddOutput ( std::string name, void ( Drivetrain::*callback ) ( bool ) )
{
    BoolDrivetrainOutput value = BoolDrivetrainOutput ( name, callback );
    boolDrivetrainOutputs->push_back ( value );
}

void AutoRecorder::AddOutput ( std::string name, void ( GearBox::*callback ) ( bool ) )
{
    BoolGearBoxOutput value = BoolGearBoxOutput ( name, callback );
    boolGearBoxOutputs->push_back ( value );
}

void AutoRecorder::AddOutput ( std::string name, void ( Drivetrain::*callback ) ( double ) )
{
    DoubleDrivetrainOutput value = DoubleDrivetrainOutput ( name, callback );
    doubleDrivetrainOutputs->push_back ( value );
}

void AutoRecorder::AddOutput ( std::string name, void ( GearBox::*callback ) ( double ) )
{
    DoubleGearBoxOutput value = DoubleGearBoxOutput ( name, callback );
    doubleGearBoxOutputs->push_back ( value );
}
