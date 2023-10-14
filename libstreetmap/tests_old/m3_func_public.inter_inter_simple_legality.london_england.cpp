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
        rand_lat = std::uniform_real_distribution<double>(51.280006409, 51.699996948);
        rand_lon = std::uniform_real_distribution<double>(-0.599989712, 0.419978589);
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

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(4082, 4078));
        CHECK(path_is_legal(4082, 4078, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(12655, 12656));
        CHECK(path_is_legal(12655, 12656, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(14603, 206371));
        CHECK(path_is_legal(14603, 206371, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(14685, 14686));
        CHECK(path_is_legal(14685, 14686, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(22, 18039));
        CHECK(path_is_legal(22, 18039, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(47989, 47990));
        CHECK(path_is_legal(47989, 47990, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(80633, 80632));
        CHECK(path_is_legal(80633, 80632, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(87126, 87125));
        CHECK(path_is_legal(87126, 87125, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(90134, 90133));
        CHECK(path_is_legal(90134, 90133, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(99384, 99392));
        CHECK(path_is_legal(99384, 99392, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(105890, 43579));
        CHECK(path_is_legal(105890, 43579, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(124175, 124174));
        CHECK(path_is_legal(124175, 124174, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(126296, 126295));
        CHECK(path_is_legal(126296, 126295, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(82337, 82332));
        CHECK(path_is_legal(82337, 82332, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(70270, 52570));
        CHECK(path_is_legal(70270, 52570, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(148592, 148470));
        CHECK(path_is_legal(148592, 148470, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(87809, 124938));
        CHECK(path_is_legal(87809, 124938, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(107359, 150944));
        CHECK(path_is_legal(107359, 150944, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(49002, 49004));
        CHECK(path_is_legal(49002, 49004, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(83200, 120947));
        CHECK(path_is_legal(83200, 120947, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(91598, 94027));
        CHECK(path_is_legal(91598, 94027, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(185177, 185184));
        CHECK(path_is_legal(185177, 185184, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(187157, 187160));
        CHECK(path_is_legal(187157, 187160, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(194107, 149996));
        CHECK(path_is_legal(194107, 149996, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(194157, 194164));
        CHECK(path_is_legal(194157, 194164, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(202178, 202176));
        CHECK(path_is_legal(202178, 202176, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(111831, 163037));
        CHECK(path_is_legal(111831, 163037, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(213724, 213720));
        CHECK(path_is_legal(213724, 213720, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(221820, 30038));
        CHECK(path_is_legal(221820, 30038, path));

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(111359, 111360));
        CHECK(path_is_legal(111359, 111360, path));

    } //findPathBetweenIntersections_simple_legality

} //inter_inter_simple_path_func_legality_public

