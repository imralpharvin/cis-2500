#ifndef MYMALLOC_H
#define MYMALLOC_H
#define malloc          mymalloc
#define realloc         myrealloc
#define free            myfree

void *mymalloc( size_t size );
void *myrealloc( void *ptr, size_t size );
void myfree( void *ptr );
#endif
