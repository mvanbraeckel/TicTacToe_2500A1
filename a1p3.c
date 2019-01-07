/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 01/24/2017
 * a1p3.c
    Links to "tictactoe.h" for functions about the game.

    Takes an integer command-line argument representing the move number and loops over all possible boards.
    When it finds a board that matches the move number, the program should determine if
    someone is the winner (according to the winner function you wrote earlier).

    If the game is a win, loss or tie ('2', '1', or '0'), it should:
      Set the "winner" value in the strategy_struct variable to that value,
      Set the "best_move" value to -1, and
      Save the structure in the appropriate position in the binary file.

    If the game is undetermined (the winner function returns ' ' (blank space)),
    then your program should look at all the possible moves that can be made and
    look at the winner value stored in the file for each of the resulting boards.
    It should then do the following:
       - If there is a move that leads to a board whose "winner" value matches the
         current player’s "turn" (i.e. the current player can make a winning move),
         then set the winner value in the strategy_struct variable to the current player
         and set the "best_move" to whatever move led to that board.
       - If there is no winning move, but there is a tying move, then set the
         winner value in the strategy_struct to '0' (tie) and set the "best_move"
         to whatever move led to that board.
       - If there are no winning moves, and no tying moves, then set the
         winner value to the opponent's character and set the "best_move" to the
         last (highest numbered) legal move.

    Run your program with the command line argument set to 9, 8, 7, 6, 5, 4, 3, 2, 1, 0.
    At this point your program will have mastered the game of tic-tac-toe and
    incorporated its body of knowledge in the “strategyfile”.
 */

#include "tictactoe.h"

int main(int argc, char **argv) {
  int moveNum;
  unsigned short us;
  char b3[10];
  struct strategy_struct strat;
  FILE *fp;

  /* checks that the correct #of command line arguments have been entered */
  if(argc != 2) {
    fprintf(stderr, "Usage: %s <input: int>\n", argv[0]);
    exit(-1);
  }

  moveNum = atoi(argv[1]);

  fp = fopen("strategyfile", "rb+");  /* opens the strategyfile to read and write to */
  if(fp == NULL) {
    fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */
  }

  /* loops through all possible boards */
  for(us = 0; us < 19683; us++) {
    b3fromus(b3, us);
    if(get_move(b3) == moveNum + '0') {
      if(winner(us) != ' ') {       /* there is a winner or a tie (game-over) */
        strat.best_move = -1;
        strat.winner = winner(us);
        set_record(fp, us, strat);

      } else { /* (winner(us) == ' ') */
        evaluate_move(fp, us, &strat);
        set_record(fp, us, strat);
      }
    }
  }

  fclose(fp); /* closes the file after done writing */

  return 0;
}
