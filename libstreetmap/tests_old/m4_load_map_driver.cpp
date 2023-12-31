#include <string>
#include <UnitTest++/UnitTest++.h>

#include "unit_test_util.h"

#include "m1.h"

namespace ezgl {
	extern void set_disable_event_loop (bool new_setting);
}

int main(int argc, char** argv) {
    //Disable interactive graphics
    ezgl::set_disable_event_loop(true);


    //Run the unit tests
    int num_failures = UnitTest::RunAllTests();

    return num_failures;
}

TEST(LoadMapToronto) {
    std::string map_name = "/cad2/ece297s/public/maps/toronto_canada.streets.bin";
    bool load_success = false;
    {
        ECE297_TIME_CONSTRAINT(20000);

        load_success = loadMap(map_name);

    }
    CHECK(load_success);

    closeMap();
}

TEST(LoadMapNewYork) {
    std::string map_name = "/cad2/ece297s/public/maps/new-york_usa.streets.bin";
    bool load_success = false;
    {
        ECE297_TIME_CONSTRAINT(30000);

        load_success = loadMap(map_name);

    }
    CHECK(load_success);

    closeMap();
}

TEST(LoadMapLondonEngland) {
    std::string map_name = "/cad2/ece297s/public/maps/london_england.streets.bin";
    bool load_success = false;
    {
        ECE297_TIME_CONSTRAINT(60000);

        load_success = loadMap(map_name);

    }
    CHECK(load_success);

    closeMap();
}
