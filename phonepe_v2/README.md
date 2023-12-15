## Entities:

    Task {
        task_id,
        min_cpu,

    }
    Resource {
        resource_type enum,
        price,
        bool is_available;
        int cpu;
    }
    DataCenter {
        
    }
    Resource_Allocator_Interface {

    }
    Reports_Interface {
        
    }


## To run:
    Open terminal and run following command
        g++ --std=c++17 driver.cpp
