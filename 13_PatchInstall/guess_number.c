#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <string.h>
#include <locale.h>
#include "config.h"

#define _(STRING) gettext(STRING)

int main(int argc, char *argv[]) {
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, ".");
  textdomain (PACKAGE);  
  
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

