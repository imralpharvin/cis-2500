/* tictactoe.c
   Code file for TicTaCToe functions.
   By:  Ralph Arvin De Castro (rdecastr@uoguelph.ca)
   Student ID:  0923223
 */

#include <stdio.h>
#include "tictactoe.h"
#include <string.h>
#include <stdlib.h>

/*Converts base 3 number to unsigned short number*/
unsigned short b3tous( char b3[10] )
{
  int j = 0;
  int i;
  int k;
  int value = 1;

  b3[9] = '\0';
  for( i=8; i>=0; i-- )
  {
    k = b3[i] - '0';
    k = k *value;
    j = j + k;
    value = value*3;
  }
  return j;
}

/*Converts unsigned short number to base 3 number*/
void b3fromus( char b3[10], unsigned short us )
{
	int i;

  if( us == 0 )
  {
    for( i=8; i>=0; i-- )
    {
      b3[9] = '\0';
      b3[i] = 0 + '0';
    }
  }

	while( us > 0 )
	{
		b3[9] = '\0';
		for( i=8; i>=0; i-- )
		{
			b3[i] = us % 3;
			b3[i] = b3[i] + '0';
			us = us / 3;
		}
	}
}

/*Converts base 3 number to board*/
void boardfromb3( char board[60], char b3[10])
{
  int i;
  int j;

  for( i=8; i>=0; i-- )
	{
    switch( b3[i] )
    {
      case '0':
      j = i/3;
      board[ ( ( 4 * i ) + 1 + ( 12 * j ) ) ] = ' ';
      break;

      case '1':
      j = i/3;
      board[ ( ( 4 * i ) + 1 + ( 12 * j ) ) ] = 'O';
      break;

      case '2':
      j = i/3;
      board[ ( ( 4 * i ) + 1 + ( 12 * j ) ) ] = 'X';
      break;

      default:
      fprintf( stderr, "Error: bad value in b3\n" );
      exit(-1);
      break;
    }
  }
  printf( "%s\n", board );
}

/*Converts board to b3*/
void boardtob3( char b3[10], char board[60] )
{
  int i;
  int j;

  for( i=8; i>=0; i++ )
  j = i / 3;
	{
    switch( board[ ( ( 4 * i ) + 1 + ( 12 * j ) ) ] )
    {
      case ' ':
      b3[i] = '0';
      break;

      case 'X':
      b3[i] = '2';
      break;

      case 'O':
      b3[i] = '1';
      break;
    }
  }
}

/*Gets move number*/
char get_move( char b3[10] )
{
  int i;
  int move = 9;

  for( i=8; i>=0; i-- )
  {
    if( b3[i] == '0' )
    {
    move--;
    }
  }
  move = move + '0';
  return move;
}

/*Gets turn number*/
char get_turn( char b3[10] )
{
  int i;
  int move = 0;
  char turn;

  for( i=8; i>=0; i-- )
  {
    if( b3[i] == '0' )
    {
    move++;
    }
  }

  if( ( move % 2 ) == 1 )
  {
  turn = '2';
  }
  else if( ( move % 2 ) == 0 )
  {
  turn = '1';
  }

  return turn;
}

/*Gets winner*/
char winner( unsigned short us )
{

  char b3[10];
  char winner;

  b3fromus( b3, us );
  winner = ' ';

  /*All possible winning or tying moves*/
  if( b3[0] == '1' && b3[3] == '1' && b3[6] == '1' )
  {
    winner = '1';
  }
  else if( b3[1] == '1' && b3[4] == '1' && b3[7] == '1' )
  {
    winner = '1';
  }
  else if( b3[2] == '1' && b3[5] == '1' && b3[8] == '1' )
  {
    winner = '1';
  }
  else if( b3[0] == '2' && b3[3] == '2' && b3[6] == '2' )
  {
    winner = '2';
  }
  else if( b3[1] == '2' && b3[4] == '2' && b3[7] == '2' )
  {
    winner = '2';
  }
  else if( b3[2] == '2' && b3[5] == '2' && b3[8] == '2' )
  {
    winner = '2';
  }
  else if( b3[0] == '1' && b3[1] == '1' && b3[2] == '1' )
  {
    winner = '1';
  }
  else if( b3[3] == '1' && b3[4] == '1' && b3[5] == '1' )
  {
    winner = '1';
  }
  else if( b3[6] == '1' && b3[7] == '1' && b3[8] == '1' )
  {
    winner = '1';
  }
  else if( b3[0] == '2' && b3[1] == '2' && b3[2] == '2' )
  {
    winner = '2';
  }
  else if( b3[3] == '2' && b3[4] == '2' && b3[5] == '2' )
  {
    winner = '2';
  }
  else if( b3[6] == '2' && b3[7] == '2' && b3[8] == '2' )
  {
    winner = '2';
  }
  else if( b3[0] == '1' && b3[4] == '1' && b3[8] =='1' )
  {
    winner = '1';
  }
  else if( b3[0] == '2' && b3[4] == '2' && b3[8] =='2' )
  {
    winner = '2';
  }
  else if( b3[2] == '1' && b3[4] == '1' && b3[6] =='1' )
  {
    winner = '1';
  }
  else if( b3[2] == '2' && b3[4] == '2' && b3[6] =='2' )
  {
    winner = '2';
  }
  else if( ( b3[0] == '1'|| b3[0] == '2' ) && (b3[1] == '1' || b3[1] == '2') && ( b3[2] == '1' || b3[2] == '2' ) && ( b3[3] == '1' || b3[3] == '2' ) && ( b3[4] == '1' || b3[4] == '2' ) && ( b3[5] == '1' || b3[5] == '2' ) && ( b3[6] == '1' || b3[6] == '2' ) && ( b3[7] == '1' || b3[7] == '2' ) && ( b3[8] == '1' || b3[8] == '2' ) )
  {
    winner = '0';
  }

  return winner;
}

