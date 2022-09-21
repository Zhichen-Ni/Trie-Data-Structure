///////////////////////////////////////////////////////////////////////////// 
// INTEGRITY STATEMENT (v3)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement:
// https://student.cs.uwaterloo.ca/~cs136/current/assignments/integrity.shtml
/////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with: 

// None 
//  
// Name: Zhichen Ni 
// login ID: z29ni 
///////////////////////////////////////////////////////////////////////////// 

#include "wordlist.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>


// This data structure is only a SUGGESTION
// You may modify it if you wish

struct trienode {
  bool word_end;
  struct trienode **children;
};

struct wordlist {
  struct trienode *root;
  int count;
};

// The following applies to all functions
// requires: all wordlist parameters are valid (not NULL) 
//           all string parameters are valid (not NULL)
//           all string parameters are words (see above)
// time: (m) is the the length of the word (string) s
//       (n) is the number of characters in all of the words in the wordlist


// see wordlist.h for details
struct wordlist *wordlist_create(void) {
  struct wordlist *wdlst = malloc(sizeof(struct wordlist));
  wdlst->count = 0;
  struct trienode *td = malloc(sizeof(struct trienode));
  td->word_end = false;
  struct trienode **child = malloc(sizeof(struct trienode *) * 26);
  for (int i = 0; i < 26; i++) {
    child[i] = NULL;
  }
  td->children = child;
  wdlst->root = td;
  return wdlst;
}

// see wordlist.h for details
int wordlist_count(const struct wordlist *wl) {
  assert(wl);
  return wl->count;
}

// trienode_add(s, td, repeat) adds the word s to trienode td
//   (if it does not already exist in td)
// effects: may modify td
// time: O(m)
void trienode_add(const char *s, struct trienode *td, int *repeat) {
  assert(s);
  if (s[0] == '\0') {
    if (td->word_end == true) {
      *repeat = 1;
    }
    td->word_end = true;
    return;
  }
  int idx = s[0] - 'a';
  if (td->children[idx] == NULL) {
    struct trienode *new = malloc(sizeof(struct trienode));
    new->word_end = false;
    struct trienode **child = malloc(sizeof(struct trienode *) * 26);
    for (int i = 0; i < 26; i++) {
      child[i] = NULL;
    }
    new->children = child;
    td->children[idx] = new;
  }
  trienode_add((s + 1), td->children[idx], repeat);
}

// see wordlist.h for details
void wordlist_add(const char *s, struct wordlist *wl) {
  assert(wl);
  assert(s);
  int repeat = 0;
  trienode_add(s, wl->root, &repeat);
  if (repeat == 0) {
    wl->count++;
  }
}

// trienode_remove(s, td, success) removes the word s 
//    from tirenode td (if it exists)
// effects: may modify td
// time: O(m)
void trienode_remove(const char *s, struct trienode *td, int *success) {
  assert(s);
  if (s[0] == '\0') {
    td->word_end = false;
    *success = 1;
    return;
  }
  int idx = s[0] - 'a';
  if (td->children[idx] == NULL) {
    return;
  }
  trienode_remove((s + 1), td->children[idx], success);
}

// see wordlist.h for details
void wordlist_remove(const char *s, struct wordlist *wl) {
  assert(wl);
  assert(s);
  int success = 0;
  trienode_remove(s, wl->root, &success);
  if (success == 1) {
    wl->count--;
  }
}

// trienode_lookup(s, td) determines if td and the contains the word s
// time: O(m)
bool trienode_lookup(const char *s, struct trienode *td) {
  assert(s);
  if (s[0] == '\0') {
    return td->word_end;
  }
  int idx = s[0] - 'a';
  if (td->children[idx] == NULL) {
    return false;
  }
  return trienode_lookup((s + 1), td->children[idx]);
}

// see wordlist.h for details
bool wordlist_lookup(const char *s, const struct wordlist *wl) {
  assert(wl);
  assert(s);
  return trienode_lookup(s, wl->root);
}

// trienode_destory(td) frees all memory for td
// effects: td is no longer valid
// time: O(n)
void trienode_destory(struct trienode *td) {
  for (int i = 0; i < 26; i++) {
    if(td->children[i] != NULL) {
      trienode_destory(td->children[i]);
    }
  }
  free(td->children);
  free(td);
}

// see wordlist.h for details
void wordlist_destroy(struct wordlist *wl) {
  assert(wl);
  trienode_destory(wl->root);
  free(wl);
}

// trienode_print(td, s) prints each word after td in alphabetical order,
//   with each word followed by a newline (e.g., "%s\n")
// note: if the empty string is after td, it prints an initial blank line
// effects: may produce output
// time: O(n)
void trienode_print(struct trienode *td, char *s) {
  if(td == NULL) {
    return;
  }
  if (td->word_end == true) {
    printf("%s\n", s);
  }
  for (int i = 0; i < 26; i++) {
    if (td->children[i] != NULL) {
      char now = i + 'a';
      int len = strlen(s);
      char *curr = malloc(sizeof(char) * (len + 1 + 1));
      strcpy(curr, s);
      curr[len] = now;
      curr[len + 1] = '\0';
      trienode_print(td->children[i], curr);
    }
  }
  free (s);
}

// see wordlist.h for details
void wordlist_print(const struct wordlist *wl) {
  assert(wl);
  if (wl->count == 0) {
    return;
  }
  char *first = malloc(sizeof(char));
  first[0] = '\0';
  trienode_print(wl->root, first);
}

// trienode_to_aos(td, curr, output, idx) creates an array of strings 
//   containing each word in wl in alphabetical order
// effects: allocates memory (caller must free each string and array itself)
// time: O(n)
void trienode_to_aos(struct trienode *td, char *curr, char **output, int *idx) {
  if (td == NULL) {
    return;
  }
  if (td->word_end == true) {
    int len = strlen(curr);
    char *temp = malloc(sizeof(char) * (len + 1));
    strcpy(temp, curr);
    output[*idx] = temp;
    (*idx)++;
  }
  for (int i = 0; i < 26; i++) {
    if (td->children[i] != NULL) {
      char now = i + 'a';
      int length = strlen(curr);
      char *new = malloc(sizeof(char) * (length + 1 + 1));
      strcpy(new, curr);
      new[length] = now;
      new[length + 1] = '\0';
      trienode_to_aos(td->children[i], new, output, idx);
    }
  }
  free(curr);
}

// see wordlist.h for details
char **wordlist_to_aos(const struct wordlist *wl) {
  assert(wl);
  if (wl->count == 0) {
    return NULL;
  }
  char **output = malloc(sizeof(char *) * wl->count);
  char *first = malloc(sizeof(char));
  first[0] = '\0';
  int idx = 0;
  trienode_to_aos(wl->root, first, output, &idx);
  return output;
}