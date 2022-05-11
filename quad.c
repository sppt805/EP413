/**
Lab 1 - quad.c

Spencer Thiessen, spt805
Meghan Brehon, meb369

Created September 3/21
Last Modified: September 8/21

About: This file uses a main routine which takes 3 floating points
and determines the appropriate roots associated with the quadratic equation.
**/

#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <complex.h>

/*
Title: Quadratic

Description: This function can take in 3 parameters of double-precision floating point numbers
             From a quadratic function and calculates the roots of the expression, including
             complex roots then prints the answer to the console to 5 significant figures
*/
void quadratic(float a, float b, float c){
  // variables to store final root values
  float ans1;
  float ans2;
  float rad; // value under radical
  // Calculating expression under the radical
  rad = pow(b,2) - 4*a*c;

  // If statement to handle complex roots
  // This if statement determines if the given coefficients will produce complex roots
  // complex if value under radical is negative
  if(rad < 0){
    float denom; // variable for the denominator in quadratic function
    denom = 2 * a; // calculate denominator
    float imag; // variable for imaginary part of complex roots
    imag = sqrt(-1*rad) / denom; // calculates the imaginary part of the root, as if real
    float real; // real part of complex roots
    real = -b / denom; // calculate real part

    // Print the complex roots to the console
    printf("\nRoots are: %.4e + %.4e i, %.4e - %.4e i \n", real, imag, real, imag);
  }
  // If the value under the radical is not negative, no complex root will be statement
  // and calculation can be done normally
  else {
    // variables to store noncomplex roots
    ans1 = (-b + sqrt(rad)) / 2*a;
    ans2 = (-b - sqrt(rad)) / 2*a;
    // Print the noncomplex roots to the console
    printf("\nRoots are: %.4e %.4e \n", ans1, ans2);
  }
}

/*
Title: main function

Description: This main function asks the user to input 3 double-precision floating numbers
             pertaining to 3 coefficients of a quadratic function then calls on 'Quadratic' subroutine
             to calculate the complex or noncomplex roots
*/
int main(void){
  // Variables to store coefficients
  float a;
  float b;
  float c;
  // Prompt user for 3 double precision floating points
  printf("Enter 3 coefficients that are double-precision floating point numbers:\n");
  // Takes user input and assigns the inputs to a, b, c
  scanf("%f %f %f", &a, &b, &c);
  // Call on quadratic to calculate and print the roots
  quadratic(a, b, c);

  return 0; // standard return 0
}
