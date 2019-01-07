# TicTacToe_2500A1
Tic tac toe game with smart AI that will never lose (Intermediate Programming course assignment 1)

*Do not use code from this or copy any aspects without explicit permission from creator*

Use the makefile to compile and view the executable file names to actually run the programs

*NOTE: You must run each a1p# in order from 1 to 5*

# tictactoe.c
    Contains all the functions required for the game tic-tac-toe

# a1p1
    Takes single cmd line argument representing an integer board number (us format) and 
    prints out all the info about that board (excluding the strategyfile).
    
# a1p2
    Writes a binary file, named "strategyfile", consisting of exactly 39366 bytes (which should contain 19683 2-byte records).
    Each record will encode the following structure for every possible tic-tac-toe board in order for us=0 to us=19682:
      For now, set best_move to '9' and set the value of winner to ' ' (blank space).

# a1p3
    Takes an integer command-line argument representing the move number and loops over all possible boards.
    
    When it finds a board that matches the move number, the program should determine if
    someone is the winner (according to the winner function you wrote earlier).

    If the game is a win, loss or tie ('2', '1', or '0'), it:
      Sets the "winner" value in the strategy_struct variable to that value,
      Sets the "best_move" value to -1, and
      Save the structure in the appropriate position in the binary file.

    If the game is undetermined (the winner function returns ' ' (blank space)),
    then it looks at all the possible moves that can be made and
    looks at the winner value stored in the file for each of the resulting boards.
    
    It then does the following:
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
    *NOTE: this means to execute a1p3 10 times, each time using the next integer in the set
      (eg. "./a1p3 9", then "./a1p3 8", ..., and finally "./a1p3 0")*
    
    At this point, the AI will have mastered the game of tic-tac-toe and
    incorporated its body of knowledge in the “strategyfile”.
    
# a1p4
    Takes single command line argument representing an integer board number (us format)
    and displays the winner and best_move values from the strategyfile for each board
    as well as all the other information about that board.
    
# a1p5
    ----------------------------- TIC-TAC-TOE GAME -----------------------------
    User can choose to play as 'X' or 'O'. ('X' will always go first.)
    The opponent of the user will be the computer who plays using a created
    strategyfile (thus, it's a simple AI) that will always play optimally.
    Due to this, the computer will be undefeatable because this game is 'solved'.
    Thus, the user will only ever be able to lose or tie when playing.
    ----------------------------------------------------------------------------
