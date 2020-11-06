#pragma once
#ifndef QUEUE_USING_LIST_C_H_
#define QUEUE_USING_LIST_C_H_

struct  Node
{
	int data;
	struct Node *next;
};
typedef struct Node QNode;
typedef QNode *LQueue;

LQueue front = nullptr;
LQueue rear = nullptr;

int isQueueEmpty();
int enquue(int d);
int dequeue();
#endif QUEUE_USING_LIST_C_H_