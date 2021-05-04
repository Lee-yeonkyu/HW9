/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf_s(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf_s("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf_s("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf_s("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			fflush(stdout);
			scanf_s("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr) // 왼쪽자식>뿌리>오른쪽자식 순으로 출력.LVR 형식
{
	if (ptr) {
		inorderTraversal(ptr->left);
		printf("%d", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr) //왼쪽자식>오른쪽자식>뿌리 순으로 출력.LRV 형식
{
	if (ptr) {
		printf("%d", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr) //뿌리>왼쪽자식>오른쪽자식 순으로 출력. VLR 형식
{
	if (ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf("%d ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node* p = head->left; //현재 노드를 저장할 포인터.
	Node* list = (Node*)malloc(sizeof(Node));
	Node* pre; //현재 노드의 부모를 저장할 포인터.
	list->left = NULL;	list->right = NULL;
	list->key = key;

	if (head->left == NULL) { //헤더노드가 비었을때.
		head->left = list; //헤더의 왼쪽에 list붙여주기.
		return 1;
	}
	else {
		while (p) //현재 노드가 NULL일때 까지.
		{
			if (p->key == key) { printf("error!!\n"); return -1; } //현재 노드와 값이 같은 경우 오류.
			pre=p;
			if (p->key > key)// 현재 노드보다 값이 작은 경우 -> 왼쪽으로 이동.
				p = p->left;
			else // 현재 노드보다 값이 큰 경우 -> 오른쪽으로 이동.
				p = p->right;
		}
		if (pre->key > key)// 현재 노드의 부모보다 값이 작은 경우 ->부모의 왼쪽으로 이동.
			pre->left = list;
		else // 현재 노드의 부모보다 값이 큰 경우 -> 부모의 오른쪽으로 이동.
			pre->right = list;
	}
	return 1;
}

int deleteLeafNode(Node* head, int key)
{

}

Node* searchRecursive(Node* ptr, int key)
{

}

Node* searchIterative(Node* head, int key)
{

}


int freeBST(Node* head)
{

}





