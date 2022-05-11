/*
Title: Init (initialization task)

Spencer Thiessen
Meghan Brehon

Created: Sept 8/2021
Last edited: Sept 23/2021

Decription: This program was written to be run on the MCF5282. The below RTEMS
task is the initialization task, "Init", to accompany tasks A and B found
in files "taska.c" and "taskb.c". Init creates tasks A and B, then starts tasks
A and B, and then suspends itself.

Inputs: There are no inputs to this task (it is not passed any arguments).

Outputs: The function should create and start tasks A and B, allowing them to
run and produce their outputs. This task also passes the ID of task B to task A.
*/

// header files for the program
#include <stdlib.h> // standard C library
#include <stdio.h> // standard input and output
#include <bsp.h> // board support package
#include <rtems.h> // RTEMS definitions
#include <rtems/error.h> // RTEMS error definitions
#include "mcf5282.h" // definitions for MCF5282 (registers and pins used in the program)

// define taskA argument
rtems_task taskA(
  rtems_task_argument argument
);

// define taskB argument
rtems_task taskB(
  rtems_task_argument argument
);

// define Init argument
rtems_task Init(
  rtems_task_argument ignored
)

{
rtems_status_code scA;  // status code for task A
rtems_id tidA;  // ID for task A

// the below segment creates task A
scA =  rtems_task_create(rtems_build_name ('T', 'S', 'K', 'A'), // set the taskA name to TSKA
       50, // set the priority
       2*1024,  // set the size
       RTEMS_PREEMPT|RTEMS_NO_TIMESLICE|RTEMS_NO_ASR|RTEMS_INTERRUPT_LEVEL(0), // modes of taskA, enable preempting, disable timeslicing, disable ASR processing, set interrupt level to 0
       RTEMS_NO_FLOATING_POINT|RTEMS_LOCAL, // attributes of taskA, set non-floating point, and local
       &tidA); // set the ID
// below is an error message if the task is not successfully created
if ( scA != RTEMS_SUCCESSFUL ) {
  printf( "Can't create task A: %s\n", rtems_status_text(scA) ); // if the status code does not show RTEMS_SUCCESSFUL, print this error message
  rtems_task_suspend( RTEMS_SELF ); // suspend the task if not created
}

rtems_status_code scB; // status code for task B
rtems_id tidB;  // ID for task B

// the below segment creates task A
scB =  rtems_task_create(rtems_build_name ('T', 'S', 'K', 'B'), // set the name of taskB to TSKB
       50, // set the priority
       2*1024,  // set the size
       RTEMS_PREEMPT|RTEMS_NO_TIMESLICE|RTEMS_NO_ASR|RTEMS_INTERRUPT_LEVEL(0), // modes of taskB, enable preempting, disable timeslicing, disable ASR processing, set interrupt level to 0
       RTEMS_NO_FLOATING_POINT|RTEMS_LOCAL, // attributes of taskB, set non-floating point, and local
       &tidB); // ID for task B
// below is an error message if the task is not successfully created
if ( scB != RTEMS_SUCCESSFUL ) {
  printf( "Can't create task B: %s\n", rtems_status_text(scB) ); // if the status code does not show RTEMS_SUCCESSFUL, print this error message
  rtems_task_suspend( RTEMS_SELF ); // suspend the task if not created
}

  // starting task A
  scA = rtems_task_start(
         tidA, // task A ID
         taskA, // entry point
         tidB // task argument (set as the ID of task B so that it can be used in task A to send an event to task B)
  );

  // starting task B
  scB = rtems_task_start(
        tidB, // task B ID
        taskB, // entry point
        0 // task argument (leave as 0 as nothing needs to be passed to task B)
  );

  rtems_status_code scInit; // status code for the Init task

  // suspending init
  scInit = rtems_task_suspend(
       RTEMS_SELF // gets ID of INIT in order to suspend itself
);
// below is an error message if the task is not successfully suspended
if ( scInit != RTEMS_SUCCESSFUL ) {
  printf( "Can't receive event: %s\n", rtems_status_text(scInit) ); // if the status code does not show RTEMS_SUCCESSFUL, print this error message
  rtems_task_suspend( RTEMS_SELF ); // suspend the task if it was not already suspended
}

}
/* configuration information */

/* NOTICE: the clock driver is explicitly disabled */
#define CONFIGURE_MICROSECONDS_PER_TICK 10000 // configure the clock to have 10000 us per tick

#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER // configure the clock driver so that it is enabled

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER // again configuring the clock driver

#define CONFIGURE_MAXIMUM_TASKS            3 // set to 3 because we have 3 tasks

#define CONFIGURE_MAXIMUM_SEMAPHORES       5 // set max semaphores used in code

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE // configures initial tasks table

#define CONFIGURE_USE_MINIIMFS_AS_BASE_FILESYSTEM // Makes IMFS (In-memory file system)

#define CONFIGURE_INIT // makes <rtems/confdefs.h> instantiate configuration data structures

#include <rtems/confdefs.h> // produces almost all configuration tables required by RTEMS

/* end of configuration information */


/* end of 'init.c' file */
