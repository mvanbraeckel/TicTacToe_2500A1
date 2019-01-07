/*
 * Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
 * 01/21/2018
 * tictactoe.h
    Header file for tictactoe.c
 */

/* Included Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TICTACTOE_H
#define TICTACTOE_H

/* Struct Prototypes */
struct strategy_struct {
    char best_move;
    char winner;
};

/* Function Prototypes */
unsigned short b3tous( char b3[10] );
void b3fromus( char b3[10], unsigned short us );
void boardtob3( char b3[10], char board[60] );
void boardfromb3( char board[60], char b3[10] );
char winner( unsigned short us );
unsigned short next ( unsigned short us, char pos );
char get_move( char b3[10] );
char get_turn( char b3[10] );

void debug ( unsigned short us );
void debug2( unsigned short us );
void get_record( FILE *fp, unsigned short us, struct strategy_struct *record );
void set_record( FILE *fp, unsigned short us, struct strategy_struct record );
void evaluate_move( FILE *fp, unsigned short us, struct strategy_struct *record );

#endif
