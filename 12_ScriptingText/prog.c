/* COMMENT:: prog, 0.0.1: Fri Dec  4 21:29:40 UTC 2020 */
#include <stdio.h>
#include "outlib.h"

int main(int argc, char *argv[]) {
  int i;
  if ((Count = argc) > 1) {
    output("<INIT>");
    for(i=1; i<argc; i++)
      output(argv[i]);
    output("<DONE>");
  } else
    usage(argv[0]);
  return 0;
}

