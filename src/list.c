#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

struct node *head = NULL;
struct node *current = NULL;

void printNodes(){
	struct node *ptr head;
	print("\n[ ");

	while(ptr != NULL){
		printf("(%d) ", ptr->data);
		ptr = ptr->next;
	}
	
	printf(" ]");
}

void insert(int data) {
	struct node *link = (struct node*) malloc(sizeof(struct node));
	link->data = data;
	link->next = head;
	head = link;
}

struct node* delete() {
	struct node *tempLink = head;
	head = head->next;
	return tempLink;
}

void main() {
	insert(1);
	insert(2);
	insert(3);
	insert(4);
	insert(5);

	print("List: ");
	printList();
	delete();
	delete();
	
	printf("\nList after deleting 2 items: ");
	printList();
}
