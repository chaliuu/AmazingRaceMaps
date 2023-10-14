#include <random>
#include <iostream>
#include <UnitTest++/UnitTest++.h>

#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"
#include "m4.h"

#include "unit_test_util.h"
#include "courier_verify.h"

using ece297test::relative_error;
using ece297test::courier_path_is_legal;


SUITE(extreme_multi_london_england_public) {
    TEST(extreme_multi_london_england) {
        std::vector<DeliveryInf> deliveries;
        std::vector<IntersectionIdx> depots;
        float turn_penalty;
        std::vector<CourierSubPath> result_path;
        bool is_legal;

        deliveries = {DeliveryInf(77883, 182478), DeliveryInf(40066, 130962), DeliveryInf(183624, 151123), DeliveryInf(232423, 125207), DeliveryInf(126867, 42596), DeliveryInf(32577, 193387), DeliveryInf(32577, 9834), DeliveryInf(62452, 140541), DeliveryInf(166763, 228862), DeliveryInf(186169, 96318), DeliveryInf(235506, 8164), DeliveryInf(161266, 149477), DeliveryInf(198493, 164674), DeliveryInf(92375, 183196), DeliveryInf(54910, 158428), DeliveryInf(230206, 193387), DeliveryInf(195233, 236594), DeliveryInf(232423, 40167), DeliveryInf(78024, 79228), DeliveryInf(180268, 95978), DeliveryInf(32577, 125207), DeliveryInf(29207, 93454), DeliveryInf(118435, 129169), DeliveryInf(118435, 50800), DeliveryInf(126867, 7447), DeliveryInf(211781, 41906), DeliveryInf(114643, 173), DeliveryInf(118435, 193387), DeliveryInf(45123, 97124), DeliveryInf(120109, 239755), DeliveryInf(125792, 228862), DeliveryInf(126867, 14819), DeliveryInf(181226, 163848), DeliveryInf(32577, 151123), DeliveryInf(3204, 151123), DeliveryInf(169706, 164674), DeliveryInf(126867, 162194), DeliveryInf(44805, 222719), DeliveryInf(118435, 151123), DeliveryInf(112295, 76333), DeliveryInf(52038, 181241), DeliveryInf(32577, 193387), DeliveryInf(118435, 66462), DeliveryInf(32577, 227112), DeliveryInf(118435, 154963), DeliveryInf(45123, 125207), DeliveryInf(118435, 144188), DeliveryInf(32577, 45270), DeliveryInf(179665, 224184), DeliveryInf(77749, 125207), DeliveryInf(22970, 166401), DeliveryInf(126867, 130816), DeliveryInf(32577, 151123), DeliveryInf(45123, 143068), DeliveryInf(116820, 28991), DeliveryInf(32577, 224184), DeliveryInf(48044, 224184), DeliveryInf(126867, 228862), DeliveryInf(86342, 73151), DeliveryInf(126867, 224184), DeliveryInf(126867, 172006), DeliveryInf(86826, 66462), DeliveryInf(100119, 223662), DeliveryInf(118435, 66462), DeliveryInf(214718, 42462)};
        depots = {44};
        turn_penalty = 30.000000000;
        {
        	ECE297_TIME_CONSTRAINT(50000);
        	
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        }

        is_legal = courier_path_is_legal(deliveries, depots, result_path);
        CHECK(is_legal);

        if(is_legal) {
        	double path_cost = ece297test::compute_courier_path_travel_time(result_path, turn_penalty);
        	std::cout << "QoR extreme_multi_london_england: " << path_cost << std::endl;
        } else {
        	std::cout << "QoR extreme_multi_london_england: INVALID" << std::endl;
        }

    } //extreme_multi_london_england

} //extreme_multi_london_england_public

