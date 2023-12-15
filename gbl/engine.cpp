#include<bits/stdc++.h>
#include"include/user.h"
#include"include/restaurant.h"
#include"include/cuisine.h"
#include"include/config.h"
#include"include/order.h"
#define pb(a) push_back(a)
using namespace std;

bool is_new_restaurant(restaurant &r) {
    time_t now = time(NULL); //current time in seconds
    if (now - r.get_onboarded_time() <= NEW_RESTAURANT_TIME_WINDOW * 60 * 60){
        return true;
    }
    return false;
}

bool is_secondary_cuisine_rest(vector<cuisine_tracking> &secondary_cuisines,
    restaurant &r) {
    for (auto sc: secondary_cuisines) {
        if (r.get_cuisine() == sc.get_type()) return true;
    }
    return false;
}

bool is_secondary_cost_bracket_rest(vector<cost_tracking> &secondary_cost_brackets,
    restaurant &r) {
    for (auto sc: secondary_cost_brackets) {
        if (r.get_cost_bracket() == sc.get_cost_bracket()) return true;
    }
    return false;
}

bool is_top_kth_newly_created(vector<restaurant> &rests, int k, restaurant &r) {
    for (auto rc: rests) {
        if (k <= 0) break;
        if (is_new_restaurant(rc)) {
            k--;
            if (rc.get_restaurant_id() == r.get_restaurant_id()) return true;
        }
    }
    return false;
}

/*
    priority based sorting score calculation.
    Extensible for rule/priority based sorting.
    Currently highest power/exponent of 2 is 10, since
    we have 10 different rules. We can modify this number as 
    many rules we have, in near future.
    add 2 ^ x for higher priority weight.
    and then sum all the rules as applicable to get score of restaurant.

    Idea is 2^x > (2^(x - 1) + 2^(x - 2) + .... + 2 ^ 0).
    so if high priority rule is added to the score, with high
    power of 2, it is never possible that with even the sum
    of all the low powers of 2(low priority rules applicable),
    is greater than some high priority.
    So we get the desired ordering according to the rules.

*/
int calc_score(restaurant &r, user &u, vector<restaurant> &rests) {
    const string rest_id = r.get_restaurant_id();
    int score = 0; //start with 0 score
    if (r.get_is_recommended() && //featured restaurant
        u.get_primary_cuisine().get_type() == r.get_cuisine() //primary cuisine for user
        && u.get_primary_cost_bracket().get_cost_bracket() == r.get_cost_bracket() //primary cost for user
    ) {
        score += (1 << 10);
    }

    vector<cuisine_tracking> secondary_cuisines = u.get_secondary_cuisines();
    vector<cost_tracking> secondary_cost_brackets = u.get_secondary_cost_brackets();

    if ((r.get_is_recommended() &&
        u.get_primary_cuisine().get_type() == r.get_cuisine()
        && is_secondary_cost_bracket_rest(secondary_cost_brackets, r)
    ) ||
    (r.get_is_recommended() &&
        u.get_primary_cost_bracket().get_cost_bracket() == r.get_cost_bracket()
        && is_secondary_cuisine_rest(secondary_cuisines, r))
    ) {
        score += (1 << 9);
    }

    if (u.get_primary_cuisine().get_type() == r.get_cuisine()
        && u.get_primary_cost_bracket().get_cost_bracket() == r.get_cost_bracket()
        && r.get_rating() >= 4
    ) {
        score += (1 << 8);
    }
    if (u.get_primary_cuisine().get_type() == r.get_cuisine()
        && is_secondary_cost_bracket_rest(secondary_cost_brackets, r)
        && r.get_rating() >= 4.5
    ) {
        score += (1 << 7);
    }

    if (u.get_primary_cost_bracket().get_cost_bracket() == r.get_cost_bracket()
        && is_secondary_cuisine_rest(secondary_cuisines, r)
        && r.get_rating() >= 4.5
    ) {
        score += (1 << 6);
    }

    if (is_top_kth_newly_created(rests, 4, r)) {
        score += (1 << 5);
    }

    if (u.get_primary_cuisine().get_type() == r.get_cuisine()
        && u.get_primary_cost_bracket().get_cost_bracket() == r.get_cost_bracket()
        && r.get_rating() < 4
    ) {
        score += (1 << 4);
    }

    if (u.get_primary_cuisine().get_type() == r.get_cuisine()
        && is_secondary_cost_bracket_rest(secondary_cost_brackets, r)
        && r.get_rating() < 4.5
    ) {
        score += (1 << 3);
    }

    if (u.get_primary_cost_bracket().get_cost_bracket() == r.get_cost_bracket()
        && is_secondary_cuisine_rest(secondary_cuisines, r)
        && r.get_rating() < 4.5
    ) {
        score += (1 << 2);
    }
    //base score addition
    score += (1 << 1);
    return score;
}



