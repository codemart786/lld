#ifndef __TASK_H
#define __TASK_H 1

#include<bits/stdc++.h>
#include"task_status.h"
using namespace std;

map<string, int> unique_task_ids;
class task {
    private:
        string task_id;
        int min_cpus;
        task_status status;

    bool is_task_exists(string task_id) {
        return unique_task_ids[task_id] == 1;
    }

    bool is_new_task(task_status status) {
        return status == task_status::NEW;
    }

    void onboard_task(string task_id) {
        unique_task_ids[task_id] = 1;
    }

    public:
        task() {} //default constructor
        task(string task_id, int min_cpus, task_status status = task_status::NEW) {
            if (is_task_exists(task_id)) {
                throw string("Already registered task");
            }
            if (!is_new_task(status)) {
                throw string("Invalid task status");
            }
            this->task_id = task_id;
            this->min_cpus = min_cpus;
            this->status = status;
            onboard_task(task_id);
        }

        //getters method
        string get_task_id() const {
            return this -> task_id;
        }
        int get_min_cpus() {
            return this -> min_cpus;
        }
        task_status get_status() {
            return this->status;
        }

        //setters
        void set_status(task_status status) {
            this->status = status;
        }
};

bool operator< (const task &t1, const task &t2) {
    return t1.get_task_id() < t2.get_task_id();
}

#endif
