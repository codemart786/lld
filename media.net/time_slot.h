#ifndef __TIME_SLOT_H

#include<bits/stdc++.h>
#include"util.h"
using namespace std;

#define __TIME_SLOT_H 1

class time_slot {
    private:
        int start_time;
        int end_time;
    public:
        time_slot() {}
        time_slot(int start_time, int end_time) {
            if (!is_valid_slot(start_time, end_time)) {
                throw string("INVALID TIME SLOT");
            }
            this -> start_time = start_time;
            this -> end_time = end_time;    
        }

        bool is_not_conflicting(time_slot &t) {
            return (t.get_end_time() < this -> start_time)
                || (t.get_start_time() > this -> end_time);
        }

        //getters and setters
        int get_start_time() const {
            return this -> start_time;
        }
        int get_end_time() const {
            return this -> end_time;
        }
};

bool operator< (const time_slot &t1, const time_slot &t2) {
    return t1.get_start_time() < t2.get_start_time();
}

#endif