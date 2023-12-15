#ifndef __RESOURCE_STATUS_H
#define __RESOURCE_STATUS_H 1

//enum depicting the resource status
/*
can have one more state as onboarded.
For our assignment available = onboarded, 
but availability of the resource
should be only when it's available
to execute the task, after various
health metrics / heartbeat signals
are passing.
i.e
ONBOARDED/NEW -> AVAILABLE
AVAILABLE=NEW

*/
enum resource_status { AVAILABLE, ALLOCATED, DELETED };

#endif
