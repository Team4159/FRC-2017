#include "CardinalDash/Dashboard.h"

#include "PDP.h"

namespace CardinalDash {

    std::vector<Dashboard::DashboardValue> *Dashboard::subscribedValues = new std::vector<Dashboard::DashboardValue>();
    std::vector<Dashboard::DashboardMemberValue> *Dashboard::subscribedMemberValues = new std::vector<Dashboard::DashboardMemberValue>();

    void Dashboard::Init()
    {
        PDP::Init();
    }

    void Dashboard::PushValues()
    {
        // TODO: Send values using web sockets
        // Should use all subscribed vectors, with casting to callbacks with some magic
    }

    // It's pretty much the same thing for the rest of the file...

    void Dashboard::Subscribe(std::string name, bool (*callback)())
    {
        Dashboard::DashboardValue value = Dashboard::DashboardValue(name, Dashboard::DataType::BOOL, (void*)callback);
        subscribedValues->push_back(value);
    }

    void Dashboard::Subscribe(std::string name, char (*callback)())
    {
        Dashboard::DashboardValue value = Dashboard::DashboardValue(name, Dashboard::DataType::CHAR, (void*)callback);
        subscribedValues->push_back(value);
    }

    void Dashboard::Subscribe(std::string name, float (*callback)())
    {
        Dashboard::DashboardValue value = Dashboard::DashboardValue(name, Dashboard::DataType::FLOAT, (void*)callback);
        subscribedValues->push_back(value);
    }

    void Dashboard::Subscribe(std::string name, double (*callback)())
    {
        Dashboard::DashboardValue value = Dashboard::DashboardValue(name, Dashboard::DataType::DOUBLE, (void*)callback);
        subscribedValues->push_back(value);
    }

    void Dashboard::Subscribe(std::string name, int (*callback)())
    {
        Dashboard::DashboardValue value = Dashboard::DashboardValue(name, Dashboard::DataType::INT, (void*)callback);
        subscribedValues->push_back(value);
    }

    // Nothing to see here...

    void Dashboard::Subscribe(std::string name, bool (*callback)(void* instance), void* object)
    {
        Dashboard::DashboardMemberValue value = Dashboard::DashboardMemberValue(name, Dashboard::DataType::BOOL, (void*)callback, object);
        subscribedMemberValues->push_back(value);
    }

    void Dashboard::Subscribe(std::string name, char (*callback)(void* instance), void* object)
    {
        Dashboard::DashboardMemberValue value = Dashboard::DashboardMemberValue(name, Dashboard::DataType::CHAR, (void*)callback, object);
        subscribedMemberValues->push_back(value);
    }

    void Dashboard::Subscribe(std::string name, float (*callback)(void* instance), void* object)
    {
        Dashboard::DashboardMemberValue value = Dashboard::DashboardMemberValue(name, Dashboard::DataType::FLOAT, (void*)callback, object);
        subscribedMemberValues->push_back(value);
    }

    void Dashboard::Subscribe(std::string name, double (*callback)(void* instance), void* object)
    {
        Dashboard::DashboardMemberValue value = Dashboard::DashboardMemberValue(name, Dashboard::DataType::DOUBLE, (void*)callback, object);
        subscribedMemberValues->push_back(value);
    }

    void Dashboard::Subscribe(std::string name, int (*callback)(void* instance), void* object)
    {
        Dashboard::DashboardMemberValue value = Dashboard::DashboardMemberValue(name, Dashboard::DataType::INT, (void*)callback, object);
        subscribedMemberValues->push_back(value);
    }

    // Well aren't we nosy?
}
