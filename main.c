#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node* left;
    struct node* right;
} Node;

int initializeBST(Node** h);
void inorderTraversal(Node* ptr); /* recursive inorder traversal */
void preorderTraversal(Node* ptr); /* recursive preorder traversal */
void postorderTraversal(Node* ptr); /* recursive postorder traversal */
int insert(Node* head, int key); /* insert a node to the tree */
int deleteLeafNode(Node* head, int key); /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key); /* search the node for the key */
Node* searchIterative(Node* head, int key); /* search the node for the key */
void freeNode(Node* ptr);
int freeBST(Node* head); /* free all memories allocated to the tree */
void printTree(Node* node, int space);
void test();

int main() {
    printf("[----- [김상수] [2018038078] -----]\n");

    char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z      test BST                     = a \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f \n");
		printf(" Postorder Traversal  = t      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
        case 'a': case 'A':
            test();
            break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key =  ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
            printTree(head->left, 0);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
            printTree(head->left, 0);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
            printTree(head->left, 0);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

/**
 * @brief 노드 추가
 * 
 */
int insert(Node* head, int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

    // 루트노드가 없을 경우 만들어준다.
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

    // 루트노드의 값 설정.
	Node* ptr = head->left;
	Node* parentNode = NULL;

	while(ptr != NULL) {
        if(ptr->key == key) {
            printf("BST에는 중복된 값이 올 수 없습니다!\n");
            return 1;
        }
        // 리프노드로써 추가될 장소의 부모노드 설정.
		parentNode = ptr;

        // 리프노드로써 추가될 장소 정하기.
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	// 부모노드(insert 전의 어느 리프노드)의 값에 비해 넣는 값이 작으면 왼쪽으로 크면 오른쪽에 넣는다.
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

/**
 * @brief 중위 순회로 출력
 * 
 * 왼쪽 - 루트 - 오른쪽 순으로 탐색을 한다.
 * 왼쪽을 전부 출력하고 그 부모 출력 오른쪽 출력으로 이어가는 재귀함수이다.
 * 
 * @param ptr 
 */
void inorderTraversal(Node* ptr) {
    if(ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

/**
 * @brief 전위 순회로 출력
 * 
 * 루트(부모) - 왼쪽 - 오른쪽 순으로 탐색을 한다.
 * 왼쪽으로 가면서 그 값을 출력하고 오른쪽으로 이동해서 값을 출력한다.
 * 
 * @param ptr 
 */
void preorderTraversal(Node* ptr) {
    if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

/**
 * @brief 후위 순회로 출력
 * 
 * 왼쪽 노드 - 오른쪽 노드 - 루트(부모) 순으로 탐색을 한다.
 * 이 순으로 출력또한 된다.
 * 
 * @param ptr 
 */
void postorderTraversal(Node* ptr) {
    if(ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}

/**
 * @brief 리프노드 제거
 * 
 * @param head 
 * @param key 
 * @return int 
 */
int deleteLeafNode(Node* head, int key) {
    // 트리가 빈 경우 처리
    if (head == NULL) {
		printf("\n Nothing to delete [Head Node not initialized]\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete [Root Node not initialized]\n");
		return -1;
	}

	Node* ptr = head->left;
	Node* parentNode = head;

    // 
	while(ptr != NULL) {
        // 삭제할 키값을 찾았을 때
		if(ptr->key == key) {
            // 그 노드가 리프노드일 경우
			if(ptr->left == NULL && ptr->right == NULL) {
                // 루트노드밖에 노드가 없을 경우 처리
				if(parentNode == head) {
					head->left = NULL;
                }
                // 왼쪽 또는 오른쪽을 지워준다.
				if(parentNode->left == ptr) {
					parentNode->left = NULL;
                }
				else {
					parentNode->right = NULL;
                }
                // 지우고 나서 할당해제.
				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		// parentNode 가 항상 이전노드(부모노드)를 가리키게 한다.
		parentNode = ptr;

		// 값의 크기에 따라 다음에 갈 방향이 어디인지 정한다.
		if(ptr->key < key) {
			ptr = ptr->right;
        }
		else {
			ptr = ptr->left;
        }
	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

/**
 * @brief 검색(재귀로)
 * 
 * 크기를 비교하면서 내려가고
 * 마지막에 도달했는데도 찾는게 없으면 NULL을 반환
 * 만약 찾는 노드의 값이 현재 노드의 값보다 작거나 크지 않은 경우(같은 경우)에 그 값을 반환해준다.
 * 
 * @param ptr 
 * @param key 
 * @return Node* 
 */
Node* searchRecursive(Node* ptr, int key) {
    if(ptr == NULL) {
		return NULL;
    }

	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/* if ptr->key == key */
	return ptr;
}

/**
 * @brief 검색
 * 
 * 위의 함수와 로직은 같지만 재귀가 아니므로 if 로 값이 일치한지 확인해준다.
 * 
 * @param head 
 * @param key 
 * @return Node* 
 */
Node* searchIterative(Node* head, int key) {
    Node* ptr = head->left;

	while(ptr != NULL)
	{
		if(ptr->key == key)
			return ptr;

		if(ptr->key < key) ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	return NULL;
}

/**
 * @brief 재귀로 트리를 할당 해제 해준다.
 * 
 * @param ptr 
 */
void freeNode(Node* ptr) {
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

/**
 * @brief 이진트리 초기화
 * 
 */
int freeBST(Node* head) {
    // 이런 경우는 안생길거 같긴 하다.
    if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;
    // 루트노드와 그 밑에 있는 노드들을 할당 해제 해준다.
	freeNode(p);
    // 마지막으로 헤드를 할당 해제 해준다.
	free(head);
	return 1;
}

void printTree(Node* node, int space)
{
    int i;

    // 트리가 비었을 경우
    if (node == NULL)
        return;

    space += 10;

    printTree(node->right, space);

    printf("\n");
    for (i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", node->key);

    printTree(node->left, space);
}

void test(){
    Node* head = NULL;
    Node* temp = NULL;

    printf("\n- BST Test -\n");

    initializeBST(&head);
    // Test insert
    insert(head, 50);
    insert(head, 30);
    insert(head, 20);
    insert(head, 40);
    insert(head, 70);
    insert(head, 60);
    insert(head, 80);

    printf("\n- Inorder traversal -\n");
    inorderTraversal(head->left);
    
    printf("\n- Preorder traversal -\n");
    preorderTraversal(head->left);

    printf("\n- Postorder traversal -\n");
    postorderTraversal(head->left);

    // Test search
    temp = searchRecursive(head->left, 20);
    if(temp != NULL) {
        printf("\n- Node 20 found -\n");
    } else {
        printf("\n- Node 20 not found -\n");
    }

    temp = searchIterative(head, 90);
    if(temp != NULL) {
        printf("\n- Node 90 found -\n");
    } else {
        printf("\n- Node 90 not found -\n");
    }

    // Test delete leaf node
    deleteLeafNode(head, 20);
    printf("\n- Inorder traversal after deleting 20 -\n");
    inorderTraversal(head->left);

    // Print tree structure
    printf("\n- BST structure -\n");
    printTree(head->left, 0);

    // Test free BST
    freeBST(head);
}