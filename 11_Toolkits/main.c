#include <stdio.h>
#include <glib.h>

const int MAX_LENGTH = 80;
const char* DELIMETER  = " ";

gboolean finder(gpointer key, gpointer value, gpointer word) {
  return !g_ascii_strcasecmp(key, word);
}

gint compare_function(gconstpointer a, gconstpointer b, gpointer counter) {
  gpointer a_ptr = g_hash_table_find(counter, (GHRFunc)finder, (gpointer)a);
  gpointer b_ptr = g_hash_table_find(counter, (GHRFunc)finder, (gpointer)b);

  return *(gint* )b_ptr - *(gint* )a_ptr;
}

void print(gpointer word, gpointer counter) {
  gpointer count = g_hash_table_find(counter, (GHRFunc)finder, word);
  printf("%s\t%d\n", (char* )word, *(gint* )count);
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Error: Usage %s filename\n", argv[0]);
    return 1;
  }

  FILE* file = fopen(argv[1], "r");

  if ((file = fopen(argv[1], "r")) == NULL) {
    printf("Error: Can't open file %s\n", argv[1]);
    return 1;
  }

  GHashTable* counter = g_hash_table_new(g_str_hash, g_str_equal);
  
  gchar line[MAX_LENGTH + 1];

  while (fgets(line, MAX_LENGTH + 1, file)) {
    line[strlen(line) - 1] = '\0';
    gchar** words = g_strsplit(line, DELIMETER, -1);
    for (int i = 0; words[i]; ++i) {
      gpointer item_ptr = g_hash_table_find(counter, (GHRFunc)finder, words[i]);
      if (item_ptr) {
        // find key
        (*(gint *)item_ptr)++;
      } else {
        // not find key
        gint* tmp = g_new(gint, 1);
        *tmp = 1;
        gchar* strtmp = g_strdup(words[i]);
        g_hash_table_insert(counter, strtmp, tmp);
      }
    }
    g_strfreev(words); 
  }

  GList* sorted_words = g_hash_table_get_keys(counter);
  sorted_words = g_list_sort_with_data(sorted_words, (GCompareDataFunc)compare_function, counter);

  g_list_foreach(sorted_words, print, counter);

  g_list_free(sorted_words);
  g_hash_table_destroy(counter);
  return 0;
}