#ifndef __ROOM_H

#include<bits/stdc++.h>
#include"states.h"
using namespace std;

#define __ROOM_H 1

map<string, int> unique_room_ids;
class room {
    private:
        int capacity;
        string room_id;
    public:
        room() { //default constructor
            this -> capacity = 0;
        }
        room(string room_id, int capacity = 0) {
            if (is_room_exists(room_id)) {
                throw string("Already registered Room");
            }
            this -> room_id = room_id;
            this -> capacity = capacity;
            unique_room_ids[room_id] = states::ACTIVE;
        }

        bool is_room_exists(string room_id) {
            return unique_room_ids[room_id] == states::ACTIVE;
        }

        //getters and setters
        string get_room_id() const {
            return this -> room_id;
        }

        int get_capacity() {
            return this -> capacity;
        }
};

bool operator< (const room &r1, const room &r2) {
    return r1.get_room_id() < r2.get_room_id();
}

#endif