/* a1p3.c
   Code file for Assignment 1 Program 3.
   By:  Ralph Arvin De Castro (rdecastr@uoguelph.ca)
   Student ID:  0923223
 */

#include <stdio.h>
#include "tictactoe.h"
#include <string.h>
#include <stdlib.h>

int main( int argc, char **argv )
{
  unsigned short i = 0;
  int number, allmove = 0;
  struct strategy_struct Strategy1;
  FILE*fp;

  if( argc != 2 )
  {
    fprintf( stderr, "Move Number: %s [n]\n", argv[0] );
    exit( -1 );
  }

  number = atoi( argv[1] );
  allmove = number;

  fp = fopen( "strategyfile", "rb+" ); /*Opens strategyfile*/

  if( allmove == 0 ) /*Sets Best move and Winner when board is empty*/
  {
    Strategy1.best_move = 0;
    Strategy1.winner = '0';
    set_record( fp, i, Strategy1 );
  }
  else if( allmove > 0 ) /*Sets Best move and Winner when board has a X or O*/
  {
    for( i = 0 ; i <= 19682 ; i++ )
    {
      if( winner( i ) == '2' || winner( i ) == '1' || winner( i ) == '0' ) /*Sets Best move and Winner when board has a win or tie*/
      {
        Strategy1.best_move =-1;
        Strategy1.winner = winner( i );
        set_record( fp, i, Strategy1 );
      }
      else /*Evaluates best move and winner value when board is in progress*/
      {
        evaluate_move( fp, i, &Strategy1 );
      }
    }
  }
  fclose( fp );
  return 0;
}
