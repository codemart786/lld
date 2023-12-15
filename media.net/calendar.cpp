#include"user.h"
#include"room.h"
#include"time_slot.h"
#include"meeting.h"
#include"util.h"

#include<bits/stdc++.h>
using namespace std;

//availabilty check
map<room, map<time_slot, meeting>> bookings;
vector<room> rooms;

bool is_available(room r, time_slot t) {
    for (auto px: bookings[r]) {
        time_slot t2 = px.first;
        if(!t.is_not_conflicting(t2)) return false;
    }
    return true;
}

bool is_capacity_allowed(room r, vector<user> guests) {
    return r.get_capacity() >= guests.size();
}
bool is_valid(room r, time_slot t, vector<user> guests) {
    return is_available(r, t) && is_capacity_allowed(r, guests);
}

//creates a new meeting
meeting create_meeting(user org_user, room r, time_slot t, vector<user> guests) {
    if (!is_valid(r, t, guests)) {
        throw string("INVALID REQUEST");
    }

    meeting m(org_user, t, r, guests);
    bookings[r][t] = m; //thread safe
    return m;
}


//cancels a given meeting
bool cancel_meeting(meeting &m) {
    room r = m.get_room();
    time_slot t = m.get_time_slot();
    if (bookings[r].count(t) == 0) { //Not a booked room
        throw string("INVALID REQUEST");
    }
    bookings[r].erase(t);
    return true;
}

//reschedule meeting
bool reschedule_meeting(meeting &m, time_slot new_slot) {
    if (!is_available(m.get_room(), new_slot)) {
        throw string("UNAVAILABLE ROOM DURING THE SLOT");
    }
    room r = m.get_room();
    if (cancel_meeting(m)) {
        bookings[r][new_slot] = m;
        return true;
    }
    return false;
}

vector<room> list_all_available_rooms(time_slot &t) {
    vector<room> ret;
    for (auto r: rooms) {
        if (is_available(r, t)) ret.push_back(r);
    }
    return ret;
}

//driver function
/*
    To run:  g++ --std=c++17 calendar.cpp
*/
int main () {
    user u1("1"), u2("2"), u3("3");
    room r("1", 10), r2("2", 5);
    rooms = {r, r2};
    time_slot t(1, 2);
    time_slot t2(2, 4);
    vector<user> guests = { u2, u3 };
    meeting m;
    try {
        m = create_meeting(u1, r, t, guests);
    } catch(string &s) {
        cout << "error " << s << '\n';
    }
    cout << is_available(r, t) << '\n';
    cout << is_available(r, t2) << '\n';
    vector<room> ret = list_all_available_rooms(t2);
    for (auto x: ret) cout << x.get_room_id() << '\n';
    return 0;
}
