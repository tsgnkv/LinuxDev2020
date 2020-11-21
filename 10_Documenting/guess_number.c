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
#define RANGE 101


char* roman_table[101] = {
  "",
  "I",
  "II",
  "III",
  "IV",
  "V",
  "VI",
  "VII",
  "VIII",
  "IX",
  "X",
  "XI",
  "XII",
  "XIII",
  "XIV",
  "XV",
  "XVI",
  "XVII",
  "XVIII",
  "XIX",
  "XX",
  "XXI",
  "XXII",
  "XXIII",
  "XXIV",
  "XXV",
  "XXVI",
  "XXVII",
  "XXVIII",
  "XXIX",
  "XXX",
  "XXXI",
  "XXXII",
  "XXXIII",
  "XXXIV",
  "XXXV",
  "XXXVI",
  "XXXVII",
  "XXXVIII",
  "XXXIX",
  "XL",
  "XLI",
  "XLII",
  "XLIII",
  "XLIV",
  "XLV",
  "XLVI",
  "XLVII",
  "XLVIII",
  "XLIX",
  "L",
  "LI",
  "LII",
  "LIII",
  "LIV",
  "LV",
  "LVI",
  "LVII",
  "LVIII",
  "LIX",
  "LX",
  "LXI",
  "LXII",
  "LXIII",
  "LXIV",
  "LXV",
  "LXVI",
  "LXVII",
  "LXVIII",
  "LXIX",
  "LXX",
  "LXXI",
  "LXXII",
  "LXXIII",
  "LXXIV",
  "LXXV",
  "LXXVI",
  "LXXVII",
  "LXXVIII",
  "LXXIX",
  "LXXX",
  "LXXXI",
  "LXXXII",
  "LXXXIII",
  "LXXXIV",
  "LXXXV",
  "LXXXVI",
  "LXXXVII",
  "LXXXVIII",
  "LXXXIX",
  "XC",
  "XCI",
  "XCII",
  "XCIII",
  "XCIV",
  "XCV",
  "XCVI",
  "XCVII",
  "XCVIII",
  "XCIX",
  "C"
};

/**
 * Convert an integer number @p int_number to its roman representation 
 * @param int_number should be a number from range [1..100] 
 * @returns roman string or NULL value
 */
char * int_to_roman(int int_number) {
  if (int_number > 0 && int_number < 101) {
    return roman_table[int_number];
  }
  return NULL;
}

/**
 * Convert a string @p roman_number to its integer representation 
 * @param roman_number is a string
 * @returns integer value in range [1..100] or -1
 */
int roman_to_int(char *roman_number) {
  for (int i = 1; i < RANGE; ++i) {
    if (!strcmp(roman_number, roman_table[i])) {
      return i;
    }
  }
  return -1;
}



int main(int argc, char *argv[]) {
  int ROMAN_MODE = 0;

  setlocale(LC_ALL, "");
  bindtextdomain("guess_number", LOCALE_PATH);
  textdomain("guess_number");

  if (argc == 2 && !strcmp(argv[1], "--help")) {
    printf(_("\
      Guessing number game - guess your number in decimal or roman numbers\n\
      \n\
      Usage: guess_number [OPTIONS]\n\
      \n\
      \t--help\t\tprint this help\n\
      \t-r\t\tenter in roman-number mode\n\
    "));
    return 0;
  }

  if (argc == 2 && !strcmp(argv[1], "-r")) {
    ROMAN_MODE = 1;
  }
  
  /* Welcome message */
  if (ROMAN_MODE) {
    printf(_("Guess a number from I to C and I'l try to guess it\n"));
  } else {
    printf(_("Guess a number from 1 to 100 and I'l try to guess it\n"));
  }
  

  int low = 0;
  int high = 100;
  int middle;
  char answer[8] = {0}; 

  while (low < high) {
    middle = (low + high) / 2;
    
    /* Question */
    if (ROMAN_MODE) {
      printf(_("Is your number greater than %s? Answer %s or %s: "), int_to_roman(middle), _("y"), _("n"));
    } else {
      printf(_("Is your number greater than %d? Answer %s or %s: "), middle, _("y"), _("n"));
    }
    
    
    int res = scanf("%s", answer);
    
    if (strcmp(answer, _("y")) == 0) {
      low = middle + 1;
    } else if (strcmp(answer, _("n")) == 0) {
      high = middle;
    }
  }

  /* Answer */
  if (ROMAN_MODE) {
    printf(_("Your number id %s\n"), int_to_roman(low));
  } else {
    printf(_("Your number id %d\n"), low);
  }
  

  return 0;
}
