#pragma once
#ifndef _H_QUEUE_CLASS_
#define _H_QUEUE_CLASS_

template <typename T>
class QueueClass
{
public:
	QueueClass();
	~QueueClass();
	bool IsQueueEmpty();
	void Enqueue(T data);
	T Dequeue();

private:
	typedef struct Node
	{
		T data;
		Node* next;
	}_node;
	_node* mFront = nullptr;
	_node* mRear = nullptr;

};
#endif // !_H_QUEUE_CLASS_
