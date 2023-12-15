#ifndef __CRITERIA_H
#define __CRITERIA_H

#include<bits/stdc++.h>
#include"resource.h"
using namespace std;


//abstract class
class criteria {
    public:
        virtual resource get_best_resource(vector<resource> &resources) = 0;
};

class price_criteria_impl: public criteria {

    public:
        price_criteria_impl(){}
        resource get_best_resource(vector<resource> &resources) {
            sort(resources.begin(), resources.end(), [&](resource r1, resource r2) {
                return r1.get_price() < r2.get_price();
            });
            if (!resources.size()) {
                throw string("Empty resources list");
            }
            return resources[0];
        }
};

class exec_time_criteria_impl: public criteria {
    //exec time inversely proportional to number of cpu(s)
    public:
        resource get_best_resource(vector<resource> &resources) {
            sort(resources.begin(), resources.end(), [&](resource r1, resource r2) {
                return r1.get_cpus() > r2.get_cpus();
            });
            if (!resources.size()) {
                throw string("Empty resources list");
            }
            return resources[0];
        }
};

#endif