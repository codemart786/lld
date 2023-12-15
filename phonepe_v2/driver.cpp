#include<bits/stdc++.h>
#include"include/resource.h"
#include"include/data_center.h"
#include"include/task.h"
#include"include/resource_type.h"
#include"include/task_allocator.h"
#include"include/criteria.h"
#include"include/task_status.h"
#include"include/resource_status.h"
using namespace std;

int main () {
    /*
        due to lack of time, enclosing 
        in single try-catch block.
        Can divide them, for proper error handling cases
    */
    try {

        //creating resource
        resource r1("1", 10, 30, resource_type::SERVER_INSTANCE);
        resource r2("2", 5, 15, resource_type::SERVER_INSTANCE);

        //creating data center
        data_center dc("1", "chennai");

        //adding resources
        dc.add_resource(r1);
        dc.add_resource(r2);

        //creating tasks
        task t1("1", 2);
        task t2("2", 3);

        //creating task allocator
        task_allocator ta(dc);
        price_criteria_impl pcr;
        exec_time_criteria_impl excr;

        ta.allocate(t1, &pcr);
        ta.consume();

        ta.allocate(t2, &excr);
        ta.consume();
    } catch(string &s) {
        cout << " error " << s << '\n';
    }
    return 0;
}
