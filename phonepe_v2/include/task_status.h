#ifndef __TASK_STATUS_H
#define __TASK_STATUS_H 1

//enum depicting the task status
enum task_status { NEW, QUEUED, RUNNING, COMPLETED, ABORTED };

// NEW -> QUEUED -> RUNNING -> COMPLETED
                        // -> ABORTED
//            -> ABORTED
#endif
