#include <random>
#include <UnitTest++/UnitTest++.h>

#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"

#include "unit_test_util.h"
#include "path_verify.h"

using ece297test::relative_error;
using ece297test::path_is_legal;


SUITE(inter_inter_simple_path_func_legality_public) {
struct MapFixture {
    MapFixture() {
        rng = std::minstd_rand(4);
        rand_intersection = std::uniform_int_distribution<IntersectionIdx>(0, getNumIntersections()-1);
        rand_street = std::uniform_int_distribution<StreetIdx>(1, getNumStreets()-1);
        rand_segment = std::uniform_int_distribution<StreetSegmentIdx>(0, getNumStreetSegments()-1);
        rand_poi = std::uniform_int_distribution<POIIdx>(0, getNumPointsOfInterest()-1);
        rand_lat = std::uniform_real_distribution<double>(46.650653839, 46.711387634);
        rand_lon = std::uniform_real_distribution<double>(7.800767422, 7.915423393);
        rand_turn_penalty = std::uniform_real_distribution<double>(0., 30.);
        rand_walking_speed = std::uniform_real_distribution<double>(0.8, 5);
        rand_walking_time_limit = std::uniform_real_distribution<double>(0.0, 300);
    }

    std::minstd_rand rng;
    std::uniform_int_distribution<IntersectionIdx> rand_intersection;
    std::uniform_int_distribution<StreetSegmentIdx> rand_street;
    std::uniform_int_distribution<StreetSegmentIdx> rand_segment;
    std::uniform_int_distribution<POIIdx> rand_poi;
    std::uniform_real_distribution<double> rand_lat;
    std::uniform_real_distribution<double> rand_lon;
    std::uniform_real_distribution<double> rand_turn_penalty;
    std::uniform_real_distribution<double> rand_walking_speed;
    std::uniform_real_distribution<double> rand_walking_time_limit;
};
    TEST(findPathBetweenIntersections_simple_legality) {
        std::vector<StreetSegmentIdx> path;

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(109, 110));
        CHECK(path_is_legal(109, 110, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(167, 188));
        CHECK(path_is_legal(167, 188, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(94, 297));
        CHECK(path_is_legal(94, 297, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(323, 40));
        CHECK(path_is_legal(323, 40, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(622, 620));
        CHECK(path_is_legal(622, 620, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(643, 642));
        CHECK(path_is_legal(643, 642, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(657, 658));
        CHECK(path_is_legal(657, 658, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(743, 678));
        CHECK(path_is_legal(743, 678, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(682, 749));
        CHECK(path_is_legal(682, 749, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(324, 326));
        CHECK(path_is_legal(324, 326, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(850, 848));
        CHECK(path_is_legal(850, 848, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(885, 903));
        CHECK(path_is_legal(885, 903, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(972, 1187));
        CHECK(path_is_legal(972, 1187, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(489, 1035));
        CHECK(path_is_legal(489, 1035, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1331, 460));
        CHECK(path_is_legal(1331, 460, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(579, 798));
        CHECK(path_is_legal(579, 798, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1214, 1425));
        CHECK(path_is_legal(1214, 1425, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1188, 975));
        CHECK(path_is_legal(1188, 975, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1459, 1458));
        CHECK(path_is_legal(1459, 1458, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1453, 1732));
        CHECK(path_is_legal(1453, 1732, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1513, 1503));
        CHECK(path_is_legal(1513, 1503, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(945, 41));
        CHECK(path_is_legal(945, 41, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1589, 1588));
        CHECK(path_is_legal(1589, 1588, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1599, 1602));
        CHECK(path_is_legal(1599, 1602, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1641, 952));
        CHECK(path_is_legal(1641, 952, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(0, 1105));
        CHECK(path_is_legal(0, 1105, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1292, 284));
        CHECK(path_is_legal(1292, 284, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1721, 1722));
        CHECK(path_is_legal(1721, 1722, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(150, 295));
        CHECK(path_is_legal(150, 295, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(1798, 1800));
        CHECK(path_is_legal(1798, 1800, path));

    } //findPathBetweenIntersections_simple_legality

} //inter_inter_simple_path_func_legality_public

