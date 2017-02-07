#ifndef CARDINAL_DASH_DASHBOARD_H
#define CARDINAL_DASH_DASHBOARD_H

#include <VictorSP.h>

#include <json/json.hpp>
using json = nlohmann::json;

namespace CardinalDash
{

    class Dashboard
    {
        public:
            static void Init();

            // OVERLOADDDDD
            static void Subscribe ( std::string name, bool ( *callback ) () );
            static void Subscribe ( std::string name, char ( *callback ) () );
            static void Subscribe ( std::string name, float ( *callback ) () );
            static void Subscribe ( std::string name, double ( *callback ) () );
            static void Subscribe ( std::string name, int ( *callback ) () );

            static void Subscribe ( std::string name, bool ( *callback ) ( void* instance ),
                                    void* object );
            static void Subscribe ( std::string name, char ( *callback ) ( void* instance ),
                                    void* object );
            static void Subscribe ( std::string name, float ( *callback ) ( void* instance ),
                                    void* object );
            static void Subscribe ( std::string name, double ( *callback ) ( void* instance ),
                                    void* object );
            static void Subscribe ( std::string name, int ( *callback ) ( void* instance ),
                                    void* object );

            static void PushValues();
        private:
            enum DataType {
                BOOL, CHAR, FLOAT, DOUBLE, INT
            };

            struct DashboardValue {
                DashboardValue ( std::string n, DataType t, void* cb, void* obj ) {
                    name = n;
                    type = t;
                    callback = cb;
                    object = obj;
                }

                std::string name;
                DataType type;
                void* callback;
                void* object;
            };

            static void SubscribeToValue ( std::string name, DataType type, void* callback,
                                           void* object );

            static void GetValue ( DashboardValue value, json& data );

            static std::vector<DashboardValue>* subscribedValues;
    };

};

#endif // CARDINAL_DASH_DASHBOARD_H
