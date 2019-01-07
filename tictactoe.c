/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 01/21/2017
 * tictactoe.c
    Links to "tictactoe.h" header file
    Contains all the functions required for the game tic-tac-toe
    This is kind of like a tictactoe object
 */

#include "tictactoe.h"

/* Converts strings containing base-3 numbers to their integer equivalent as an unsigned short integer */
unsigned short b3tous( char b3[10] ) {
  /* declare variables */
  unsigned short us = 0;
  unsigned short baseVal = 6561;  /* pow(3, 8) */
  int i;

  /* loops through base-3 number changing each char into it's value */
  for (i = 0; i < 9; i++) {
    us += baseVal * (b3[i] - '0');
    baseVal /= 3;
  }
  return us;
}

/* Converts unsigned short integers to null terminated strings of the characters '0', '1', and '2' */
void b3fromus( char b3[10], unsigned short us ) {
  /* declare variables */
  unsigned short holder;
  unsigned short baseVal = 6561;  /* pow(3, 8) */
  int i;

  b3[9] = '\0';                   /* must end the string w/ null */
  for (i = 0; i < 9; i++) {
    holder = us / baseVal;

    /* create base-3 string using val from integer divison*/
    if(holder < 3) {
      b3[i] = holder + '0';       /* turns int into the respective char val */
    } else {
      printf("ERROR: modulus by 3 not equal to 0, 1, or 2\n");
    }

    /* update the new value of what's left of it numerically */
    us -= baseVal * holder;
    baseVal /= 3;
  }
}

/* Converts the C string board representation to a base-3 string */
void boardtob3( char b3[10], char board[60] ) {
  /* declare variables */
  int i, index;

  for(i = 0; i < 9; i++) {
    index = 4*i + 1 + i/3*12;     /* gets the index of the element in the 60 char board */

    /* checks the char on the board and stores respective value in b3 string */
    switch(board[index]) {
      case ' ':
        b3[i] = '0';
        break;
      case 'O':
        b3[i] = '1';
        break;
      case 'X':
        b3[i] = '2';
        break;
      default:
        printf("ERROR: found char other than SPACE, O, or X in tic-tac-toe grid square\n");
    }
  }
}

/* Converts the base-3 string representation back into a C string board */
void boardfromb3( char board[60], char b3[10] ) {
  /* declare variables */
  int i, index;
  strcpy(board, "   |   |   \n---+---+---\n   |   |   \n---+---+---\n   |   |   \0"); /* init an empty board */

  for(i = 0; i < 9; i++) {
    index = 4*i + 1 + i/3*12;     /* gets the index of the element in the 60 char board */

    /* checks the char on the board and stores respective value in b3 string */
    switch (b3[i]) {
      case '0':
        board[index] = ' ';
        break;
      case '1':
        board[index] = 'O';
        break;
      case '2':
        board[index] = 'X';
        break;
      default:
        printf("ERROR: found char other than 0, 1, or 2 in base-3 string\n");
    }
  }
}

/* Takes a board in unsigned short (us) format and determines who the winner of the board is.
   Note: that it is possible to create boards where both X and O win at the same time, e.g. 222000111(3),
   but these boards will not occur in a real game, so you are not required to worry about this case */
char winner( unsigned short us ) {
  /* declare variables */
  char b3[10];
  char moveNum;
  int i;

  b3fromus(b3, us);
  moveNum = get_move(b3);

  /* can't win a game yet unless 3 in a row */
  if(moveNum < 3) {
    return ' ';
  }
  /* check cols and rows for winner*/
  for(i = 0; i < 3; i++) {
    if(b3[i] == b3[i+3] && b3[i] == b3[i+6] && b3[i] != '0') {                  /* checks cols */
      return b3[i];
    } else if(b3[i*3] == b3[i*3+1] && b3[i*3] == b3[i*3+2] && b3[i*3] != '0') { /* checks rows */
      return b3[i*3];
    }
  }
  /* checks both diagonals, and tie, else ' ' for no winner*/
  if(b3[0] == b3[4] && b3[0] == b3[8] && b3[0] != '0') {
    return b3[0];
  } else if(b3[2] == b3[4] && b3[2] == b3[6] && b3[2] != '0') {
    return b3[2];
  } else if(moveNum == '9') {  /* game board is full and no winners, then tie */
    return '0';
  } else {                     /* no winner yet */
    return ' ';
  }
}

/* Determines what the next board looks like if a player places their symbol in a given position.
   Position 0, is the top left, 1 is the top middle, 2 is top right, 3 is middle left, ..., 8 is bottom right.
   If there is already a piece in the given position your function should return the value 0. */
unsigned short next ( unsigned short us, char pos ) {
  /* declare variables */
  char b3[10];
  char turn;

  b3fromus(b3, us);         /* convert to base-3 string so it's easier */
  turn = get_turn(b3);

  /* check which player's turn, and put in the right char into base-3 string */
  if(b3[pos-'0'] != '0') {  /* already piece there */
    return 0;
  } else if(turn == '1') {
    b3[pos-'0'] = '1';
  } else if(turn == '2') {
    b3[pos-'0'] = '2';
  } else {
    printf("ERROR: next(us, pos) messed up\n");
  }

  return b3tous(b3);        /* convert back to unsigned short to return */
}

