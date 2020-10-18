#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include <pcre2.h>

#include "config.h"

#define DX 3
#define ONLELINE 3
#define MAXSTR 80

int main() {
  setlocale(LC_ALL, "");
  WINDOW *winPATTERN, *winSUBJECT, *winOUTPUT;
  char inPATTERN[MAXSTR], inSUBJECT[MAXSTR];

  int c = 0;
  int half;

  initscr();
  cbreak();
  printw("Input:");
  refresh();

  half = (COLS - 2 * DX) / 2;

  winPATTERN = newwin(ONLELINE, half, DX, DX);
  winSUBJECT = newwin(ONLELINE, half, DX, DX + half);
  winOUTPUT = newwin(LINES - ONLELINE - DX * 2, (COLS - 2 * DX), DX + ONLELINE, DX);

  keypad(winPATTERN, TRUE);
  keypad(winSUBJECT, TRUE);
  scrollok(winOUTPUT, TRUE);

  box(winPATTERN, 0, 0); wrefresh(winPATTERN);
  box(winSUBJECT, 0, 0); wrefresh(winSUBJECT);
  box(winOUTPUT, 0, 0); wrefresh(winOUTPUT);

  wmove(winOUTPUT, 1, 0);

  pcre2_code *re;
  PCRE2_SPTR pattern;
  PCRE2_SPTR subject;

  int errnum;
  int i, rc;

  PCRE2_SIZE erroffs;
  PCRE2_SIZE *ovector;
  PCRE2_SIZE subject_length;

  do {
    box(winPATTERN, 0, 0);
    mvwgetnstr(winPATTERN, 1, 1, inPATTERN, MAXSTR);
    werase(winPATTERN);

    box(winSUBJECT, 0, 0);
    mvwgetnstr(winSUBJECT, 1, 1, inSUBJECT, MAXSTR);
    werase(winSUBJECT);

    pcre2_match_data *match_data;
    pattern = (PCRE2_SPTR)inPATTERN;
    subject = (PCRE2_SPTR)inSUBJECT;
    subject_length = (PCRE2_SIZE)strlen((char *)subject);

    wprintw(winOUTPUT, "\n  '%s' : '%s'\n", inPATTERN, inSUBJECT);

    #ifdef WITHOUT_UTF
      re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &errnum, &erroffs, NULL);
    #else
      re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP, &errnum, &erroffs, NULL);
    #endif

    if (re == NULL) {
      PCRE2_UCHAR buffer[256];
      pcre2_get_error_message(errnum, buffer, sizeof(buffer));
      wprintw(winOUTPUT, "PCRE2 compilation failed at offset %d: %s\n", (int)erroffs, buffer);
    }

    match_data = pcre2_match_data_create_from_pattern(re, NULL);
    rc = pcre2_match(re, subject, subject_length, 0, 0, match_data, NULL);

    if (rc < 0) {
      switch(rc) {
      case PCRE2_ERROR_NOMATCH:
        wprintw(winOUTPUT, "    No match\n");
        break;
      default:
        wprintw(winOUTPUT, "    Matching error %d\n", rc);
      }
    }

    ovector = pcre2_get_ovector_pointer(match_data);

    for (i = 0; i < rc; i++) {
      wprintw(winOUTPUT, "  %2ld: %.*s\n", ovector[2*i], (int)(ovector[2*i+1] - ovector[2*i]), subject + ovector[2*i]);
    }

    pcre2_match_data_free(match_data);
    pcre2_code_free(re);
    box(winOUTPUT, 0, 0); wrefresh(winOUTPUT);
    
  } while(*inPATTERN);

  endwin();
  return 0;
}
