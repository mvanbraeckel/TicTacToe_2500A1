/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 01/24/2017
 * a1p2.c
    Links to "tictactoe.h" for functions about the game
    Writes a binary file, named “strategyfile”, consisting of exactly 39366 bytes.
    This file should contain 19683 2-byte records.
    Each record will encode the following structure for every possible
    tic-tac-toe board in order for us=0 to us=19682:
      For now, set best_move to -1 (I did '9') and set the value of winner to ' ' (blank space).
 */

#include "tictactoe.h"

int main() {
  /* declare variables */
  struct strategy_struct strat;
  FILE *fout;
  int i;

  /* init the struct attributes to default values */
  strat.best_move = -1;
  strat.winner = ' ';

  fout = fopen("strategyfile", "wb"); /* opens the strategyfile to write to */
  if(fout == NULL) {
    fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */
  }

  /* loops through and writes 19683 2-byte strategy_struct records to the file */
  for(i = 0; i < 19683; i++) {
    fwrite(&strat, sizeof(struct strategy_struct), 1, fout);
  }

  fclose(fout);                       /* closes the file after done writing */

  return 0;
}
