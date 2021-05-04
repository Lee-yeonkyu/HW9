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

	printf("[----- [이연규] [2018038038] -----]\n");
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
		scanf(" %c", &command);

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
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
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
		printf("[%d]\t", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)//뿌리>왼쪽자식>오른쪽자식 순으로 출력. VLR 형식
{
	if (ptr) {
		printf("[%d]\t", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr) //왼쪽자식>오른쪽자식>뿌리 순으로 출력.LRV 형식
{
	if (ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf("[%d]\t", ptr->key);
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
	Node *tmp=head->left; //현재 노드 저장용
	Node *parent =tmp; //부모노드 저장용
	Node *del; //삭제할 노드.

	while(tmp->key !=key){ //현재 노드의 키값과 제거 대상의 키값이 같을때 까지 반복
		parent=tmp; //부모 노드 저장
		if(tmp->key<key) //현재 노드 보다 제거할 값이 더 크면
			tmp=tmp->right; // 오른쪽으로 옮겨준다.
		else //현재 노드 보다 제거할 값이 더 작으면
			tmp=tmp->left; // 왼쪽으로 옮겨준다.
	}
	del=tmp;// 제거하고자 한 키값을 가지고 있는 노드의 위치 저장.

	if(tmp->left==NULL &&tmp->right==NULL){ // 제거하고자 하는 노드의 자식이 하나도 없을때.
		if(parent->left!=NULL){ //부모의 왼쪽 자식이 존재할때.
			if(tmp->key==parent->left->key){ //그 값과 제거 하고자하는 노드의 키값이 같다면
				parent->left=NULL; //왼쪽 노드를 NULL로 바꿔준다.
				free(del);
				return 0;
			}
		}
	parent->right=NULL; //왼쪽 자식이 존재 하지 않다면 오른쪽 자식을 NULL로 처리.
	free(del);
	return 0;
	}
	else{
		printf("the node [%d] is not a leaf\n\n",key);
	}
	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if (ptr == NULL) //ptr이 공백이라면 NULL 리턴
		return NULL;
	if (key == ptr->key) //찾는 값이라면 ptr 리턴
		return ptr;
	else if (key < ptr->key) //찾는값 보다 ptr의 값이 더 크다면 왼쪽으로 재귀함수 실행
		return searchRecursive(ptr->left, key);
	else //찾는값 보다 ptr의 값이 더 작다면 오른으로 재귀함수 실행
		return searchRecursive(ptr->right, key);

}

Node* searchIterative(Node* head, int key)
{
	Node *cur =head->left;
	while(cur!=NULL){ //cur가 NULL이면 찾는 값이 없는 경우.
		if(cur->key==key) //노드의 키값과 찾는 키가 같은 경우 리턴.
			return cur; //
		else if(cur->key<key) //노드 안의 키값이 찾는 키값보다 작은경우 오른쪽으로 간다.
			cur=cur->right;
		else //노드 안의 키값이 찾는 키값보다 큰 경우 왼쪽으로 간다.
			cur=cur->left;
	}
	return 0;
}


int freeBST(Node* head)
{
	if (!head){ //빈 함수 인 경우에 에러 출력.
		printf("error!");
		return -1;
	}
	if (head){ //빈 함수가 아닌 경우에 출력.
		if(head->key==-9999){ //맨처음에 헤더노도의 왼쪽으로 시작지점으로 옮겨준다.
			freeBST(head->left);
		}
		freeBST(head -> left); //후위 순회 방식으로 왼쪽자식>오른쪽자식>뿌리 순으로 제거.
		freeBST(head -> right);
		free(head);
		head = NULL;
	}
	return 1;
}





