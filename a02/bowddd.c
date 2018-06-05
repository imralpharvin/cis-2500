while (*line)  /* while sentence doesn't point to the '\0' character at the end of the string */
{

  word = get_word( &sentence );  /* this will allocate memory for a word */
  wordandcount = new_word_count(word);

  if(wordandcount->word != NULL)
  {
    add_word(bigbag, word);
    /*printf( "word = \"%s\"; sentence = \"%s\"\n", wordandcount->word, sentence );*/ /* print out to see what's happening */
    /*print_word_count(wordandcount);*/
  }


  free(wordandcount);

  /*free_word(word);*/
}
}