/* Returns an integer indicating what move of the game it is (a move consists of one action by one player) */
char get_move( char b3[10] ) {
  /* declare variables */
  int i, pieceCount;
  pieceCount = 0;

  /* counts #of pieces */
  for(i = 0; i < 9; i++) {
    if(b3[i] != '0') {
      pieceCount++;
    }
  }
  return pieceCount + '0';
}

/* Returns a character indicating whose turn is it ('2' means X's turn, '1' means O's turn) */
char get_turn( char b3[10] ) {
  /* declare variables */
  char moveNum;
  moveNum = get_move(b3);

  if(moveNum % 2 == 0) {
    return '2'; /* player 1 is X */
  } else {
    return '1'; /* player 2 is O */
  }
}

/* prints all the information about a board (excluding the strategyfile) */
void debug(unsigned short us) {
  char b3[10] = "";
  char board[60] = "";
  int i;

  b3fromus(b3, us);
  boardfromb3(board, b3);

  printf("Board number: %d\n" \
          "Board b3: %s\n" \
          "Board pic:\n%s\n" \
          "Move: %c\n" \
          "Turn: %c\n" \
          "Winner: %c\n", us, b3, board, get_move(b3), get_turn(b3), winner(us));
  for(i = 0; i < 9; i++) {
    printf("%d -> %d\n", i, next(us, i+'0'));
  }
}

/* prints all the information about a board (including the strategyfile) */
void debug2(unsigned short us) {
  struct strategy_struct record;
  FILE *fp;
  char b3[10] = "";
  char board[60] = "";
  int i;

  b3fromus(b3, us);
  boardfromb3(board, b3);

  fp = fopen("strategyfile", "rb");                       /* opens the strategyfile to read from */
  if(fp == NULL) {
    fprintf(stderr, "ERROR: File could not be opened\n"); /* checks if fopen messed up */
  }
  get_record(fp, us, &record);
  fclose(fp);                                             /* closes the file after done reading */

  printf("Board number: %d\n" \
          "Board b3: %s\n" \
          "Board pic:\n%s\n" \
          "Move: %c\n" \
          "Turn: %c\n" \
          "Winner: %c\n" \
          "best_move=%d, winner=%c\n",
          us, b3, board, get_move(b3), get_turn(b3), winner(us),
          record.best_move, record.winner);
  for(i = 0; i < 9; i++) {
    printf("%d -> %d\n", i, next(us, i+'0'));
  }
}

/* uses fseek and fread to move to the correct record and then read it into the record variable */
void get_record( FILE *fp, unsigned short us, struct strategy_struct *record ) {
  fseek(fp, sizeof(struct strategy_struct) * us, SEEK_SET);              /* moves to the correct record */
  fread(record, sizeof(struct strategy_struct), 1, fp); /* reads the correct data into the referenced record variable */
}

/* uses fseek and fwrite to move to the correct record and then overwrite it with a record variable */
void set_record( FILE *fp, unsigned short us, struct strategy_struct record ) {
  fseek(fp, sizeof(struct strategy_struct) * us, SEEK_SET);              /* moves to the correct record */
  fwrite(&record, sizeof(struct strategy_struct), 1, fp);      /* writes the correct data into the file */
}

/* looks at all the possible moves that can be made and looks at the winner value stored in the file
   for each of the resulting boards.  It then writes the best_move and winner value to the strategyfile
   prioritizing wins, then ties, then highest-numbered legal moves when neither a winning nor tying move
   can be made on the player's turn */
void evaluate_move( FILE *fp, unsigned short us, struct strategy_struct *record) {
  /* declare variables */
  int i, found_tie;
  char b3[10];
  unsigned short next_us;
  struct strategy_struct strat;
  char win, turn, temp_pos, legal_move;

  found_tie = 0;  /* init as false */
  temp_pos = 9;   /* the i in the for-loop will always be <9 */

  /* loops through all possible boards from the current one */
  for(i = 0; i < 9; i++) {
    next_us = next(us, i+'0');

    if(next_us != 0) {
      get_record(fp, next_us, &strat);  /* look up the board */
      win = strat.winner;

      b3fromus(b3, us);
      turn = get_turn(b3);

      legal_move = i;

      if(win == turn) {           /* move caused the current player to win */
        record->winner = win;
        record->best_move = i;
        return;

      } else if(win == '0') {     /* move results in tie */
        found_tie = 1;
        if(i < temp_pos) {        /* thus getting the first grid spot available (hi-top-left) */
          temp_pos = i;
        }
      } /* else   no winning or tying moves are using the 'found_tie' int boolean */
    }
  } /* end for loop */

  /* if no winner was found, checks if a tie was found */
  if(found_tie) {
    record->winner = '0';
    record->best_move = temp_pos;

  } else {    /* no win or tie (found_tie == 0) */
    /* check which player's turn it is and sets opponent to winner */
    if(turn == '1') {
      record->winner = '2';
      record->best_move = legal_move;
    } else { /* turn == '2' */
      record->winner = '1';
      record->best_move = legal_move;
    }
  }
}
