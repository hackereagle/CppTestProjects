#include "Queue_UsingList_C.h"
#include <stdlib.h>
#include <stdio.h>

LQueue front = nullptr;
LQueue rear = nullptr;

int isQueueEmpty()
{
	if (front == nullptr)
		return 1;
	else
		return 0;
}

void enqueue(int d)
{
	LQueue new_node;
	// locate Node memory.
	new_node = (LQueue)malloc(sizeof(QNode));
	new_node->data = d;
	new_node->next = nullptr;

	if (rear == nullptr)
		front = new_node;
	else
		rear->next = new_node;

	rear = new_node;
}

int dequeue()
{
	LQueue ptr;
	int temp;

	if (!isQueueEmpty()) {
		if (front == rear) {
			rear = nullptr;
		}
		ptr = front;
		front = front->next;

		temp = ptr->data;
		free(ptr);
		return temp;
	}
	else {
		return -1;
	}
}

void TestQueue_UsingList_C()
{
	int input[100], output[100];
	int select = 1; 
	int numOfInput = 0;
	int numOfOutput = 0;
	int i, temp;
	printf("�쵲��C����C�B�z......\n");
	while (select != 3) {
		printf("[1]�s�J [2]���X [3]��ܥ������e ==> ");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			printf("�п�J�s�J��(%d) ==> ", numOfInput);
			scanf("%d", &temp);
			enqueue(temp);
			input[numOfInput++] = temp;
			break;
		case 2:
			if (!isQueueEmpty()) {
				temp = dequeue();
				printf("���X��C������: %d\n", temp);
				output[numOfOutput++] = temp;
			}
			break;
		default:
			break;
		}
	}

	printf("��J��C�������G ");
	for (i = 0; i < numOfInput; i++) {
		printf("[%d]", input[i]);
	}
	for(i = 0; i < numOfOutput; i++)
		printf("[%d]", output[i]);
	printf("\n�ѤU����C�������G ");

	while (!isQueueEmpty())
		printf("[%d]", dequeue());
	printf("\n");

	system("pause");
}