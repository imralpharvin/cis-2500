/* a1p5.c
   Code file for Assignment 1 Program 5.
   By:  Ralph Arvin De Castro (rdecastr@uoguelph.ca)
   Student ID:  0923223
 */

#include <stdio.h>
#include "tictactoe.h"
#include <string.h>
#include <stdlib.h>

int main()
{
  char name[100], player, computer, board[60], b3[10];
  unsigned short us =0;
  FILE* fp;
  struct strategy_struct Strategy1;
  int pos = 0, playerturn = 0;

  printf( "SHALL WE PLAY A GAME?\n\n" );   /*Prints Introductions*/
  printf( "PLEASE ENTER YOUR NAME:  " );
  scanf( "%s", name );
  printf( "\n\nGREETINGS %s\n", name );
  printf( "Which side would you like to play (X/O)?  " );
  scanf( "%s", &player );
  strcpy( board, " X | O |   \n---+---+---\n   |   |   \n---+---+---\n   |   |   \0" );
  if ( player == 'X' )
  {
    computer = 'O';
  }
  else if ( player == 'O' )
  {
    computer = 'X';
  }
  printf( "Ok, you will be %c; I will be %c.\n\n", player, computer );
  b3fromus( b3, us );
  boardfromb3( board, b3 );

  if( computer == 'O' )   /*If player goes first and computer goes second*/
  {
    printf( "\nYour turn; chose a move [0-8]: " );
    scanf( "%d", &playerturn );
    printf( "\n" );
    pos = playerturn + '0';
    us = next( us, pos );
    b3fromus( b3, us );
    boardfromb3( board , b3 );
  }
  computer = 'X';

  if( computer == 'X' )   /*If computer goes first and player goes second*/
  {
    while( winner( us ) == ' ' ) /*Loops until there is a winner or a tie*/
    {
      fp = fopen( "strategyfile", "rb+" );
      if( ( get_move( b3 ) - '0' ) == 0 )     /*Sets best move and winner for first move*/
      {
        Strategy1.best_move = 8;
        Strategy1.winner = 'O';
        set_record( fp, us, Strategy1 );
      }
      else if ( ( get_move( b3 ) - '0' ) >0 ) /*Sets best move and winner when board is not empty*/
      {
        if( winner( us ) == '2' || winner( us ) == '1' || winner( us ) == '0' ) /*Sets best move and winner when there is a winner*/
        {
          Strategy1.best_move = -1;
          Strategy1.winner = winner( us );
          set_record( fp, us, Strategy1 );
        }
        else /*Sets best move and winner when game is in progress*/
        {
          evaluate_move( fp, us, &Strategy1 );
        }
      }

      get_record( fp, us, &Strategy1 ); /*Gets best move and winner from strategyfile*/

      printf( "\nMy turn; my move is %d: \n\n", Strategy1.best_move ); /*Prints computer's move*/
      pos = Strategy1.best_move + '0';
      us = next( us, pos );
      b3fromus( b3, us );
      boardfromb3( board, b3 );

      if( winner( us ) == ' ' ) /*Prints player's move*/
      {
        printf( "\nYour turn; chose a move [0-8]: " );
        scanf( "%d", &playerturn );
        printf( "\n" );
        pos = playerturn + '0';
        us = next( us, pos );
        b3fromus( b3, us );
        boardfromb3( board, b3 );
      }
      fclose( fp );
    }
  }

  if( winner( us ) == '2' || winner( us ) == '1' ) /*Prints Ending Credits*/
  {
    printf( "\nI won!\n" );
  }
  else if( winner(us) == '0' )
  {
    printf( "\nThis game is a tie!\n" );
  }
  printf( "\nA STRANGE GAME.\nTHE ONLY WINNING MOVE IS\nNOT TO PLAY.\n" );

  return 0;
}
