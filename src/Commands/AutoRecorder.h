#ifndef AUTO_RECORDER_H
#define AUTO_RECORDER_H

#define AUTO_FILE "recordedAuto.json"

#include <json/json.hpp>
using json = nlohmann::json;

#include "../CommandBase.h"
#include "AutoRecorderStructs.h"

class AutoRecorder: public CommandBase
{
    public:
        AutoRecorder ( bool r );
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End() override;
        void Interrupted() override;
    private:
        json recordedData;
        int currentFrame;
        bool recording;

        void AddSource ( std::string name, bool ( OI::*callback ) () );
        void AddSource ( std::string name, double ( OI::*callback ) () );

        void AddOutput ( std::string name, void ( Drivetrain::*callback ) ( bool ) );
        void AddOutput ( std::string name, void ( GearBox::*callback ) ( bool ) );
        void AddOutput ( std::string name, void ( Drivetrain::*callback ) ( double ) );
        void AddOutput ( std::string name, void ( GearBox::*callback ) ( double ) );

        std::vector<BoolSource>* boolSources;
        std::vector<DoubleSource>* doubleSources;

        std::vector<BoolDrivetrainOutput>* boolDrivetrainOutputs;
        std::vector<DoubleDrivetrainOutput>* doubleDrivetrainOutputs;
        std::vector<BoolGearBoxOutput>* boolGearBoxOutputs;
        std::vector<DoubleGearBoxOutput>* doubleGearBoxOutputs;
};

#endif  // AUTO_RECORDER_H
