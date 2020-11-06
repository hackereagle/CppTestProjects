#include <stdlib.h>
#include <stdio.h>
#include "Queue_UsingList_C.h"

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

	if (rear = nullptr)
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

}