/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 01/27/2017
 * a1p5.c
    Links to "tictactoe.h" for functions about the game.
    --------------------------- TIC-TAC-TOE GAME ---------------------------
    User can choose to play as 'X' or 'O'. ()'X' will always go first.)
    The opponent of the user will be the computer who plays using a created
    strategyfile (basically simple AI) that will always play optimally.
    Due to this, the computer will be undefeatable because this game is 'solved'.
    Thus, the user will only ever be able to lose or tie when playing.
    ------------------------------------------------------------------------
 */

#include "tictactoe.h"

#define SIZE 42 /* won't accept line of input longer than this -2 for '\n' & '\0' */

int main(int argc, char **argv) {
  /* declare variables */
  char board[60] = "   |   |   \n---+---+---\n   |   |   \n---+---+---\n   |   |   \0"; /* initializes an empty board */
  char username[SIZE], input[SIZE], b3[10];
  char player, cpu, player_move;
  unsigned short us, next_us;
  int game_over, valid_move;
  struct strategy_struct strat;
  FILE *fin;

  /* init variables */
  us = 0;
  next_us = 0;
  player = ' ';
  cpu = ' ';
  player_move = -1;
  game_over = 0;
  valid_move = 0;

  /* get name from user */
  printf("\nSHALL WE PLAY A GAME?\n");
  printf("\nPLEASE ENTER YOUR NAME:  ");

  fgets(username, SIZE, stdin);
  username[strlen(username)-1] = '\0';  /* removes '\n' */

  printf("\nGREETINGS %s\n", username);

  /* loops until valid input is given */
  while(player != 'X' && player != 'O') {
    printf("Which side would you like to play (X/O)?  ");

    /* gets player's symbol choice */
    fgets(input, SIZE, stdin);
    player = input[0];

    if(player != 'X' && player != 'O') {
      /* displays error message */
      printf("\nINVALID: Must choose 'X' or 'O'\n\n");
    }
  }

  /* assign cpu other symbol */
  if(player == 'X') {
    cpu = 'O';
  } else {
    cpu = 'X';
  }
  printf("Ok, you will be %c; I will be %c.\n", player, cpu);

  /* assign the char turn numbers (CPU the other symbol) */
  if(player == 'X') {
    player = '2';
    cpu = '1';
  } else {
    player = '1';
    cpu = '2';
  }

  fin = fopen("strategyfile", "rb");  /* opens the strategyfile to read and write to */
  if(fin == NULL) {
    fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */
  }

  /* continue running until the game ends */
  while(!game_over) {
    /* reset and update variables */
    valid_move = 0;
    us = next_us;
    b3fromus(b3, us);
    boardfromb3(board, b3);
    printf("\n%s\n", board);  /* displays the current board pic */

    /* check if winner has been decided */
    if(winner(us) == ' ') {
      get_record(fin, us, &strat);

      /* check who's turn it is */
      if(get_turn(b3) == cpu) {
        printf("\nMy turn; my move is %d:\n", strat.best_move);
        next_us = next(us, strat.best_move + '0');

      } else {
        /* makes sure move choice is valid */
        while(!valid_move) {
          printf("\nYour turn; choose a move [0-8]: ");

          /* gets player's move choice */
          fgets(input, SIZE, stdin);
          player_move = input[0];

          if(player_move-'0' >= 0 || player_move-'0' <= 8) {  /* must be between [0-8] */
              /* check that the grid spot is available */
              if(next(us, player_move) != 0) {
                valid_move = 1;

              } else {
                valid_move = 0;
              }
          } else {
            valid_move = 0;
          }

          if(valid_move) {
            next_us = next(us, player_move);
          } else {
            /* displays error message */
            printf("\nINVALID: Cannot make your move there.\n");
          }
        } /* end while loop */
      }

    } else {  /* game ends */
      /* check who won */
      if(winner(us) == cpu) {
        printf("\nI won!\n");
      } else if(winner(us) == player_move) {  /* should never occur */
        printf("\nAh, I guess you have somehow managed to best me.\n");
      } else {  /* winner(us) == '0' tied */
        printf("\nThe game is a tie.\n");
      }
      game_over = 1;
    }
  } /* end game_over while loop */

  /* display closing statement */
  printf("\nA STRANGE GAME.\n" \
          "THE ONLY WINNING MOVE IS\n" \
          "NOT TO PLAY.\n\n");

  fclose(fin);
  return 0;
}
