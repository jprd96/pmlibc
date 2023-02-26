#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define max(a,b) ((a) > (b) ? (a) : (b))

typedef struct Node {
    struct Node *left;
	int data;
	struct Node *right;
} Node;

/*  This function inserts a new node into a BST and returns the new root. 
    If BST is empty, the new node = the new tree. If the data to be entered is 
	less than root's value, recurse left. If it's greater than root's value, 
	recurse right.  */
Node *insert(Node *root, int data) {
	if(root == NULL) {
		root = (Node*)malloc(sizeof(Node));
		(*root).left = NULL;
		(*root).data = data;
		(*root).right = NULL;
	} 
	else if(data <= (*root).data) {
		(*root).left = insert((*root).left, data);
	} 
	else {
		(*root).right = insert((*root).right, data);
	}
	return root;
}

/*  This function serves as a helper to delete().  */
int search(Node* root, int data) {
	if(root == NULL) { 
		return 0; 
	}
	if((*root).data == data) { 
		return 1; 
	}
    int inLeft = search((*root).left, data);
    if(inLeft) { 
		return 1; 
	}
    int inRight = search((*root).right, data);
    return inRight;

}

/*  This function serves as a helper to delete().  */
Node* findMin(Node* root) {
	while((*root).left != NULL) {
		root = (*root).left;
	}
	return root;
}

/*  This function deletes a node and returns the new root.
    If the data to be deleted is less than root's value, recurse left. If it's 
	greater than root's value, recurse right. If it's the same as the root, 
	this is the node to delete. If the root has no children, simply free it. If 
	the root has one child, make a copy before you delete the child and recurse 
	down. If the root has two children, first find the minimum of the right. 
	Then copy the min to the root and then delete the min.  */
Node *delete(struct Node *root, int data) {
	if(!search(root, data)) {
		return root;
	}
	else if(data < (*root).data) {
		(*root).left = delete((*root).left, data);
	}
	else if(data > (*root).data) {
		(*root).right = delete((*root).right, data);
	}
	else {
		if((*root).left == NULL && (*root).right == NULL) {
			free(root);
			root = NULL;
		}
		else if((*root).left != NULL && (*root).right == NULL) {
			Node *temp = (*root).left;
			free(temp);
			root = (*root).left;
		}
		else if((*root).left == NULL && (*root).right != NULL) {
			Node *temp = (*root).right;
			free(temp);
			root = (*root).right;
		}
		else {
			Node *temp = findMin(root->right);
			(*root).data = (*temp).data;
			(*root).right = delete((*root).right, (*temp).data); 
		}
	}
	return root;
}

/*  This function returns the height of a BST.  */
int getHeight(Node* root) {
	if(root == NULL) {
		return -1;
	}
	return((max(getHeight((*root).left), getHeight((*root).right))) + 1);
}

/*  This function prints the pre-order traversal of a BST.
	Start at the root, traverse depth first, and end at the right-most node. 
	Useful for creating a copy of a BST. Place the nodes in an array with 
	pre-order and then perform insert on a new tree for each value.  */
void preOrder(Node *root) {
	if(root == NULL) {
		return;
	}
	printf("%d ", (*root).data);
	preOrder((*root).left);
	preOrder((*root).right);

}

/*  This function prints the in-order traversal of a BST.
	Start at the left-most node and end at the right-most node. This prints the 
	nodes in sorted order. */
void inOrder(Node *root) {
	if(root == NULL) {
		return;
	}
	inOrder((*root).left);
	printf("%d ", (*root).data);
	inOrder((*root).right);
}

/*  This function prints the post-order traversal of a BST.
	Start at the left-most node and end at the root. Useful for deleting a tree 
	from leaf to root. */
void postOrder(Node *root) {
	if(root == NULL) {
		return;
	}
	postOrder((*root).left);
	postOrder((*root).right);
	printf("%d ", (*root).data);
}

/*  This function frees each node and its children and sets head to null.  */
void deleteBST(Node *root) {
	if(root == NULL) {
		return;
	}
	deleteBST((*root).left);
    deleteBST((*root).right);
    free(root);
	root = NULL;
}

/*  Test suite. */
int main(void) {
	// pre-order: 7 1 0 3 2 5 4 6 8 10 
	// in-order: 0 1 2 3 4 5 6 7 8 10 
	// post-order: 0 2 4 6 5 3 1 10 8 7 
    int n, x, option;
	Node *root = NULL;

	printf("How many numbers? ");
	scanf("%d", &n);

	printf("Enter %d numbers: ", n);
	for(int i=0; i<n; i++) {
		scanf("%d", &x);
		root = insert(root, x);
	}

    printf("Choose an operation: \n");
    printf("1. Insert a new node\n");
    printf("2. Delete a node\n");
    printf("3. Get the height of the BST\n");
	printf("4. Print the pre-order traversal\n");
    printf("5. Print the in-order traversal\n");
    printf("6. Print the post-order traversal\n");
	printf("7. Delete the BST\n");
    printf("Your choice: ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            printf("Enter the node to insert: ");
            scanf("%d", &x);
            root = insert(root, x);
			preOrder(root);
            break;

        case 2:
            printf("Enter the node to delete: ");
            scanf("%d", &x);
            root = delete(root, x);
			preOrder(root);
            break;

        case 3:
            printf("Height: %d\n", getHeight(root));
            break;

        case 4:
            preOrder(root);
            break;

        case 5:
            inOrder(root);
            break;

        case 6:
            postOrder(root);
            break;
	
		case 7:
            deleteBST(root);
			printf("Tree is now empty.");
            break;
    }
	printf("\n");
    return 0;
}