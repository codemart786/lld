/*
order entity is created to decouple
the user and restaurant entity.
It follows the schema of generic order,
like can have status field
in future, denoting `order status`.
For now, it will help in decoupling user
and restaurant classes, and will orchaestrate
between the two.
*/

#ifndef __ORDER_H
#define __ORDER_H 1

#include<bits/stdc++.h>
#include"user.h"
#include"restaurant.h"
using namespace std;

int order_ids = 0;
class order {
    private:
        string order_id;
    public:
        order() {
            this -> order_id = ++order_ids;
        }
        
        void track_order(user &u, restaurant &r) {
            u.add_cuisine_tracking(r.get_cuisine());
            u.add_cost_tracking(r.get_cost_bracket());
        }

        string get_order_id() const {
            return this -> order_id;
        }
};

bool operator< (const order &o1, const order &o2) {
    return o1.get_order_id() < o2.get_order_id();
}

#endif
