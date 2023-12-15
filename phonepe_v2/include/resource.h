#ifndef __RESOURCE_H
#define __RESOURCE_H 1

#include<bits/stdc++.h>
#include"resource_type.h"
#include"resource_status.h"
using namespace std;

map<string, int> unique_resource_ids;
class resource {
    private:
        string resource_id;
        int cpus;
        double price;
        resource_status status;
        resource_type type;

    void onboard_resource(string resource_id) {
        unique_resource_ids[resource_id] = 1;
    }

    bool is_resource_exists(string resource_id) {
        return unique_resource_ids[resource_id] == 1;
    }

    public:
        resource() {} //default constructor
        resource(string resource_id, int cpus, double price,
            resource_type type) {
                if (is_resource_exists(resource_id)) {
                    throw string("Already registered resource");
                }
                this -> resource_id = resource_id;
                this -> cpus = cpus;
                this -> price = price;
                this -> type = type;
                this -> status = resource_status::AVAILABLE;
                onboard_resource(resource_id);
            }

        //getters
        string get_resource_id() const {
            return this -> resource_id;
        }
        int get_cpus() {
            return this -> cpus;
        }
        double get_price() {
            return this -> price;
        }
        resource_type get_resource_type() {
            return this -> type;
        }
        resource_status get_resource_status() {
            return this -> status;
        }

        //setter
        void set_status(resource_status status) {
            this->status = status;
        }
};

bool operator< (const resource &r1, const resource &r2) {
    return r1.get_resource_id() < r2.get_resource_id();
}

#endif
