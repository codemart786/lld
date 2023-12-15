#ifndef __RESTAURANT_H
#define __RESTAURANT_H 1

#include<bits/stdc++.h>
using namespace std;

#include"cuisine.h"
#include"states.h"

map<string, int> unique_restaurant_ids;
class restaurant {
    private:
        string restaurant_id;
        cuisine _cuisine;
        int cost_bracket;
        double rating;
        bool is_recommended;
        time_t onboarded_time;

        bool is_restaurant_exists(string restaurant_id) {
            return unique_restaurant_ids[restaurant_id] == states::ONBOARDED;
        }
        bool is_valid_rating(double rating) {
           return rating >= 0 && rating <= 5.0;
        }
        bool is_valid_cost_bracket(int cost_bracket) {
            return cost_bracket > 0 && cost_bracket <= 5;
        }

        void onboard_restaurant(string restaurant_id) {
            unique_restaurant_ids[restaurant_id] = states::ONBOARDED;
        }

    public:
        restaurant() {} //default constructor
        //constructor initialising objects, with some defaults
        //if no value provided for the parameter/attribute
        restaurant(string restaurant_id, cuisine _cuisine, 
            int cost_bracket, bool is_recommended = false, 
            double rating = 0.0, time_t onboarded_time = time(NULL)) {
                if (is_restaurant_exists(restaurant_id)) {
                    throw string("Already registered Restaurant");
                }
                if (!is_valid_cost_bracket(cost_bracket)) {
                    throw string("Invalid cost bracket for a restaurant");
                }
                if (!is_valid_rating(rating)) {
                    throw string("Invalid rating for a restaurant");
                }
                if (_cuisine == cuisine::DUMMY) {
                    throw string("Invalid cuisine provided for a restaurant");
                }
                this -> restaurant_id = restaurant_id;
                this -> _cuisine = _cuisine;
                this -> cost_bracket = cost_bracket;
                this -> rating = rating;
                this -> is_recommended = is_recommended;
                this -> onboarded_time = onboarded_time;
                onboard_restaurant(restaurant_id);
            }
        
        //public getters method
        string get_restaurant_id() const {
            return this -> restaurant_id;
        }
        cuisine get_cuisine() {
            return this -> _cuisine;
        }
        int get_cost_bracket() {
            return this -> cost_bracket;
        }
        double get_rating() {
            return this -> rating;
        }
        bool get_is_recommended() {
            return this -> is_recommended;
        }
        time_t get_onboarded_time() {
            return this -> onboarded_time;
        }
};

bool operator< (const restaurant &r1, const restaurant &r2) {
    return r1.get_restaurant_id() < r2.get_restaurant_id();
}

#endif
