/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 01/24/2017
 * a1p4.c
    Links to "tictactoe.h" for functions about the game.
    Simillar to a1p1.c
    Takes a single command line argument representing an integer board number (us format)
    and displays the winner and best_move values from the strategyfile for each board
    as well as all the other information about that board.
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

  debug2(us);  /* prints all the info for the given board */

  return 0;
}
