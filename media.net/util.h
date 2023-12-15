//all utility related functions

#ifndef __UTIL_H
#define __UTIL_H

bool is_valid_slot(int start_time, int end_time) {
    return start_time <= end_time && start_time >= 0;
}

#endif
