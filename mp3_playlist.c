#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef char element[100];
typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

int count;
DListNode* current;


void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

void print_dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		if (p == current)
			printf("<-| #%s# |-> ", p->data);
		else
			printf("<-| %s |-> ", p->data);
	}
	printf("\n");
}

void dinsert(DListNode* before, element data)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	strcpy(newnode->data, data);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;

	count++;
}

void ddelete(DListNode* head,
	DListNode* removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);

	count--;
}

void dchange(DListNode* node1, DListNode* node2)
{
	element data;

	strcpy(data, node1->data);
	strcpy(node1->data, node2->data);
	strcpy(node2->data, data);
}


int main(void)
{
	char ch;
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);

	dinsert(head, "After LIKE");
	dinsert(head, "Attention");
	dinsert(head, "Pink Venom");
	dinsert(head, "Hype boy");
	dinsert(head, "LOVE DIVE");
	dinsert(head, "새삥");

	current = head->rlink;
	print_dlist(head);

	do {
		printf("\n명령어를 입력하시오(<, >, r, i, d, q): ");
		ch = getchar();
		if (ch == '<') {
			current = current->llink;
			if (current == head)
				current = current->llink;
		}
		else if (ch == '>') {
			current = current->rlink;
			if (current == head)
				current = current->rlink;
		}
		else if (ch == 'r') {
			srand(time(NULL));
			int move = rand() % count;
			for (int i = 0; i < move; i++) {
				current = current->rlink;
				if (current == head)
					current = current->rlink;
			}
			printf("%d만큼 이동합니다.\n", move);
		}
		else if (ch == 'i') {
			char name[100];
			char new_name[100];

			DListNode* p;
			printf("어느 음악 뒤에 삽입? ");
			scanf(" %[^\n]s", name);

			for (p = head->rlink; p != head; p = p->rlink) {
				if (strcmp(p->data, name) == 0) {
					printf("새로운 음악 이름은? ");
					scanf(" %[^\n]s", new_name);
					dinsert(p, new_name);
					break;
				}
			}
			if (p == head)
				printf("해당 노래를 찾을 수 없습니다.\n");
		}
		else if (ch == 'd') {
			char name[100];

			DListNode* p;
			printf("어느 음악을 삭제? ");
			scanf(" %[^\n]s", name);

			for (p = head->rlink; p != head; p = p->rlink) {
				if (strcmp(p->data, name) == 0) {
					if (current == head)
						current = current->rlink;
					ddelete(head, p);
					break;
				}
			}
			if (p == head)
				printf("해당 노래를 찾을 수 없습니다.\n");
		}
		print_dlist(head);
		getchar();
	} while (ch != 'q');

}