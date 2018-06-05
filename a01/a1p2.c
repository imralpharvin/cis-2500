/* a1p2.c
   Code file for Assignment 1 Program 2.
   By:  Ralph Arvin De Castro (rdecastr@uoguelph.ca)
   Student ID:  0923223
 */

#include <stdio.h>
#include "tictactoe.h"

int main( )
{
  int i;
  struct strategy_struct Strategy1 ;
  FILE*fp;
  Strategy1.best_move = -1;
  Strategy1.winner = ' ';

  fp = fopen("strategyfile","wb"); /*Opens strategyfile*/

  for( i=1 ; i <= 19683 ; i++ )  /*Write on strategyfile*/
  {
    fwrite( &Strategy1, sizeof( Strategy1 ), 1, fp );
  }

  fclose( fp ); /*Closes Strategyfile*/

  return 0;
}
