/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 01/23/2017
 * a1p1.c
    Links to "tictactoe.h" for functions about the game
    Takes a single command line argument representing an integer board number (us format)
    and prints out all the information about that board (excluding the strategyfile).
 */

#include "tictactoe.h"

int main(int argc, char **argv) {
  /* declare variables */
  unsigned short us;

  /* checks that the correct #of command line arguments have been entered */
  if(argc != 2) {
    fprintf(stderr, "Usage: %s <input: unsigned short>\n", argv[0]);
    exit(-1);
  }
  us = atoi(argv[1]);

  debug(us);  /* prints all the info for the given board */

  return 0;
}
