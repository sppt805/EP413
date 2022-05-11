/*
Title: Task A

Spencer Thiessen
Meghan Brehon

Created: Sept 8/2021
Edited: Sept 23/2021

Description: This program was written to be run on an MCF5282. The program defines task A. It configures the general
input/output of the board such that the task can drive pin E3 either high or low in order to create a square wave on
the pin.

Variables:
  Input: the argument of this task is tidB, the ID of task B passed from the initialization task.

  Output: This task doesn't output variables, but rather should produce a square wave on pin E3 (pin E3 set to high) of the MCF5282.
*/

// header files for the program
#include <stdlib.h> // standard C library
#include <stdio.h> // standard input and output
#include <bsp.h> // board support package
#include <rtems.h> // RTEMS definitions
#include <rtems/error.h> // RTEMS error definitions
#include "mcf5282.h" // definitions for the MCF5282 (registers and pins used in the program)

// define the argument of the task to be tidB, the ID of task B (being passed from the initialization task)
rtems_task taskA(
  rtems_task_argument tidB
)
{

// status code for the task
rtems_status_code sc0;

// enable read and write for GPIO
MCF5282_CCM_CCR &= ~MCF5282_CCM_CCR_SZEN;

// set GPIO PE3 high to function as output
// DDRE : Data Direction Register E
MCF5282_GPIO_DDRE |= MCF5282_GPIO_DDRx(3);

// set portE low for digital output
// PEPAR : Port E Pin Assignment Register
MCF5282_GPIO_PEPAR &= ~MCF5282_GPIO_PEPAR_PEPA3;

// what task A does
for(;;){
  // wait for one clock tick, then continue
  sc0 = rtems_task_wake_after(
    1
  );
  // error message if the task does not successfully wake and resume
  if ( sc0 != RTEMS_SUCCESSFUL ) {
    printf( "Can't wake after: %s\n", rtems_status_text(sc0) ); // if the status code does not show success, print the error
    rtems_task_suspend( RTEMS_SELF ); // suspend the task if not successful
  }

  // Set pin E3 high
  MCF5282_GPIO_PORTE |= 0b00001000;

  // Send event to taskB
  sc0 = rtems_event_send(
    tidB,
    RTEMS_EVENT_0
  );
  // error message if the task is not successfully sent
  if ( sc0 != RTEMS_SUCCESSFUL ) {
    printf( "Can't send event: %s\n", rtems_status_text(sc0) ); // if the status code does not show success, print the error
    rtems_task_suspend( RTEMS_SELF ); // suspend the task if the event was not sent successfully
  }

  // Set pinE3 low by complimenting it
  MCF5282_GPIO_PORTE &= ~0b00001000;
}
}




// #include <rtems/confdefs.h>
