#ifndef __COST_TRACKING_H
#define __COST_TRACKING_H 1

#include<bits/stdc++.h>
#include"config.h"
using namespace std;

class cost_tracking {
    private:
        int cost_bracket; //cost bracket ... 0 -> 5
        int no_of_orders;

    public:
        cost_tracking() { //default constructor
            this -> no_of_orders = 0;
            //Not valid cost bracket, used only for dummy purposes
            this -> cost_bracket = DUMMY_COST_TRACKING;
        }
        cost_tracking(int cost_bracket, int no_of_orders = 0) {
            this -> cost_bracket = cost_bracket;
            this -> no_of_orders = no_of_orders;
        }

        int get_cost_bracket() {
            return this -> cost_bracket;
        }
        int get_no_of_orders() {
            return this -> no_of_orders;
        }
        void incr_no_of_orders() {
            this -> no_of_orders = this -> no_of_orders + 1;
        }
};

#endif
