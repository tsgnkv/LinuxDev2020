/** @file guess_number.c
 * Main file
 *
 * Guessing number game 
 */

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <string.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."


/**
 * Convert an integer number @p int_number to its roman representation 
 * @param int_number should be a number from range [1..100] 
 * @returns roman string or NULL value
 */
char * int_to_roman(int int_number) {
  return NULL;
}

/**
 * Convert a string @p roman_number to its integer representation 
 * @param roman_number is a string
 * @returns integer value in range [1..100] or -1
 */
int roman_to_int(char *roman_number) {
  return -1;
}

int main(int argc, char *argv[]) {
  setlocale (LC_ALL, "");
  bindtextdomain ("guess_number", LOCALE_PATH);
  textdomain ("guess_number");  
  
  /* Welcome message */
  printf(_("Guess a number from 1 to 100 and I'l try to guess it\n"));

  int low = 0;
  int high = 100;
  int middle;
  char answer[8] = {0}; 
 
  while (low < high) {
    middle = (low + high) / 2;
    
    /* Question */
    printf(_("Is your number greater than %d? Answer %s or %s: "), middle, _("y"), _("n"));
    
    int res = scanf("%s", answer);
    
    if (strcmp(answer, _("y")) == 0) {
      low = middle + 1;
    } else if (strcmp(answer, _("n")) == 0) {
      high = middle;
    }
  }

  /* Answer */
  printf(_("Your number id %d\n"), low);

  return 0;
}

