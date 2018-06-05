/* bow.c
   Code Source file for functions.
   By:  Ralph Arvin De Castro (rdecastr@uoguelph.ca)
   Student ID:  0923223
 */

#include "bow.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

/*Points to a bag struct and declare its members: bag, bag size and total words*/
struct bag_struct *new_bag( )
{
  struct bag_struct *baggy;

  baggy = malloc( sizeof( struct bag_struct ) );
  baggy->bag = NULL;
  baggy->bag_size = 0;
  baggy->total_words = 0;

  return baggy;
}

/*Searches the bag for the right position of the new word in the bag*/
int bagsearch( struct bag_struct *bow, char *word )
{
  struct bag_struct *halfBag;
  int halfIndex;
  int cmp;
  int pos;

  halfIndex = ( bow->bag_size ) / 2 ;
  halfBag = new_bag( );
  halfBag->bag_size =  halfIndex;

  if (bow->bag_size == 0) /*When bag is empty*/
  {
    return 0; /*Position of first word will always be at index 0*/
  }
  else if( bow->bag_size > 0 ) /*When bag is not empty*/
  {
    cmp = strcmp( bow->bag[halfIndex].word, word ); /*Compares middle word and new word*/
    if( cmp < 0 ) /*Middle word > new word alphabetically */
    {
      if( bow->bag_size % 2 == 0 )  /*When bagsize is even*/
      {
        halfBag->bag = bow->bag + halfIndex; /*New bag will be the second half of original bag*/
        pos = bagsearch( halfBag, word );
        return pos + halfIndex; /*Recursion: searches bag until position is found*/
      }
      else if( bow->bag_size % 2 == 1 ) /*When bagsize is odd*/
      {
        halfBag->bag = bow->bag + halfIndex +1; /*New bag will be the (second half + 1 )of original bag*/
        pos = bagsearch( halfBag, word );
        return pos + halfIndex + 1; /*Recursion*/
      }
    }
    else if( cmp >= 0 ) /*Middle word <= new word alphabetically */
    {
      halfBag->bag = bow->bag; /*New bag will be the first half of original bag*/
      pos = bagsearch( halfBag, word );
      return pos; /*Recursion*/
    }
  }
  return 0;
}

/*Gets words from a string pointer and takes out non letters*/
char *get_word( char **string_ptr )
{
  char *word;
  int counter = 0;

  word = malloc( 924 ); /*allocate memory for word*/

  while( is_letter( **string_ptr ) != 1 && ( **string_ptr != '\0' ) ) /*skips non past letters*/
  {
    *string_ptr += sizeof( char );
  }

  while( is_letter( **string_ptr ) == 1 ) /*takes all letters until a non letter appears*/
  {
    word[counter] = **string_ptr;
    *string_ptr += sizeof( char );
    word[counter] = tolower( word[counter] );
    counter++;
  }

  word[counter] = '\0'; /*puts a null terminator to the word*/

  if( word[0] =='\0' ) /*if word is invalid, then return NULL*/
  {
    return NULL;
  }

  word = realloc( word, strlen( word ) + 1 ); /*realloc memory for word*/
  return word;
}

/*Points to word count struct and declare its members: word and count*/
struct word_count_struct *new_word_count( char *word )
{
  struct word_count_struct *ptr;

  ptr = malloc( sizeof( struct word_count_struct ) );
  ptr->word = word;
  ptr->count = 1;

  return ptr;
}

/*Adds the new word to the bag*/
void add_word( struct bag_struct *bow, char *word )
{
  struct word_count_struct *word_count;
  int pos;
  int sizeofWCS = sizeof( struct word_count_struct );

  word_count = new_word_count( word ); /*puts the word in the wordcout struct*/
  pos = bagsearch( bow, word ); /*gets position of new word from bagsearch*/

  if( bow->bag_size == 0 ) /*puts first word at index 0*/
  {
    bow->bag_size++;
    bow->bag = realloc( bow->bag, sizeofWCS* ( ( bow->bag_size ) + 1 ) );
    memcpy( &( bow->bag[pos] ), word_count, sizeofWCS );
  }
  else if( pos < bow->bag_size ) /*puts new word to appropriate position given by bagsearch function */
  {
    if( strcmp( bow->bag[pos].word, word ) != 0 ) /*put new word when word is new*/
    {
      bow->bag_size++; /*increase bag size by 1*/
      bow->bag = realloc( bow->bag, sizeofWCS * ( ( bow->bag_size ) + 1 ) );
      memcpy( &( bow->bag[pos+1] ), &( bow->bag[pos] ), sizeofWCS * ( bow->bag_size - pos ) );
      memcpy( &( bow->bag[pos] ), word_count, sizeofWCS );
    }
    else if( strcmp( bow->bag[pos].word, word ) == 0 ) /*doesn't put new word if it is already in bag*/
    {
      bow->bag[pos].count++;  /*increase word count by 1*/
    }
  }
  else if( pos == bow->bag_size ) /*puts word to the last index when word is the last word alphabetically*/
  {
    if( strcmp( bow->bag[pos-1].word, word ) != 0 ) /*put new word when word is new*/
    {
      bow->bag_size++;
      bow->bag = realloc( bow->bag, sizeofWCS * ( ( bow->bag_size ) + 1 ) );
      memcpy( &( bow->bag[pos+1] ), &( bow->bag[pos] ), sizeofWCS* ( bow->bag_size - pos ) );
      memcpy( &( bow->bag[pos] ), word_count, sizeofWCS );
    }
    else if( strcmp( bow->bag[pos].word, word ) == 0 ) /*doesn't put new word if it is already in bag*/
    {
      bow->bag[pos].count++; /*increase word count by 1*/
    }
  }
  bow->total_words++; /*increase total words by 1*/
}

