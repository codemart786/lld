#ifndef __CUISINE_TRACKING_H
#define __CUISINE_TRACKING_H 1

#include<bits/stdc++.h>
using namespace std;

#include"cuisine.h"

class cuisine_tracking {

    private:
        //south_indian, north_indian, or ... any other cuisine type
        cuisine type;
        int no_of_orders;

    public:
        cuisine_tracking() { //default constructor
            this -> no_of_orders = 0;
            this -> type = cuisine::DUMMY;
        }
        cuisine_tracking(cuisine type, int no_of_orders = 0) {
            this -> type = type;
            this -> no_of_orders = no_of_orders;
        }

        cuisine get_type() {
            return this -> type;
        }
        int get_no_of_orders() {
            return this -> no_of_orders;
        }
        void incr_no_of_orders() {
            this -> no_of_orders = this -> no_of_orders + 1;
        }
};

#endif
