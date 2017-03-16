struct BoolSource {
    BoolSource ( std::string n, bool ( OI::*cb ) () )
    {
        name = n;
        callback = cb;
    }

    std::string name;
    bool ( OI::*callback ) ();
};

struct DoubleSource {
    DoubleSource ( std::string n, double ( OI::*cb ) () )
    {
        name = n;
        callback = cb;
    }

    std::string name;
    double ( OI::*callback ) ();
};

struct BoolDrivetrainOutput {
    BoolDrivetrainOutput ( std::string n, void ( Drivetrain::*cb ) ( bool ) )
    {
        name = n;
        callback = cb;
    }

    std::string name;
    void ( Drivetrain::*callback ) ( bool );
};

struct DoubleDrivetrainOutput {
    DoubleDrivetrainOutput ( std::string n, void ( Drivetrain::*cb ) ( double ) )
    {
        name = n;
        callback = cb;
    }

    std::string name;
    void ( Drivetrain::*callback ) ( double );
};

struct BoolGearBoxOutput {
    BoolGearBoxOutput ( std::string n, void ( GearBox::*cb ) ( bool ) )
    {
        name = n;
        callback = cb;
    }

    std::string name;
    void ( GearBox::*callback ) ( bool );
};

struct DoubleGearBoxOutput {
    DoubleGearBoxOutput ( std::string n, void ( GearBox::*cb ) ( double ) )
    {
        name = n;
        callback = cb;
    }

    std::string name;
    void ( GearBox::*callback ) ( double );
};
