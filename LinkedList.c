#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *head;

/*  Remember, *temp points to an address. Printing temp will print the address. 
    To work with temp's data, you need to de-reference it (*tmp). 
    To insert x, create a *temp node pointer and set it to a new address in 
    memory. Set temp's data to x. 
    You could also do temp->data to x. */
void insertFront(int x) { 
    Node *temp; 
    temp = (Node*)malloc(sizeof(Node));
    
    (*temp).data = x;
    (*temp).next = head;
    head = temp;
}

/*  Create *temp and *prev node pointers and allocate memory for the nodes. Set 
    the temp node's data to x. Have prev point to the same place head points to 
    because you don't want to actually change where head is. You just want to 
    start there. 
    While prev isn't null, shift each node to the left. Eventually set the temp 
    node to the last element. */
void insertBack(int x) {
    Node *temp;
    Node *prev;
    temp = (Node*)malloc(sizeof(Node));
    prev = (Node*)malloc(sizeof(Node));

    (*temp).data = x;
    (*temp).next = NULL;

    prev = head;
    while((*prev).next != NULL) {
        prev = (*prev).next;
    }
    (*prev).next = temp;
}

/*  Similar start to insertBack(), but also create a new_node pointer. That's 
    where x is going. Set the new_node's data to x. 
    If you're inserting at the first element, do something special. 
    Have prev and temp both point to the same place head points to. Shift temp 
    and prev to make space for new_node. Then insert new_node. */
void insertAt(int x, int idx) {    
	Node *temp;
    Node *prev;
    Node *new_node;
	temp = (Node*)malloc(sizeof(Node));
	prev = (Node*)malloc(sizeof(Node));
	new_node = (Node*)malloc(sizeof(Node));

    if(idx == 1) {
        temp = head;
        (*new_node).data = x;
        head = new_node;
        (*head).next = (*temp).next;
	}

	(*new_node).data = x;
    
	prev = head;
	temp = head;

	for(int i=0; i<idx; i++) {
        temp = (*temp).next;
    }
	for(int i=0; i<idx-2; i++) {
        prev = (*prev).next;
    }

	(*prev).next = new_node;
	(*new_node).next = temp;
}

/*  Similar to insertAt(), except we're deleting the node where x is. If we're 
    deleting at the front, simply move head to the right one step. */
void deleteAt(int idx) {
    Node *temp;
    Node *prev;
	temp = (Node*)malloc(sizeof(Node));
	prev = (Node*)malloc(sizeof(Node));

	prev = head;
	temp = head;

    if(idx == 1) {
    	head = (*temp).next;
        free(temp);
    	return;
    }

	for(int i=0; i<idx; i++)
		temp = (*temp).next;
	
	for(int i=0; i<idx-2; i++)
		prev = (*prev).next;

	(*prev).next = temp;
}

/*  Free each node and set head to null. */
void deleteList(Node *root) {
    Node *tmp;
    while(root != NULL) {
        tmp = root;
        root = (*root).next;
        free(tmp);
    }
	head = NULL;
}

/*  If the list is only one element, set the head to it. Call reverse 
    recursively. Use a temp node to save the the root's next node because we 
    eventually want to set root.next to null. */
void reverse(Node *root) {
    if((*root).next == NULL) {
		head = root;
		return;
	}

	reverse((*root).next);
	Node *temp;
	temp = (*root).next;
	(*temp).next = root;
	(*root).next = NULL;
}

/*  Recursively print the list by referencing each node's next. */
void printList(Node *root) {
    if(root == NULL)
		return;

	printf("%d ", (*root).data);
	printList((*root).next);
}

/*  Same as printList, but backwards. */
void printReverse(Node *root) {
    if(root == NULL)
		return;

	printReverse((*root).next);
	printf("%d ", (*root).data);
}

/*  Test suite. */
int main(void) {
    int n, x, option;
	head = NULL;

	printf("How many numbers? ");
	scanf("%d", &n);

	printf("Enter %d numbers: ", n);
	scanf("%d", &x);
	insertFront(x);

	for(int i=0; i<n-1; i++) {
		scanf("%d", &x);
		insertBack(x);
	}
	printf("Choose an operation: \n");
	printf("1. Add an element at the front\n");
	printf("2. Add an element at the back\n");
    printf("3. Insert an element at an index\n");
    printf("4. Delete an element at an index\n");
	printf("5. Delete the list\n");
	printf("6. Reverse the list (changes the original list)\n");
	printf("7. Print the list in reverse (does not change the original list)\n");
	printf("Your choice: ");
	scanf("%d", &option);

	switch(option) {
		case 1:
			printf("Enter a number to add to the front: ");
			scanf("%d", &x);
			insertFront(x);
			printf("List: ");
            printList(head);
			break;

		case 2:
            printf("Enter a number to add to the back: ");
			scanf("%d", &x);
			insertBack(x);
			printf("List: ");
            printList(head);
			break;

		case 3:
            printf("Enter a number and index to add: ");
			scanf("%d %d", &x, &n);
			insertAt(x, n);
			printf("List: ");
            printList(head);
			break;

		case 4:
			printf("Enter the index of the number to delete: ");
			scanf("%d", &n);
			deleteAt(n);
			printf("List: ");
            printList(head);
			break;

        case 5:
            deleteList(head);
            if(head == NULL) {
			    printf("List: []");
            }
			break;

        case 6:
            reverse(head);
            printf("List: ");
            printList(head);
            break;

        case 7:
            printf("List: ");
			printReverse(head);
			break;
	}
    printf("\n");
    return 0;
}