#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Variable "data" makes it easier to print the trie.  */
typedef struct Trie {
    char data;
    struct Trie *children[26];
	int end;
} Trie;

/*  Insert notes.  */
Trie *init(char data) {
    Trie *root = (Trie*)malloc(sizeof(Trie));
    for (int i = 0; i < 26; i++) {
        root->children[i] = NULL;
    }
    root->data = data;
    root->end = 0;
    return root;
}

/*  Insert notes.  */
Trie *getNode(Trie *trie, char c) {
    int idx = c - 97;
    Trie* next = trie->children[idx];
    return next;
}

/*  Insert notes.  */
void addNode(Trie *trie, char c, Trie *newNode) {
    int idx = c - 97;
    trie->children[idx] = newNode;
    return;
}

/*  Insert notes.  */
void insertHelper(Trie *trie, int idx, char *word, int wordSize) {
    if (idx == wordSize) {
        trie->end = 1;
        return;
    }
    if(getNode(trie, word[idx]) == NULL) {
        addNode(trie, word[idx], init(word[idx]));
    }
    return insertHelper(getNode(trie, word[idx]), idx + 1, word, wordSize);

}

/*  This function inserts a new word into the trie.
    ** passes by reference. Need to do so because we initialize the root trie 
    in main like Trie *root = NULL.  */
void insert(Trie *trie, char *word) {
    insertHelper(trie, 0, word, strlen(word));
    return;
}

/*  Insert notes.  */
int searchHelper(Trie *trie, int idx, char *word, int wordSize) {
    if(idx == wordSize) {
        return trie->end;
    }
    if(getNode(trie, word[idx]) == NULL) {
        return 0;
    }
    return searchHelper(getNode(trie, word[idx]), idx + 1, word, wordSize);
}

/*  Insert notes.  */
int search(Trie *trie, char *word) {
    return searchHelper(trie, 0, word, strlen(word));
}

/*  Insert notes.  */
int startsWithHelper(Trie *trie, int idx, char *prefix, int prefixSize) {
    if(idx == prefixSize) {
        return 1;
    }
    if(getNode(trie, prefix[idx]) == NULL) {
        return 0;
    }
    return startsWithHelper(getNode(trie, prefix[idx]), idx + 1, prefix, prefixSize);
}

/*  Insert notes.  */
int startsWith(Trie *trie, char *prefix) {
    return startsWithHelper(trie, 0, prefix, strlen(prefix));
}

/*  This function prints the trie.
    Do nothing if the trie is empty.   */
void printTrie(Trie *trie) {
    if(trie == NULL) {
        return;
    }
    Trie *temp = trie;
    if(temp->data != '\0') {
        printf("%c -> ", temp->data);
    }
    for(int i = 0; i < 26; i++) {
        printTrie(temp->children[i]); 
    }
}

// void printWordsInTrie(char **wordsCopy, int n) {
//     for(int i = 0; i < n; i++) {
//         printf("--> %s\n", wordsCopy[i]);
//     }
// }
/*  This function deletes the entire trie.
    Do nothing if the trie is empty. Then recursively free each node.  */
void deleteTrie(Trie *trie) {
    if(trie == NULL) {
        return;
    }    
    for(char i = 97; i < 123; i++) {
        deleteTrie(getNode(trie, i));
    }
    free(trie);
    return;
}

/*  Test suite.  */
int main(void) {
    int n;
    printf("How many words do you want to add to the trie? ");
	scanf("%d", &n);

    Trie *trie = init('\0');
    char **words;
    char **wordsCopy;
    words = malloc(n*sizeof(char*));

    printf("Enter %d words: ", n);
    for(int i = 0; i < n; i++) {
        words[i] = malloc(50*sizeof(char));
        scanf("%s", words[i]);
        insert(trie, words[i]);
        printf("-> inserted %s\n", words[i]);
    }

    wordsCopy = words;
    printTrie(trie);

    while(1) {
        int option;
        printf("\n==========================================================\n");
        printf("Choose an operation: \n");
        printf("1. Add a word\n"); 
        printf("2. Search for a word\n");
        printf("3. Check if any word contains a prefix\n");
        printf("4. Print the trie\n");
        printf("5. Exit\n");
        printf("Your choice: ");
        scanf("%d", &option);
        printf("==========================================================");
        switch(option) {
        case 1:
            printf("\nEnter a word: ");
            char *toAdd = (char*)malloc(50*sizeof(char));
            scanf("%s", toAdd);
            insert(trie, toAdd);
            printf("Result: inserted %s", toAdd);
            break;

        case 2:
            printf("\nEnter a word to search: ");
            char *toSearch = (char*)malloc(50*sizeof(char));
            scanf("%s", toSearch);
            if(search(trie, toSearch)) {
                printf("Result: %s DOES exist in trie", toSearch);
            } else {  
                printf("Result: %s DOES NOT exist in trie", toSearch);
            }
            break;

        case 3:
            printf("\nEnter a prefix to search: ");
            char *prefix = (char*)malloc(50*sizeof(char));
            scanf("%s", prefix);
            if(startsWith(trie, prefix)) {
                printf("Result: a word DOES exist in trie with prefix %s", prefix);
            } else {  
                printf("Result: a word DOES NOT exist in trie with prefix %s", prefix);
            }
            break;

        case 4:
            printf("\n");
            printTrie(trie);
            break;
            
        case 5:
            goto exit;
        }
    }
    exit : deleteTrie(trie);
    printf("\nTrie deleted\n");

    return 0;
}