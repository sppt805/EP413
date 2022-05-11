/*
Title: Task B

Spencer Thiessen
Meghan Brehon

Created: Sept 8/2021
Edited: Sept 23/2021

Description: This program was written to be run on an MCF5282. The program defines task B. It configures the general
input/output of the board such that the task can drive pin E2 either high or low in order to create a square wave on
the pin.

Variables:
  Input: This task does not have any input arguments.

  Output: This task doesn't output variables, but rather should produce a square wave on pin E2 of the MCF5282.
*/

// header files for the program
#include <stdlib.h> // standard C library
#include <stdio.h> // standard input and output
#include <bsp.h> // board support package
#include <rtems.h> // RTEMS definitions
#include <rtems/error.h> // RTEMS error definitions
#include "mcf5282.h" // definitions for the MCF5282 (registers and pins used in the program)

// define the argument of task B
rtems_task taskB(
  rtems_task_argument argument
)
{

  // status code for the task
  rtems_status_code sc1;

  // enable read and write for GPIO
  MCF5282_CCM_CCR &= ~MCF5282_CCM_CCR_SZEN;

  // Set GPIO PE2 high to function as output
  // DDRE : Data Direction Register E
  MCF5282_GPIO_DDRE |= MCF5282_GPIO_DDRx(2);

  // Set portE low for digital output
  // PEPAR : Port E Pin Assignment Register
  MCF5282_GPIO_PEPAR &= ~MCF5282_GPIO_PEPAR_PEPA2;

// create an event to sit in the place of an outgoing event when receiving the event from task A
// (this event doesn't do anything but act as a placeholder, as no event is going out from task B)
rtems_event_set EVENT_NULL;

// what the task does
for(;;){
// receive the event from task A
  sc1 = rtems_event_receive(
    RTEMS_EVENT_0, // the event being received
    RTEMS_WAIT, // the task will wait to receive the event
    0, // the interval of the event is set to 0 clock ticks
    &EVENT_NULL // placeholder for an outgoing event
  );
  // error message if the event is not successfully received
  if ( sc1 != RTEMS_SUCCESSFUL ) {
    printf( "Can't receive event: %s\n", rtems_status_text(sc1) ); // if the status code isn't successful, print the error statement
    rtems_task_suspend( RTEMS_SELF ); // suspend the task if the event was not received
  }

    // toggle the state of pin E2 with XOR (i.e. set high if low, or set low if high)
    MCF5282_GPIO_PORTE ^= MCF5282_GPIO_PORTx2;

}
}
