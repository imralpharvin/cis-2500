/* memcheck.c
   Code Source file for functions.
   By:  Ralph Arvin De Castro (rdecastr@uoguelph.ca)
   Student ID:  0923223
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Memcheck main*/
int memcheck_main( );
char *stdrup2( char *str );

/*Structure for mem struct*/
struct mem_struct
{
  void *memptr;
  char *file;
  int line;
  struct mem_struct *next;
};

void print_list( struct mem_struct* head );

struct mem_struct *head = NULL; /*Declaring global variable to NULL*/

/*Main function with memcheck main called*/
int main( )
{
  memcheck_main( );

  print_list( head );
  return 0;
}

/*Strdup2 pseduo function*/
char *strdup2( char *str )
{
  char *new;
  new = malloc( strlen( str )+1 );
  if ( new )
    {
    strcpy( new, str );
    }
  return new;
}

/*Memcheck free*/
void memcheck_free( void *ptr, char *file, int line )
{
  struct mem_struct **dptr;
  struct mem_struct *temp;

  for( dptr = &head; *dptr; dptr = &( *dptr )->next )
  {
    if( ( *dptr )->memptr == ptr )
    {
      free( ptr );
      temp = *dptr;
      *dptr = ( *dptr )->next;
      free( temp );

      return;
    }
  }

  printf( "memcheck error:  attempting to free memory address %p in file \"%s\", line %d.\n", ptr, file , line );
}

/*Memcheck malloc*/
void *memcheck_malloc( size_t size, char *file, int line )
{
  struct mem_struct *newlist;
  void *temp;

  temp = malloc( size );

  newlist = malloc( sizeof( struct mem_struct ) );
  newlist->memptr = temp;
  newlist->file = strdup2( file );
  newlist->line = line;
  newlist->next = head;

  head = newlist;

  return temp;
}

/*Memcheck Realloc*/
void *memcheck_realloc( void *ptr, size_t size, char *file, int line )
{
  struct mem_struct **dptr;
  void *temp;

  for( dptr = &head; *dptr; dptr = &( *dptr )->next )
  {
    if( ( *dptr )->memptr == ptr )
    {
      temp = realloc( ptr, size );
      ( *dptr )->memptr = temp;
      ( *dptr )->file = strdup2( file );
      ( *dptr )->line = line;
      return temp;
    }
  }
  temp = memcheck_malloc( size, file, line );

  return temp;
}

/*Memcheck Calloc*/
void *memcheck_calloc( size_t nmemb, size_t size, char *file, int line )
{
  struct mem_struct *newlist;
  void *temp;

  temp = calloc( nmemb, size );

  newlist = malloc( sizeof( struct mem_struct ) );
  newlist->memptr = temp;
  newlist->file = strdup2( file );
  newlist->line = line;
  newlist->next = head;

  head = newlist;

  return temp;
}

/*Print List*/
void print_list( struct mem_struct *head )
{
  while( head != NULL )
  {
    printf( "memcheck error:  memory address %p which was allocated in file \"%s\", line %d, was never freed\n", head->memptr, head->file, head->line );
    head = head->next;
  }
}
