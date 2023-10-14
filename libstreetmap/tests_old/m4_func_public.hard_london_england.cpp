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


SUITE(hard_london_england_public) {
    TEST(hard_london_england) {
        std::vector<DeliveryInf> deliveries;
        std::vector<IntersectionIdx> depots;
        float turn_penalty;
        std::vector<CourierSubPath> result_path;
        bool is_legal;

        deliveries = {DeliveryInf(104227, 222278), DeliveryInf(113235, 114497), DeliveryInf(154701, 219425), DeliveryInf(93932, 82632), DeliveryInf(244594, 233875), DeliveryInf(17950, 40084), DeliveryInf(166998, 102921), DeliveryInf(140827, 17215), DeliveryInf(112290, 87838), DeliveryInf(232625, 139894), DeliveryInf(124453, 184967), DeliveryInf(119021, 233947), DeliveryInf(235839, 47611), DeliveryInf(204220, 68374), DeliveryInf(211863, 232622), DeliveryInf(71076, 213919), DeliveryInf(39541, 235167), DeliveryInf(31931, 14689), DeliveryInf(130962, 28937), DeliveryInf(64962, 27273), DeliveryInf(11726, 157871), DeliveryInf(109761, 194335), DeliveryInf(239544, 81760), DeliveryInf(132938, 133469), DeliveryInf(232508, 86584), DeliveryInf(121957, 217025), DeliveryInf(55069, 45719), DeliveryInf(115250, 120761), DeliveryInf(176839, 90842), DeliveryInf(197996, 127676), DeliveryInf(205868, 230077), DeliveryInf(175907, 20466), DeliveryInf(223364, 51207), DeliveryInf(239121, 93423), DeliveryInf(136929, 235715), DeliveryInf(235241, 89052), DeliveryInf(77106, 200925), DeliveryInf(140929, 243846), DeliveryInf(196595, 139199), DeliveryInf(1657, 67432), DeliveryInf(114765, 165287), DeliveryInf(201894, 221081), DeliveryInf(11625, 170758), DeliveryInf(109263, 202734)};
        depots = {27};
        turn_penalty = 30.000000000;
        {
        	ECE297_TIME_CONSTRAINT(50000);
        	
        result_path = travelingCourier(turn_penalty, deliveries, depots);
        }

        is_legal = courier_path_is_legal(deliveries, depots, result_path);
        CHECK(is_legal);

        if(is_legal) {
        	double path_cost = ece297test::compute_courier_path_travel_time(result_path, turn_penalty);
        	std::cout << "QoR hard_london_england: " << path_cost << std::endl;
        } else {
        	std::cout << "QoR hard_london_england: INVALID" << std::endl;
        }

    } //hard_london_england

} //hard_london_england_public