/*
    Sorts the restaurant acc to the algorithm mentioned in
    spec/requirments doc: https://docs.google.com/document/d/1XdRGqjMaEFQRkRlOAYUFr0loFM79mBpEMYje-rtoDeM/edit#
    returns top RETURN_RESTAURANTS_LIST_LIMIT, default value 100
*/
vector<string> get_restaurant_recommendations(user u, 
    vector<restaurant> &available_restaurants) {
    vector<restaurant> rests = available_restaurants;
    //sorting according to the rating of the restaurant
    sort(rests.begin(), rests.end(), [&](restaurant &r1, restaurant &r2) {
        return r1.get_rating() > r2.get_rating();
    });
    sort(available_restaurants.begin(), available_restaurants.end(),
        [&](restaurant &a, restaurant &b) {
            return calc_score(a, u, rests) > calc_score(b, u, rests);
        });

    vector<string> res;
    int limit = RETURN_RESTAURANTS_LIST_LIMIT;
    for (auto r: available_restaurants) {
        if (limit <= 0) break;
        res.push_back(r.get_restaurant_id());
        limit--;
    }
    return res;
}

//utility function
template<typename T>
void print_vector(vector<T> &a) {
    for (T x: a) cout << x << ' ';
    cout << '\n';
}

/*
Driver function, used for seeding data and testing the entire codebase
creating test data and testing the codebase here;
*/
int main () {
    user user_1, user_2;
    vector<restaurant> res;
    order o;
    try {
        user u1("1"), u2("2");
        user_1 = u1, user_2 = u2;
        restaurant r1("1", cuisine::SOUTH_INDIAN, 1,false, 2);
        restaurant r2("2", cuisine::SOUTH_INDIAN, 1, true, 4);
        restaurant r3("3", cuisine::NORTH_INDIAN, 2, false, 4.5);
        restaurant r4("4", cuisine::CHINESE, 3, true, 5);
        restaurant r5("5", cuisine::NORTH_INDIAN, 4, true);
        restaurant r6("6", cuisine::CHINESE, 5, true);
        restaurant r7("7", cuisine::NORTH_INDIAN, 5, false);
        restaurant r8("8", cuisine::SOUTH_INDIAN, 1, true, 3);
        restaurant r9("9", cuisine::CHINESE, 5, false);
        restaurant r10("10", cuisine::CHINESE, 5, false);
        res = {r1, r2, r3, r4, r5, r6, r7, r8, r9, r10};
    } catch(string &s) {
        cout << "error " << s << '\n';
    }
    o.track_order(user_1, res[0]);
    o.track_order(user_1, res[0]);
    o.track_order(user_1, res[0]);
    o.track_order(user_1, res[1]);
    o.track_order(user_1, res[1]);
    o.track_order(user_1, res[2]);
    o.track_order(user_1, res[7]);
    o.track_order(user_1, res[0]);
    o.track_order(user_1, res[1]);
    o.track_order(user_1, res[3]);

    vector<string> final_sorted_list = get_restaurant_recommendations(
        user_1, res
    );
    print_vector(final_sorted_list);
    return 0;
}
