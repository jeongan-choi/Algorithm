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
	dinsert(head, "����");

	current = head->rlink;
	print_dlist(head);

	do {
		printf("\n��ɾ �Է��Ͻÿ�(<, >, r, i, d, q): ");
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
			printf("%d��ŭ �̵��մϴ�.\n", move);
		}
		else if (ch == 'i') {
			char name[100];
			char new_name[100];

			DListNode* p;
			printf("��� ���� �ڿ� ����? ");
			scanf(" %[^\n]s", name);

			for (p = head->rlink; p != head; p = p->rlink) {
				if (strcmp(p->data, name) == 0) {
					printf("���ο� ���� �̸���? ");
					scanf(" %[^\n]s", new_name);
					dinsert(p, new_name);
					break;
				}
			}
			if (p == head)
				printf("�ش� �뷡�� ã�� �� �����ϴ�.\n");
		}
		else if (ch == 'd') {
			char name[100];

			DListNode* p;
			printf("��� ������ ����? ");
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
				printf("�ش� �뷡�� ã�� �� �����ϴ�.\n");
		}
		print_dlist(head);
		getchar();
	} while (ch != 'q');

}