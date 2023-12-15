#ifndef __TASK_ALLOCATOR_H
#define __TASK_ALLOCATOR_H 1

#include<bits/stdc++.h>
#include"task.h"
#include"resource.h"
#include"criteria.h"
#include"data_center.h"
#include"task_status.h"
using namespace std;

class task_allocator {

    private:
        queue<task> wait_queue; //wait queue of tasks
        map<task, criteria *> task_criteria_map;
        data_center dc;
        map<task, resource> task_history;
        
    public:
        //task_allocator() {} //default constructor
        task_allocator(data_center &dc) {
            this -> dc = dc;
        }
        
        void doExec(resource &r, task &t) {
            //executing task t on resource r;
            /*
                Due to lack of time priting the report/
                status variables
            */
            r.set_status(resource_status::ALLOCATED); //allocating the resource
            t.set_status(task_status::RUNNING);

            // run the task, some exec function, or some entrypoint 
            //of the code, as in docker/k8s
            
            task_history[t] = r;
        }

        void allocate(task &t, criteria *c) {
            //allocate will just add to the wait queue
            if (t.get_status() != task_status::NEW) {
                throw string("Task not in valid state");
            }
            task_criteria_map[t] = c;
            wait_queue.push(t);
            t.set_status(task_status::QUEUED);
            printf("TASK SUBMITTED SUCCESSFULLY\n");
        }

        /*
            this method can be called periodically.
            cron - since it will poll the wait queue repeatedly
            FIFO order, may suffer from starvation
            can have max_retries parameter added for the task
            and in report
        */
        void consume() {
            if (!wait_queue.size()) { //empty queue
                return;
            }
            task &t = wait_queue.front();
            wait_queue.pop();
            
            criteria *cr = task_criteria_map[t];
            vector<resource> available_resources = dc.get_available_resources(
                resource_type::SERVER_INSTANCE, t.get_min_cpus()
            );

            if (!available_resources.size()) { //no available resource
                t.set_status(task_status::NEW);
                allocate(t, cr); //retry
                return;
            }
            resource r = cr->get_best_resource(available_resources);
            time_t start_time = time(NULL);
            doExec(r, t);

            r.set_status(resource_status::AVAILABLE);
            t.set_status(task_status::COMPLETED);
            time_t end_time = time(NULL);
            
            log_details(r, t, start_time, end_time, t.get_status());
        }

        void log_details(resource &r, task &t, time_t start_time,
            time_t end_time, task_status status) {
                /*
                    printing details on the screen
                    due to less time,
                    we can also send email or store 
                    report structure somewhere with us
                */
               cout << "\n===================\n";
               cout << " resource id " << r.get_resource_id() << '\n';
               cout << " task id " << t.get_task_id() << '\n';
               cout << " start time " << start_time << '\n';
               cout << " end time " << end_time << '\n';
               cout << " task status " << status << '\n';
               cout << "\n===================\n";
        }

};

#endif
