#include <UnitTest++/UnitTest++.h>
#include "unit_test_util.h"
#include "m1.h"

std::string map_dir = "/cad2/ece297s/public/maps/";

SUITE(M1_Public_Load_Maps) {
    TEST(load_saint_helena) {
        {
            UNITTEST_TIME_CONSTRAINT(3000);
            CHECK(loadMap(map_dir + "saint-helena.streets.bin"));
            ECE297_CHECK_EQUAL(420, getNumIntersections());
        }
        closeMap();
    }
    
    TEST(load_hamilton) {
        {
            UNITTEST_TIME_CONSTRAINT(3000);
            CHECK(loadMap(map_dir + "hamilton_canada.streets.bin"));
            ECE297_CHECK_EQUAL(21499, getNumIntersections());
        }
        closeMap();
    }

    TEST(load_moscow) {
        {
            UNITTEST_TIME_CONSTRAINT(10000);
            CHECK(loadMap(map_dir + "moscow_russia.streets.bin"));
            ECE297_CHECK_EQUAL(153448, getNumIntersections());
        }
        closeMap();
    }

    TEST(load_toronto) {
        {
            UNITTEST_TIME_CONSTRAINT(15000);
            CHECK(loadMap(map_dir + "toronto_canada.streets.bin"));
            ECE297_CHECK_EQUAL(151703, getNumIntersections());
        }
        closeMap();
    }

    TEST(load_newyork) {
        {
            UNITTEST_TIME_CONSTRAINT(20000);
            CHECK(loadMap(map_dir + "new-york_usa.streets.bin"));
            ECE297_CHECK_EQUAL(214437, getNumIntersections());
        }
        closeMap();
    }

    TEST(load_golden_horseshoe) {
        {
            UNITTEST_TIME_CONSTRAINT(20000);
            CHECK(loadMap(map_dir + "golden-horseshoe_canada.streets.bin"));
            ECE297_CHECK_EQUAL(240227, getNumIntersections());
        }
        closeMap();
    }

    TEST(load_invalid_map_path) {
        {
            UNITTEST_TIME_CONSTRAINT(3000);
            CHECK(!loadMap("/this/path/does/not/exist"));
        }
    }
}
