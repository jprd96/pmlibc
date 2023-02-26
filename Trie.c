#include <stdio.h>
#include <stdlib.h>

typedef struct Trie {
    Trie *children[26];
    int end_word;
} Trie;

/*  This function inserts a new word into the trie.
    ** passes by reference. Need to do so because we initialize the root trie 
    in main like Trie *root = NULL.  */
void insert(Trie *trie, char *word, unsigned int word_len) {
    if(word_len == 0) {
        (*trie).end_word = 1;
        return;
    }
    const unsigned int index = word[0] - 'a';
    if((*trie).children[index] == NULL) {
        Trie *trie2 = NULL;
        trie2 = (Trie*)calloc(1, sizeof(Trie));
        return;
    }
    
}

void search(Trie trie, char *word, unsigned int word_len, Trie **result) {
    ;
}

void print(Trie *trie, char prefix[], unsigned int prefix_len) {
    ;
}


/*  Test suite.  */
int main(void) {
    Trie *trie = NULL;
    trie = (Trie*)calloc(1, sizeof(Trie));
    return 0;
}