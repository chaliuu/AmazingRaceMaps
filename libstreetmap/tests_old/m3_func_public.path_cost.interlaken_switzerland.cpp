#include <random>
#include <UnitTest++/UnitTest++.h>

#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"

#include "unit_test_util.h"
#include "path_verify.h"

using ece297test::relative_error;
using ece297test::path_is_legal;


SUITE(path_cost_public) {
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
    TEST(computePathTravelTime) {
        std::vector<StreetSegmentIdx> path;
        double turn_penalty;
        double expected;
        double actual;

        path = {530, 529, 528, 527, 526, 1906, 1905, 1904, 1903, 1902, 1901, 1900, 1899, 1898, 1897, 1896, 1940, 1, 0};
        turn_penalty = 0.90258765451972178;
        expected = 120.34909650646122259;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {1726, 946, 1910, 1909, 1756, 1902, 1901, 1900, 1899, 1898, 1897, 1896, 1940, 1939, 2099, 2098, 53, 8, 7, 6};
        turn_penalty = 7.66876581015625014;
        expected = 148.09737525973523020;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {1379, 1380, 2225, 2226, 4, 5, 6, 7, 8, 53, 2098, 2099, 1939, 1, 0};
        turn_penalty = 0.00000000000000000;
        expected = 148.84607108086026983;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {1749, 1662, 1663, 1664, 838, 479, 2187, 478, 837, 1836, 1256, 1255, 1254, 1253, 1252, 761, 760, 55, 50, 51, 52, 53, 2098, 2099, 1939, 1940, 1896, 1897, 1898, 10};
        turn_penalty = 12.86716044314528418;
        expected = 175.42588779710240487;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {509, 510, 511, 512, 467, 466, 436, 435, 434, 908, 909, 910, 930, 931, 1120, 1119, 20, 528, 527, 526, 1906, 1905, 1904, 1903, 1902, 1901, 1900, 1899, 1898, 1897, 1896, 1940, 1, 0};
        turn_penalty = 0.00000000000000000;
        expected = 188.39061335111213680;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {1129, 1799, 2061, 31, 30, 29, 219, 218, 217, 216, 215, 214, 1533, 1546, 58, 210, 209, 208, 207, 59, 2059, 1025, 1024, 1023, 1022, 1821, 1833, 1895, 1894, 1893, 1892, 1891, 1890, 1889, 1888, 1887, 1756, 1902, 1901, 1900, 1899, 1898, 1897, 1896, 1940};
        turn_penalty = 2.68072293181142607;
        expected = 189.70564767343836365;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {230, 1844, 228, 229, 1845, 1389, 2114, 1532, 1533, 1546, 58, 210, 209, 208, 207, 59, 2059, 1025, 1024, 1023, 1022, 1821, 1833, 1895, 1894, 1893, 1892, 1891, 1890, 1889, 1888, 1887, 1756, 1902, 1901, 1900, 1899, 1898, 1897, 1896, 1940, 1939, 2099, 2098, 53, 8, 7, 6};
        turn_penalty = 7.96910429139791976;
        expected = 278.47499138309473210;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {1561, 995, 994, 1886, 80, 79, 78, 1545, 1531, 1532, 1533, 1546, 58, 210, 209, 208, 207, 59, 2059, 1025, 1024, 1023, 1022, 1821, 206, 205, 818, 817, 531, 530, 529, 20, 21, 22};
        turn_penalty = 27.22910222223687171;
        expected = 290.82894770783468630;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {506, 505, 504, 503, 1244, 1245, 2224, 456, 1231, 1230, 441, 2, 3, 4, 5, 6, 7, 8, 53, 2098, 2099, 1939, 1940, 1896, 1897, 1898};
        turn_penalty = 13.71927624544100688;
        expected = 298.74646121727107584;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {948, 949, 1997, 1998, 1999, 2000, 2001, 2002, 83, 84, 1548, 1549, 1550, 1551, 1552, 1553, 1554, 1555, 1556, 1557, 1257, 335, 336, 337, 2081, 1534, 2082, 2173, 48, 1761, 2136, 491, 492, 2137, 489, 2134, 490, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52, 53, 2098, 2099, 1939, 1, 0};
        turn_penalty = 0.00000000000000000;
        expected = 308.75248165809239254;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {355, 354, 353, 346, 347, 348, 1959, 1960, 1961, 912, 911, 1798, 1797, 1796, 1795, 1794, 1793, 1792, 1791, 1790, 1789, 1788, 2014, 1937, 44, 45, 1983, 1984, 1785, 160, 1458, 121, 475, 223, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52};
        turn_penalty = 10.72199757501731554;
        expected = 340.67270865951212500;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {1883, 1855, 1343, 1342, 1341, 1340, 1339, 1338, 221, 1440, 1441, 1442, 1443, 1444, 1445, 1446, 1447, 1448, 1449, 1450, 1039, 1598, 1599, 1600, 1601, 1393, 1394, 999, 1065, 1002, 1001, 1000, 255, 33, 32};
        turn_penalty = 38.78946586502576110;
        expected = 341.29800757440199277;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {998, 2175, 1352, 2023, 2176, 2170, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 2029, 949, 948, 947, 900, 1880, 1882, 1881, 241, 245, 244, 242, 1763};
        turn_penalty = 43.83224127580765384;
        expected = 354.07032441998643435;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {2029, 1997, 1998, 1999, 2000, 2001, 2002, 83, 84, 1548, 1549, 1550, 1551, 1552, 1553, 1554, 1555, 1556, 1557, 1257, 335, 336, 337, 2081, 1534, 2082, 2173, 48, 1761, 2136, 491, 492, 2137, 489, 2134, 490, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52, 53, 2098, 2099, 1939, 1940, 1896, 447, 448};
        turn_penalty = 17.26744121680091126;
        expected = 378.02937249301436395;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {763, 597, 586, 269, 270, 715, 589, 590, 717, 1783, 260, 261, 200, 201, 1973, 175, 1983, 1984, 1785, 160, 1458, 121, 475, 223, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52, 8, 7, 6, 5, 4, 3};
        turn_penalty = 4.11236351442220283;
        expected = 379.78777340468820967;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {672, 1784, 656, 1744, 1743, 291, 1787, 1786, 199, 743, 82, 176, 746, 45, 1983, 1984, 1785, 160, 1458, 121, 475, 223, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52, 8, 7, 6};
        turn_penalty = 7.92470683533765108;
        expected = 415.44198059055793237;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {66, 67, 68, 866, 1332, 1333, 1548, 84, 83, 2002, 2001, 2000, 1999, 1998, 1997, 949, 948, 947, 2028, 2027, 1336, 1337, 231, 193, 192, 1886, 1885, 1884, 1883, 1855, 1343, 1342, 1341, 1340, 1339, 1338, 221, 1440, 1441, 1442, 1443, 1444, 1445, 1446, 1447, 1448, 1512, 1513, 1514, 1515};
        turn_penalty = 44.11521863240028551;
        expected = 439.20053611168953012;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {565, 564, 563, 397, 396, 395, 394, 393, 954, 953, 608, 607, 606, 605, 1787, 1786, 199, 743, 82, 176, 746, 45, 1983, 1984, 1785, 160, 1458, 121, 475, 223, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52, 8, 7, 6, 5, 4, 3, 2};
        turn_penalty = 3.90960681914189401;
        expected = 440.72797736946387204;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {2046, 164, 2094, 2089, 403, 2199, 42, 2079, 2080, 60, 2085, 2131, 2132, 2133, 48, 1761, 2136, 491, 492, 2137, 489, 2134, 490, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52, 53, 2098, 2099, 1939, 1940, 1896, 1897, 1898, 1899, 1900, 1901, 1902, 1903, 1904, 1905, 11, 12, 1140, 24};
        turn_penalty = 29.50603330874932340;
        expected = 442.89345142929687427;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {1392, 1396, 1393, 144, 143, 142, 141, 140, 914, 913, 1603, 1867, 598, 1354, 2016, 2015, 585, 587, 588, 715, 589, 590, 717, 1783, 260, 261, 200, 201, 1973, 175, 1983, 1984, 1785, 160, 1458, 121, 475, 223, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52, 8, 7, 6, 5, 4};
        turn_penalty = 5.46601715552688994;
        expected = 449.72256786604486933;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {1216, 295, 294, 32, 33, 255, 256, 253, 1061, 925, 758, 923, 151, 583, 763, 597, 586, 269, 270, 715, 589, 590, 717, 1783, 260, 261, 200, 201, 1973, 175, 1983, 1984, 1785, 160, 1458, 121, 475, 223, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52, 8, 7, 6, 5};
        turn_penalty = 6.71398457277002869;
        expected = 474.10937083919822044;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {1957, 1956, 1955, 1954, 356, 1959, 348, 347, 346, 345, 344, 343, 342, 341, 340, 339, 109, 1307, 1306, 1995, 1994, 1993, 1992, 1991, 1990, 1989, 897, 900, 2028, 2027, 1336, 1337, 231, 193, 192, 80, 79, 78, 1545, 1531, 1532, 1533, 1546, 58, 210, 209, 208, 207, 59, 2059, 1025, 1024, 1023, 1022, 1821, 206, 205, 818, 817, 531, 530, 529, 20, 21, 22, 23, 24, 25, 26};
        turn_penalty = 31.34028327739956765;
        expected = 534.10340633643374986;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {398, 397, 396, 395, 394, 393, 954, 953, 608, 607, 606, 605, 1787, 1786, 199, 743, 82, 176, 746, 45, 1983, 1984, 1785, 160, 1458, 121, 475, 223, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52, 53, 2098, 2099, 1939, 1940, 1896, 1897, 1898, 1899, 1900, 1901, 1902, 1903, 1904, 1905, 1906, 526, 527, 528, 20};
        turn_penalty = 25.16084927376740765;
        expected = 578.88292679007804509;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {1297, 1277, 1278, 1355, 485, 484, 1191, 1192, 1784, 656, 1744, 1743, 291, 1787, 1786, 199, 743, 82, 176, 746, 45, 1983, 1984, 1785, 160, 1458, 121, 475, 223, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52, 53, 2098, 2099, 1939, 1940, 1896, 1897, 1898, 1899, 1900, 1901, 1902, 1903, 1904, 1905};
        turn_penalty = 14.24546986562031847;
        expected = 645.67764266205699641;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {2193, 249, 248, 1040, 1737, 0, 1, 1939, 2099, 2098, 53, 52, 51, 50, 54, 57, 2100, 1043, 550, 49, 2194, 1938, 47, 2128, 2125, 2126, 2135, 489, 2138, 2139, 2142, 735, 1782, 1460, 1459, 161, 85, 1975, 1971, 1977, 1972, 202, 203, 292, 592, 591, 584, 486, 718, 580, 581, 578, 714, 487, 599, 151, 923, 922, 757, 925, 1061, 253, 256, 255, 33, 32};
        turn_penalty = 38.07595966077786898;
        expected = 689.13344382254240372;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {780, 779, 778, 777, 776, 775, 774, 773, 772, 799, 798, 797, 796, 795, 794, 793, 771, 770, 769, 768, 767, 766, 765, 165, 582, 1008, 1007, 792, 577, 763, 597, 586, 269, 270, 715, 589, 590, 717, 1783, 260, 261, 200, 201, 1973, 175, 1983, 1984, 1785, 160, 1458, 121, 475, 223, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52, 53, 2098, 2099, 1939, 1940, 1896, 1897, 1898, 1899, 1900, 1901, 1902, 1903, 1904, 1905, 11, 12, 1140, 24, 25, 26};
        turn_penalty = 31.07746946120639464;
        expected = 725.20531298634512041;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {1965, 1966, 1967, 360, 1958, 1957, 1956, 1955, 1954, 1311, 1310, 1152, 1151, 911, 1798, 1797, 1796, 1795, 1794, 1793, 1792, 1791, 1790, 1789, 1788, 2014, 1937, 44, 45, 1983, 1984, 1785, 160, 1458, 121, 475, 223, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52, 53, 2098, 2099, 1939, 1940, 1896, 1897, 1898, 1899, 1900, 1901, 1902, 1903, 1904, 1905, 11, 12, 1140, 24, 25, 26};
        turn_penalty = 31.68914896056834252;
        expected = 756.50937110914867390;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {570, 569, 568, 567, 566, 565, 564, 563, 397, 396, 395, 394, 393, 954, 953, 608, 607, 606, 605, 1787, 1786, 199, 743, 82, 176, 746, 45, 1983, 1984, 1785, 160, 1458, 121, 475, 223, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52, 53, 2098, 2099, 1939, 1940, 1896, 1897, 1898, 1899, 1900, 1901, 1902, 1903, 1904, 1905, 11, 12, 1140, 24, 25, 26, 27};
        turn_penalty = 32.80671457076476116;
        expected = 774.07319871642323506;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {1417, 1416, 1415, 1414, 1413, 1412, 1411, 1410, 1409, 455, 5, 6, 7, 8, 52, 51, 50, 54, 57, 2100, 1043, 550, 49, 2194, 1938, 47, 2128, 2125, 2126, 2135, 489, 2138, 2139, 2142, 735, 1782, 1460, 1459, 161, 85, 1975, 1971, 1977, 1972, 202, 203, 292, 592, 591, 584, 486, 718, 580, 581, 578, 716, 579, 763, 577, 791, 1354, 598, 1867, 1604, 914, 915, 1594, 1596, 1868, 1869, 34, 35};
        turn_penalty = 43.34477103046508972;
        expected = 810.06420641751753919;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

        path = {381, 1237, 370, 369, 1058, 1236, 1235, 1234, 1233, 483, 188, 732, 1784, 656, 1744, 1743, 291, 1787, 1786, 199, 743, 82, 176, 746, 45, 1983, 1984, 1785, 160, 1458, 121, 475, 223, 2124, 2129, 47, 1938, 2194, 49, 550, 1043, 2100, 57, 54, 50, 51, 52, 53, 2098, 2099, 1939, 1940, 1896, 1897, 1898, 1899, 1900, 1901, 1902, 1903, 1904, 1905, 11, 12, 1140, 24};
        turn_penalty = 29.15722898780660799;
        expected = 863.71344110648317383;
        actual = computePathTravelTime(turn_penalty, path);
        CHECK(relative_error(expected, actual) < 0.002000000);

    } //computePathTravelTime

} //path_cost_public