/*Gets unsigned short value of next picked position*/
unsigned short next( unsigned short us, char pos )
{
  char b3[10];
  char turn;
  int p = 0;

  b3fromus( b3, us );
  turn = get_turn( b3 );
  p = pos - '0';

  if ( b3[p] == '1' || b3[p] == '2' )
  {
    return 0;
  }

  if ( turn == '1' )
  {
    b3[p]= '1';
  }
  else if ( turn == '2' )
  {
    b3[p]= '2';
  }

  us = b3tous( b3 );

  return us;
}

/*Gets best move and winner from strategyfile*/
void get_record( FILE *fp, unsigned short us, struct strategy_struct *record )
{
  fseek( fp, sizeof( struct strategy_struct ) * us , SEEK_SET );
  fread( record, sizeof(struct strategy_struct), 1, fp );
}

/*Sets best move and winner to strategyfile*/
void set_record( FILE *fp, unsigned short us, struct strategy_struct record )
{
  fseek( fp, sizeof( struct strategy_struct ) * us, SEEK_SET );
  fwrite( &record, sizeof( struct strategy_struct ), 1 ,fp );
}

/*Evaluates next moves if game is still in progress*/
void evaluate_move( FILE *fp, unsigned short us, struct strategy_struct *diffrecord )
{
  int i = 0;
  char b3[10];
  int temp_var;
  int win_var;
  int opponent_var;
  int found_winner =0;
  int found_tie = 0;
  int opponent_winner =0;
  int legal_move = 0;
  char opponent = '0';

  fp = fopen( "strategyfile", "rb+" );

  if( get_turn( b3 ) == '1' ) /*Sets opponent number*/
  {
    opponent = '2';
  }
  else if( get_turn( b3 ) == '2' )
  {
    opponent ='1';
  }

  for( i=0; i<=8; i++ ) /*Loops possible values for next turn*/
  {
    if( next( us, i +'0' ) > 0 ) /*Evaluates if position is not taken*/
    {
      b3fromus( b3, us );
      if ( winner( next( us, i + '0' ) ) == get_turn( b3 ) ) /*Evaluates if the position is a winning move*/
      {
        win_var = i;
        found_winner = 1;
      }
      else if ( winner( next( us, i + '0' ) ) == '0' ) /*Evaluates if the position is a tying move*/
      {
        temp_var = i;
        found_tie = 1;
      }
      else if ( winner( next( us, i + '0' ) ) == ' ' ) /*Evaluates if there is no winning or tying move*/
      {
        legal_move = i;
      }
    }
  }

  if( found_winner == 1 ) /*Sets best move and winner if a winning move is found*/
  {
    diffrecord->best_move = win_var;
    diffrecord->winner = get_turn( b3 );
    set_record( fp, us, *diffrecord );
  }
  else /*Sets best move and winner if a winning move is not found*/
  {
    if( found_tie == 1 ) /*Sets best move and winner if a winning move is not found but tying move is found*/
    {
      diffrecord->best_move = temp_var;
      diffrecord->winner = '0';
      set_record( fp, us, *diffrecord );
    }
    else if ( found_tie == 0 ) /*Sets best move and winner if both winning move and tying move are not found*/
    {

      for( i = 8; i >= 0; i-- ) /*Switch values*/
      {
        switch( b3[i] )
        {
          case '1':
          b3[i] = '2';
          break;

          case  '2':
          b3[i] = '1';
          break;
        }
      }
      us = b3tous( b3 );

      for( i = 8; i >= 0; i-- ) /*Checks if switched values has future blocking move*/
      {
        if ( winner( next( us, i + '0' ) ) == get_turn( b3 ) ) /*Determines if there opponent has a winning move*/
        {
          opponent_var = i;
          opponent_winner = 1;
        }
      }

      if( opponent_winner == 1 ) /*Sets best move and winner if there is a blocking move*/
      {
        for( i = 8; i >= 0; i-- ) /*Switches back board*/
        {
          switch( b3[i] )
          {
            case '1':
            b3[i] = '2';
            break;

            case  '2':
            b3[i] = '1';
            break;
          }
        }
        us = b3tous( b3 );
        diffrecord->best_move = opponent_var;
        diffrecord->winner = opponent;
        set_record( fp, us, *diffrecord );
      }
      else if( opponent_winner == 0 ) /*Sets best move and winner if there is no blocking move*/
      {
        for( i=8; i>=0; i-- ) /*Switches back board*/
        {
          switch( b3[i] )
          {
            case '1':
            b3[i] = '2';
            break;

            case  '2':
            b3[i] = '1';
            break;
          }
        }
        us = b3tous( b3 );
        diffrecord->best_move = legal_move;
        diffrecord->winner = opponent;
        set_record( fp, us, *diffrecord );
      }
    }
  }
  fclose( fp );

}
