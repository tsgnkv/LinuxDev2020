#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>

#define ESC_KEY 27
#define SPACE_KEY 32

#define OFFSET 1

void show_file(const char *filename, char **data, int size) {
    
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    printw("File: %s; size: %d", filename, size);
    refresh();

    WINDOW *frame = newwin(LINES - 2 * OFFSET , COLS - 2 * OFFSET, OFFSET, OFFSET);
    box(frame, 0, 0);
    touchwin(frame);
    wrefresh(frame);
    

    WINDOW *text_window = newwin(LINES - 2 * (OFFSET + 1), COLS - 2 * (OFFSET + 1), OFFSET + 1, OFFSET + 1);
    keypad(text_window, TRUE);
    scrollok(text_window, TRUE);

    int i = 0;

    while ((i < size) && (i < LINES - 2 * (OFFSET + 1) - 1)) {
        wprintw(text_window, "%3d: %s", i + 1, data[i]);
        i++;
    }

    wrefresh(text_window);
    
    int c = wgetch(text_window);

    while (c != ESC_KEY) {
        if (c == SPACE_KEY) {
            int j = 0;
            werase(text_window);
            while ((i < size) && (j < LINES - 2 * (OFFSET + 1) - 1)) {
                move(OFFSET + 2, OFFSET + 2);
                wprintw(text_window, "%3d: %s", i + 1, data[i]);
                i++;
                j++;
            }
            wrefresh(text_window);
        }
        c = wgetch(text_window);
    }

    endwin();
}

int main(int argc, char** argv) {

    if (argc != 2) {
        return -1;
    }

    const char *filename = argv[1];

    FILE *fp = fopen(filename, "r");

    if (!fp) {
        return -1;
    }

    char cr;
    size_t lines = 0;

    while (cr != EOF) {
        if (cr == '\n') lines++;
        cr = getc(fp);
    }
    
    rewind(fp);

    char *data[lines];
    size_t n;

    for (size_t i = 0; i < lines; i++) {
        data[i] = NULL;
        size_t n = 0;
        getline(&data[i], &n, fp);
    }

    fclose(fp);

    show_file(filename, data, lines);
    
    for (size_t i = 0; i < lines; i++) {
        free(data[i]);
    }
    
    return 0;

}
