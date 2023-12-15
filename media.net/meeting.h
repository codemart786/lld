#ifndef ____MEETING_H

#include<bits/stdc++.h>
#include"room.h"
#include"user.h"
#include"time_slot.h"
#include"states.h"
using namespace std;

#define ____MEETING_H 1

int ids = 0;
class meeting {
    private:
        int meeting_id;
        user org_user;
        time_slot t;
        vector<user> guests;
        room r;
        
    public:
        meeting() {} //default constructor
        meeting(user org_user, time_slot t, room r, vector<user> guests) {
            this -> org_user = org_user;
            this -> t = t;
            this -> r = r;
            this -> guests = guests;
            this -> meeting_id = ++ids;
        }

        //getters and setters
        vector<user> get_guests() {
            return this -> guests;
        }
        time_slot get_time_slot() {
            return this -> t;
        }

        room get_room() {
            return this -> r;
        }

        user get_org_user() {
            return this -> org_user;
        }

        int get_meeting_id() const {
            return this -> meeting_id;
        }
};

bool operator< (const meeting &m1, const meeting &m2) {
    return m1.get_meeting_id() < m2.get_meeting_id();
}

#endif