/*Adds words from a line in the bag*/
void add_text( struct bag_struct *bow, char *line )
{
  char *word;
  struct word_count_struct *word_count;
  while( *line )  /* while sentence doesn't point to the '\0' character at the end of the string */
  {
    word = get_word( &line );  /* gets word from a line */
    word_count = new_word_count( word ); /*puts word in a struct */
    if( word_count->word != NULL )
    {
      add_word( bow, word ); /*Adds words to the bag*/
    }
    free( word_count ); /*free memory allocated for word count struct*/
  }
}

/*Reads a file and put all the words in a bag*/
void read_sms_data( struct bag_struct *bow, char *label )
{
  FILE *fp;
  char text[924];
  char *firstWord;

  fp = fopen( "SMSSpamCollection", "rb" ); /*open file*/
  if( fp == NULL )
  {
    printf( "Could not open file" ); /*warning if file is not working*/
  }

  while( fgets( text, 924, fp ) != NULL ) /*loop lines until end of file*/
  {
    firstWord = hamOrSpam( bow, text ); /*detect if first word of the line is ham or spam*/
    if( strcmp( firstWord, label ) == 0 ) /*if firstWord is the same as the label then add the words in that line*/
    {
      if( strcmp( label, "ham" ) == 0 ) /*when label is ham*/
      {
        add_text( bow, text + 4 ); /*start adding text after ham\t */
      }
      else if( strcmp( label, "spam" ) == 0 ) /*when label is spam*/
      {
        add_text( bow, text + 5 ); /*start adding text after spam\t */
      }
    }
  }
  fclose( fp ); /*close file*/
}

void differences( struct bag_struct *ham, struct bag_struct *spam )
{
  int j = 0;
  int k = 0;
  double hamRatio; /*frequency of a ham word/total words*/
  double spamRatio; /*frequency of a spam word/total words*/

  while( j < ham->bag_size && k < spam->bag_size ) /*loop until all words from both bags are compared*/
  {
    if( strcmp( ham->bag[j].word, spam->bag[k].word ) < 0 ) /*ham word < spam word alphabetically*/
    {
      hamRatio =( double )ham->bag[j].count /( double )ham->total_words;
      spamRatio =( double )1 /( double )spam->total_words;
      print_differences( ham, spam, hamRatio, spamRatio, j, k ); /*calculate and print significant ratios of frequencies*/
      j++; /*go the next ham word*/
    }
    else if( strcmp( ham->bag[j].word, spam->bag[k].word ) > 0 ) /*ham word > spam word alphabetically*/
    {
      hamRatio =( double )1 /( double )ham->total_words;
      spamRatio =( double )spam->bag[k].count /( double )spam->total_words;
      print_differences( ham, spam, hamRatio, spamRatio, j, k ); /*calculate and print significant ratios of frequencies*/
      k++; /*go the next spam word*/
    }
    else if( strcmp( ham->bag[j].word, spam->bag[k].word ) == 0 ) /*same word*/
    {
      hamRatio =( double )ham->bag[j].count/( double )ham->total_words;
      spamRatio =( double )spam->bag[k].count/( double )spam->total_words;
      print_differences( ham, spam, hamRatio, spamRatio, j, k ); /*calculate and print significant ratios of frequencies*/
      j++; /*go the next ham word*/
      k++; /*go the next spam word*/
    }
  }
}

/********************************HELPER FUNCTIONS*********************************/
/*Detect if letter or non letter*/
int is_letter( char character )
{
  if( isalpha( character ) )
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/*Prints word and its count*/
void print_word_count( struct word_count_struct *word_count )
{
  printf( "%s: %d\n",word_count->word, word_count->count );
}

void print_bag( struct bag_struct *word_count )
{
  int counter = 0;
  for( counter = 0; counter < word_count->bag_size; counter++ )
  {
    printf( "%d ", counter );
    print_word_count( ( word_count->bag )+counter );
  }
  printf( "Total Words: %d\n\n",word_count->total_words );
}

/*Free memory allocated for bag*/
void free_bag( struct bag_struct *bow )
{
  free( bow );
}

/*Detect if firstword is ham or spam in the line*/
char *hamOrSpam( struct bag_struct *bow, char *line )
{
  char *firstword;

  firstword = get_word( &line );
  return firstword;
}

/*Prints significant ratios between ham and spam frequencies*/
void print_differences( struct bag_struct *ham, struct bag_struct *spam, double hamRatio, double spamRatio, int j, int k )
{
  double bothRatio;
  if( hamRatio > 0.005 || spamRatio >0.005 )
  {
    bothRatio = hamRatio/spamRatio;
    if( bothRatio < 1 )
    {
      bothRatio = spamRatio/hamRatio;
    }
    if( bothRatio > 2 )
    {
      if( spamRatio > hamRatio )
      {
      printf( "%20s %8.6f %8.6f %10.6f spam\n",spam->bag[k].word, hamRatio, spamRatio, bothRatio );
      }
      else if( spamRatio < hamRatio )
      {
      printf( "%20s %8.6f %8.6f %10.6f ham\n",ham->bag[j].word, hamRatio, spamRatio, bothRatio );
      }
    }
  }
}
