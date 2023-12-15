#ifndef __USER_H

#include<bits/stdc++.h>
#include"states.h"
using namespace std;

#define __USER_H 1

map<string, int> unique_user_ids;
class user {
    private:
        string user_id;
    public:
        user() { //default constructor
        }
        user(string user_id) {
            if (is_user_exists(user_id)) {
                throw string("Already registered User");
            }
            this -> user_id = user_id;
            unique_user_ids[user_id] = states::ACTIVE;
        }

        bool is_user_exists(string user_id) {
            return unique_user_ids[user_id] == states::ACTIVE;
        }
        //getters and setters
        string get_user_id() const {
            return this -> user_id;
        }
};

bool operator< (const user &u1, const user &u2) {
    return u1.get_user_id() < u2.get_user_id();
}

#endif