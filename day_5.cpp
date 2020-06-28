#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include <ctype.h>
#include <set>
using namespace std;

struct Node {
	char data;
	struct Node *next;
	struct Node *prev;
};

struct listRep {
	int size;
	Node *head;
};

typedef struct listRep *List;

List newLL() {
	List listr = (List)malloc(sizeof(listRep));
	assert(listr!=NULL);
	listr->size = 0;
	listr->head = NULL;
	return listr;
}

int isEmpty(List listr) {
	if (listr->head == NULL) {
		return 1;
	}
	return 0;
}

Node *createNode(char val) {
	Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

Node *insertNode(List listr, char val) {
    Node *newHead = createNode(val);
    newHead->next = listr->head;
    if (listr->head != NULL) {
    	(listr->head)->prev = newHead;
    }
    listr->head = newHead;
    listr->size++;
    return newHead;
}

void printLinkedList(List listr) {
    if (listr->head == NULL) {
        return;
    }
    Node *curr = listr->head;
    while (curr->next != NULL) {
        printf("%c", curr->data);
        curr=curr->next;
    }
    printf("%c\n", curr->data);
    return;
}

void deleteNode(List listr, Node* del) {
	if (listr->head == NULL || del == NULL) {
		return;
	}

	if (listr->head == del)
		listr->head = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
	    del->prev->next=del->next;
	free(del);
    listr->size--;
	return;
}

void freeLL(List listr) {
	Node *temp;
    while (listr->head != NULL) {
    	temp=listr->head;
    	listr->head=listr->head->next;
    	free(temp);
    }
    free(listr);
}

int isElementMatch(char comp1, char comp2) {
    if (tolower(comp1)==tolower(comp2)) {
        if (isupper(comp1) && islower(comp2)) {
            return 1;
        } else if (isupper(comp2) && islower(comp1)) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

int main() {
    ifstream myfile ("input_5.txt");
    char c;
    List myList=newLL();
    if (myfile.is_open()) {
      while (myfile.get(c)) {
          insertNode(myList, c);
      }
    }
    Node *curr = myList->head;
    while (curr->next != NULL) {
    	Node *temp;
    	Node *temp2;
        if (isElementMatch(curr->data,curr->next->data)) {
            temp = curr;
    		temp2 = curr->next;
            //if not at list head
            if (curr->prev != NULL) {
                curr = curr->prev;
            //if at list head move two spaces forward
            } else if (curr->next->next != NULL) {
                curr = curr->next->next;
            } else {
                curr=curr->next;
            }
    		deleteNode(myList, temp);
            deleteNode(myList, temp2);
    	} else {
            curr=curr->next;
    	}
    }
    printLinkedList(myList);
    cout << myList->size << "\n";
    freeLL(myList);
	return 0;
}

