#include <random>
#include <UnitTest++/UnitTest++.h>

#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"

#include "unit_test_util.h"
#include "path_verify.h"

using ece297test::relative_error;
using ece297test::path_is_legal;


SUITE(inter_inter_simple_path_func_optimality_public) {
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
    TEST(findPathBetweenIntersections_simple_optimality) {
        std::vector<StreetSegmentIdx> path;
        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(4082, 4078));
        CHECK(path_is_legal(4082, 4078, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 34.32548756937995194);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(12655, 12656));
        CHECK(path_is_legal(12655, 12656, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 6.78771904895164724);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(14603, 206371));
        CHECK(path_is_legal(14603, 206371, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 95.17209100236996733);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(14685, 14686));
        CHECK(path_is_legal(14685, 14686, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 34.10496703674886021);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(22, 18039));
        CHECK(path_is_legal(22, 18039, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 5.33110525646702182);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(47989, 47990));
        CHECK(path_is_legal(47989, 47990, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2.03006719174479144);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(80633, 80632));
        CHECK(path_is_legal(80633, 80632, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 11.22126984693958818);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(87126, 87125));
        CHECK(path_is_legal(87126, 87125, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 12.26566009008592673);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(90134, 90133));
        CHECK(path_is_legal(90134, 90133, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 7.86933001728303516);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(99384, 99392));
        CHECK(path_is_legal(99384, 99392, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 16.42682236063055612);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(105890, 43579));
        CHECK(path_is_legal(105890, 43579, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 11.90580087439021106);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(124175, 124174));
        CHECK(path_is_legal(124175, 124174, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 13.15167479485719326);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(126296, 126295));
        CHECK(path_is_legal(126296, 126295, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 11.11411791005804872);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(82337, 82332));
        CHECK(path_is_legal(82337, 82332, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 10.64197863162361024);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(70270, 52570));
        CHECK(path_is_legal(70270, 52570, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2.72893430334343678);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(148592, 148470));
        CHECK(path_is_legal(148592, 148470, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 5.45133231193049195);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(87809, 124938));
        CHECK(path_is_legal(87809, 124938, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 6.76419335499105223);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(107359, 150944));
        CHECK(path_is_legal(107359, 150944, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1.50998172791268859);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(49002, 49004));
        CHECK(path_is_legal(49002, 49004, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 39.51194981319596167);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(83200, 120947));
        CHECK(path_is_legal(83200, 120947, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 17.52163712929608153);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(91598, 94027));
        CHECK(path_is_legal(91598, 94027, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2.68949035084233579);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(185177, 185184));
        CHECK(path_is_legal(185177, 185184, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1.94342856021615873);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(187157, 187160));
        CHECK(path_is_legal(187157, 187160, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1.49651417719553614);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(194107, 149996));
        CHECK(path_is_legal(194107, 149996, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 3.54834864902633207);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(194157, 194164));
        CHECK(path_is_legal(194157, 194164, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 10.48888573102301081);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(202178, 202176));
        CHECK(path_is_legal(202178, 202176, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1.43358081254962322);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(111831, 163037));
        CHECK(path_is_legal(111831, 163037, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 9.09697415885436911);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(213724, 213720));
        CHECK(path_is_legal(213724, 213720, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2.86864398070050619);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(221820, 30038));
        CHECK(path_is_legal(221820, 30038, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 31.01545277434718173);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(111359, 111360));
        CHECK(path_is_legal(111359, 111360, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1.32455466452973880);

    } //findPathBetweenIntersections_simple_optimality

} //inter_inter_simple_path_func_optimality_public

