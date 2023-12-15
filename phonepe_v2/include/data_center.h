#ifndef __DATA_CENTER_H
#define __DATA_CENTER_H 1

#include<bits/stdc++.h>
#include"resource.h"
#include"resource_type.h"
using namespace std;

map<string, int> unique_data_center_ids;
class data_center {

    private:
        string location;
        string data_center_id;
        set<resource> resources; //set of all the resources in DC

        void onboard_data_center(string data_center_id) {
            unique_data_center_ids[data_center_id] = 1;
        }

        bool is_data_center_exists(string data_center_id) {
            return unique_data_center_ids[data_center_id] == 1;
        }

    public:
        data_center() {} //default constructor
        data_center(string data_center_id, string location) {
            if (is_data_center_exists(data_center_id)) {
                throw string("Already registered data center");
            }
            this -> data_center_id = data_center_id;
            this -> location = location;
        }
        //getters
        string get_data_center_id() const {
            return this -> data_center_id;
        }
        string get_location() {
            return this -> location;
        }


        //to handle one resource type, with its requirement
        //get_available_resources(map<resource_type, int>)
        /*
            data center
                => naive impl of data_center
                => subzones, 
                => data center is the least clustered
                => Problem stmt: resource available, with the given filter and type
                => Redis bloom filter => 
                => assuming we have a list 
                => set, set of total resources
                => two set, available, allocated
                => available (>= ), O(lg N), lower_bound(cpus)
        */
        vector<resource> get_available_resources(resource_type type, int min_cpu) {
            vector<resource> res;
            std::copy_if (this->resources.begin(), this->resources.end(),
                std::back_inserter(res), [&](resource r) {
                    return r.get_resource_type() == type
                        && r.get_resource_status() == resource_status::AVAILABLE
                        && r.get_cpus() >= min_cpu;
                    });
            return res;
        }

        vector<resource> get_allocated_resources(resource_type type) {
            vector<resource> res;
            std::copy_if (this->resources.begin(), this->resources.end(),
                std::back_inserter(res), [&](resource r){
                    return r.get_resource_type() == type
                        && r.get_resource_status() == resource_status::ALLOCATED;
                    });
            return res;
        }

        //utility methods
        resource add_resource(resource &r) {
            resources.insert(r);
            return r;
        }

        bool delete_resource(resource &r) {
            if (r.get_resource_status() == resource_status::DELETED) {
                throw string("Already deleted resource");
            }
            //put a safety check, so that ongoing task can complete
            if (r.get_resource_status() == resource_status::ALLOCATED) {
                throw string("Currently in use. Please try again after sometime");
            }
            r.set_status(resource_status::DELETED);
            resources.erase(r);
            return true;
        }

};

bool operator< (const data_center &d1, const data_center &d2) {
    return d1.get_data_center_id() < d2.get_data_center_id();
}

#endif
