#pragma once
#ifndef QUEUE_USING_LIST_C_H_
#define QUEUE_USING_LIST_C_H_

struct Node
{
	int data;
	struct Node *next;
};
typedef struct Node QNode;
typedef QNode *LQueue;

int isQueueEmpty();
void enqueue(int d);
int dequeue();
void TestQueue_UsingList_C();
#endif QUEUE_USING_LIST_C_H_ 