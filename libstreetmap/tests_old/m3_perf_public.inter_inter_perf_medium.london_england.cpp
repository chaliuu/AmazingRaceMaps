#include <random>
#include <UnitTest++/UnitTest++.h>

#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"

#include "unit_test_util.h"
#include "path_verify.h"

using ece297test::relative_error;
using ece297test::path_is_legal;


SUITE(inter_inter_path_perf_medium_public) {
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
    TEST_FIXTURE(MapFixture, findPathBetweenIntersections_perf_medium) {
        //Verify Functionality
        std::vector<StreetSegmentIdx> path;
        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(33539, 48507));
        CHECK(path_is_legal(33539, 48507, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2366.72190776064689999);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(51244, 102666));
        CHECK(path_is_legal(51244, 102666, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1471.48928327706221353);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(67297, 60432));
        CHECK(path_is_legal(67297, 60432, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2380.14597765036978672);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(68434, 65486));
        CHECK(path_is_legal(68434, 65486, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2575.47359398624485038);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(109805, 116735));
        CHECK(path_is_legal(109805, 116735, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 4725.71402790261254268);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(109842, 199663));
        CHECK(path_is_legal(109842, 199663, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1367.72000329408842845);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(116826, 224737));
        CHECK(path_is_legal(116826, 224737, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 3022.73209805691840302);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(162105, 141762));
        CHECK(path_is_legal(162105, 141762, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 919.09195511800771783);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(163296, 35783));
        CHECK(path_is_legal(163296, 35783, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1864.15053600842611559);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(199195, 230522));
        CHECK(path_is_legal(199195, 230522, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2566.41315250580100837);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(203253, 223434));
        CHECK(path_is_legal(203253, 223434, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1808.10383599079250416);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(175301, 20991));
        CHECK(path_is_legal(175301, 20991, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 472.47153269182797430);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(127132, 71129));
        CHECK(path_is_legal(127132, 71129, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 863.71662717575031820);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(56178, 221441));
        CHECK(path_is_legal(56178, 221441, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 924.40082545122265856);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(111597, 50071));
        CHECK(path_is_legal(111597, 50071, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1816.38350891719824176);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(164195, 55117));
        CHECK(path_is_legal(164195, 55117, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1017.14434116802920016);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(182730, 229273));
        CHECK(path_is_legal(182730, 229273, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1462.49568474521583994);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(186414, 66324));
        CHECK(path_is_legal(186414, 66324, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 879.30167767242232912);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(227291, 59664));
        CHECK(path_is_legal(227291, 59664, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1224.21606332372948600);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(83553, 78426));
        CHECK(path_is_legal(83553, 78426, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2942.30109351539977069);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(195225, 34121));
        CHECK(path_is_legal(195225, 34121, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 2300.70691592236289580);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(228788, 4467));
        CHECK(path_is_legal(228788, 4467, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 3973.49019681348181621);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(230574, 150660));
        CHECK(path_is_legal(230574, 150660, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2755.05252931132281446);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(231435, 50911));
        CHECK(path_is_legal(231435, 50911, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1792.14497482457454680);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(171031, 76664));
        CHECK(path_is_legal(171031, 76664, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 1211.57790053826875010);

        path = findPathBetweenIntersections(0.00000000000000000, std::make_pair(89829, 235147));
        CHECK(path_is_legal(89829, 235147, path));
        CHECK(computePathTravelTime(0.00000000000000000, path) <= 1510.11011697259641551);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(65252, 153333));
        CHECK(path_is_legal(65252, 153333, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2205.23127874284637073);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(16684, 79011));
        CHECK(path_is_legal(16684, 79011, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2475.04958373464478427);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(237994, 172575));
        CHECK(path_is_legal(237994, 172575, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2585.68139875488532198);

        path = findPathBetweenIntersections(15.00000000000000000, std::make_pair(184207, 162765));
        CHECK(path_is_legal(184207, 162765, path));
        CHECK(computePathTravelTime(15.00000000000000000, path) <= 2153.91006410280033379);

        //Generate random inputs
        std::vector<IntersectionIdx> intersection_ids1;
        std::vector<IntersectionIdx> intersection_ids2;
        std::vector<double> turn_penalties;
        for(size_t i = 0; i < 40; i++) {
            intersection_ids1.push_back(rand_intersection(rng));
            intersection_ids2.push_back(rand_intersection(rng));
            turn_penalties.push_back(rand_turn_penalty(rng));
        }
        {
            //Timed Test
            ECE297_TIME_CONSTRAINT(6861);
            std::vector<StreetSegmentIdx> result;
            for(size_t i = 0; i < 40; i++) {
                result = findPathBetweenIntersections(turn_penalties[i], std::make_pair(intersection_ids1[i], intersection_ids2[i]));
            }
        }
    } //findPathBetweenIntersections_perf_medium

} //inter_inter_path_perf_medium_public

