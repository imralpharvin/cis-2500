/* main.c
   Code Source file for main program.
   By:  Ralph Arvin De Castro (rdecastr@uoguelph.ca)
   Student ID:  0923223
 */

#include "bow.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  struct bag_struct *hamBag = new_bag();
  struct bag_struct *spamBag = new_bag();
  char *hamLabel = "ham";
  char *spamLabel = "spam";

  printf("Hello there!\n");
  printf("This program reads a file and gets words from lines either starting with ham or spam and compare ratios of word frequencies.\n");
  printf("The table below displays significant words which are most indicative of the message type. The columns are in this order: \n\n");
  printf(" Word | Ham Frequency | Spam Frequency | Ham and Spam Ratio | Message Type\n\n");

  read_sms_data( hamBag, hamLabel ); /*Read SMS data with ham label and put all the words in a bag*/
  read_sms_data( spamBag, spamLabel ); /*Read SMS data with spam label and put all the words in a bag*/
  differences( hamBag, spamBag ); /*Find and print differences(frequencies and ratios) between ham and spam bags*/

  printf("\nIf you want to print the words from ham and spam bags, go to main.c and uncomment the prints section.\n");
  printf("Goodbye!\n");
  /*print_bag( hamBag );
  print_bag( spamBag );*/ /*Prints ham and spam bags: Uncomment to print*/

  free_bag( hamBag ); /*Free memory allocated for hambag*/
  free_bag( spamBag ); /*Free memory allocated for spambag*/
  return 0;
}
