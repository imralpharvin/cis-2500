/* a1p1.c
   Code file for Assignment 1 Program 1.
   By:  Ralph Arvin De Castro (rdecastr@uoguelph.ca)
   Student ID:  0923223
 */

#include <stdio.h>
#include "tictactoe.h"
#include <string.h>
#include <stdlib.h>

int main( int argc , char **argv )
{
  unsigned short us;
  char b3[10], board[60], move, turn, champion, pos = '0';
  int i, number, posint =  0;

  if( argc != 2 )
  {
    fprintf( stderr , "Board Number: %s [n]\n" , argv[0] );
    exit( -1 );
  }

  number = atoi( argv[1] ); /*Sets and prints Board Number*/
  us = number;
  printf( "Board Number: %d\n", us );

  b3fromus( b3, us ); /*Sets and prints Board b3*/
  printf( "Board b3: %s\n", b3 );

  strcpy( board, " X | O |   \n---+---+---\n   |   |   \n---+---+---\n   |   |   \0" ); /*Sets and prints Board*/
  boardfromb3 ( board , b3 );

  move = get_move( b3 ); /*Sets and prints move*/
  printf( "Move: %c\n", move );

  turn = get_turn( b3 ); /*Sets and prints Turn*/
  printf( "Turn: %c\n", turn );

  champion = winner( us ); /*Sets and prints winner*/
  printf( "Winner: %c\n", champion );

  for( i=0 ; i<=8 ; i++ ) /*Sets and prints next board values*/
  {
    us = next( us , pos );
    printf( "%d -> %d\n", i, us );
    posint = pos -'0';
    posint++;
    pos = posint + '0';
    us = number;
  }
  return 0;
}
