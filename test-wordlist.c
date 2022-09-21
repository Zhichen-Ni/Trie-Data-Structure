// This is a simple test client for the wordlist module
// note that it does not test the wordlist_print function

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "wordlist.h"

int main(void) {
  struct wordlist *wl = wordlist_create();
 
  wordlist_add("monkey", wl);
  wordlist_add("monkey", wl);
  wordlist_add("alligator", wl);
  wordlist_add("zebra", wl);
  
  assert(wordlist_count(wl) == 3);
  
  wordlist_add("unicorn", wl);
  wordlist_remove("unicorn", wl);
  
  assert(!wordlist_lookup("unicorn", wl));
  assert(wordlist_lookup("monkey", wl));

  char **aos = wordlist_to_aos(wl);
  assert(!strcmp("alligator", aos[0]));
  assert(!strcmp("zebra", aos[2]));
  for (int i = 0; i < wordlist_count(wl); ++i) {
    free(aos[i]);
  }
  free(aos);
  
  wordlist_destroy(wl);
}
