// A module for a wordlist ADT

#include <stdbool.h>

// SEASHELL_READONLY

// A word *** only contains lowercase letters ('a'...'z') ***
// an empty string ("") is also considered a word

// The following applies to all functions
// requires: all wordlist parameters are valid (not NULL) 
//           all string parameters are valid (not NULL)
//           all string parameters are words (see above)
// time: (m) is the the length of the word (string) s
//       (n) is the number of characters in all of the words in the wordlist

struct wordlist;

// wordlist_create() creates a new empty wordlist
// effects: allocates memory (must call wordlist_destroy)
struct wordlist *wordlist_create(void);

// wordlist_count(wl) counts how many words are in wl
// time: O(1)
int wordlist_count(const struct wordlist *wl);

// wordlist_add(s, wl) adds the word s to wordlist wl
//   (if it does not already exist in wl)
// effects: may modify wl
// time: O(m)
void wordlist_add(const char *s, struct wordlist *wl);

// wordlist_remove(s, wl) removes the word s from wordlist wl (if it exists)
// effects: may modify wl
// time: O(m)
void wordlist_remove(const char *s, struct wordlist *wl);

// wordlist_lookup(s, wl) determines if wl contains the word s
// time: O(m)
bool wordlist_lookup(const char *s, const struct wordlist *wl);

// wordlist_destroy(wl) frees all memory for wl
// effects: wl is no longer valid
// time: O(n)
void wordlist_destroy(struct wordlist *wl);

// wordlist_print(wl) prints each word in wl in alphabetical order,
//   with each word followed by a newline (e.g., "%s\n")
// note: if the empty string is in wl, it prints an initial blank line
// effects: may produce output
// time: O(n)
void wordlist_print(const struct wordlist *wl);

// wordlist_to_aos(wl) returns an array of strings containing
//   each word in wl in alphabetical order
// notes: returns NULL if wl is empty
//        returns a dynamic array, and each string is dynamically allocated
// effects: allocates memory (caller must free each string and array itself)
// time: O(n)
char **wordlist_to_aos(const struct wordlist *wl);
