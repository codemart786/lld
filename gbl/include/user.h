#ifndef __USER_H
#define __USER_H 1

#include<bits/stdc++.h>
#include"cuisine_tracking.h"
#include"cost_tracking.h"
#include"states.h"
using namespace std;

map<string, int> unique_user_ids;
class user {

    private:
        string user_id;
        vector<cuisine_tracking> cuisines;
        vector<cost_tracking> cost_brackets;

        bool is_user_exists(string user_id) {
            return unique_user_ids[user_id] == states::ONBOARDED;
        }
        void onboard_user(string user_id) {
            unique_user_ids[user_id] = states::ONBOARDED;
        }

        /*
        sorts cost brackets list, in decreasing order of no of orders
        */
        void apply_sort_cost(vector<cost_tracking> &cost_brackets) {
            sort(cost_brackets.begin(), cost_brackets.end(),
                [&](cost_tracking c1, cost_tracking c2) {
                    return c1.get_no_of_orders() > c2.get_no_of_orders();
            });
        }

        /*
            sorts cuisines list, in decreasing order of no of orders
        */
        void apply_sort_cuisine(vector<cuisine_tracking> &cuisines) {
            sort(cuisines.begin(), cuisines.end(),
                [&](cuisine_tracking c1, cuisine_tracking c2) {
                    return c1.get_no_of_orders() > c2.get_no_of_orders();
            });
        }

    public:
        user() {} //default constructor
        user(string user_id) {
            if (is_user_exists(user_id)) {
                throw string("Already registered user");
            }
            this -> user_id = user_id;
            onboard_user(user_id);
        }

        /*
            tracks cuisines for user orders, keep them sorted
        */
        void add_cuisine_tracking(cuisine _cuisine) {
            for (auto &c: cuisines) {
                if (c.get_type() == _cuisine) {
                    c.incr_no_of_orders();
                    apply_sort_cuisine(cuisines);
                    return;
                }
            }
            cuisine_tracking c(_cuisine);
            c.incr_no_of_orders();
            cuisines.push_back(c);
            apply_sort_cuisine(cuisines);
        }


        /*
            tracks cost brackets for user orders, keep them sorted
        */
        void add_cost_tracking(int cost_bracket) {
            for (auto &cb: cost_brackets) {
                if (cb.get_cost_bracket() == cost_bracket) {
                    cb.incr_no_of_orders();
                    apply_sort_cost(cost_brackets);
                    return;
                }
            }
            cost_tracking cb(cost_bracket);
            cb.incr_no_of_orders();
            cost_brackets.push_back(cb);
            apply_sort_cost(cost_brackets);
        }

        string get_user_id() const {
            return this -> user_id;
        }
        vector<cost_tracking> get_cost_brackets() {
            return this -> cost_brackets;
        }
        vector<cuisine_tracking> get_cuisines() {
            return this -> cuisines;
        }

        /*
            fetches the primary cuisine for the user, which
            is the most ordered cuisine the user had ordered in the past.
            assumption: there will be no conflict for primary cuisine
            position and only one of the available cuisines will
            make it to the user primary list
        */
        cuisine_tracking get_primary_cuisine() {
            cuisine_tracking c;
            if (cuisines.size() == 0
                || cuisines[0].get_no_of_orders() == 0) return c;
            return cuisines[0];
        }
        /*
            fetches the secondary cuisine for the user, which
            is the next two most ordered cuisine(s) the user had ordered
            in the past.
        */
        vector<cuisine_tracking> get_secondary_cuisines() {
            vector<cuisine_tracking> ret; 
            cuisine_tracking c;
            if (cuisines.size() <= 1
                || cuisines[1].get_no_of_orders() == 0) ret.push_back(c);
            else ret.push_back(cuisines[1]);

            if (cuisines.size() <= 2
                || cuisines[2].get_no_of_orders() == 0) ret.push_back(c);
            else ret.push_back(cuisines[2]);
            return ret;
        }

        /*
            primary and secondary cost brackets definition
            is similar to primary and secondary cuisines
        */
        cost_tracking get_primary_cost_bracket() {
            cost_tracking c;
            if (cost_brackets.size() == 0
                || cost_brackets[0].get_no_of_orders() == 0) return c;
            return cost_brackets[0];
        }
        vector<cost_tracking> get_secondary_cost_brackets() {
            vector<cost_tracking> ret;
            cost_tracking c;
            if (cost_brackets.size() <= 1
                || cost_brackets[1].get_no_of_orders() == 0) ret.push_back(c);
            else ret.push_back(cost_brackets[1]);

            if (cost_brackets.size() <= 2
                || cost_brackets[2].get_no_of_orders() == 0) ret.push_back(c);
            else ret.push_back(cost_brackets[2]);
            return ret;
        }
};

bool operator< (const user &u1, const user &u2) {
    return u1.get_user_id() < u2.get_user_id();
}

#endif
