#include "QueueClass.h"
#include <iostream>

template <typename T>
QueueClass<T>::QueueClass()
{
}

template <typename T>
QueueClass<T>::~QueueClass()
{
	if (mFront != nullptr) {
		delete mFront;
		mFront = nullptr;
	}

	if (mRear != nullptr) {
		delete mRear;
		mRear = nullptr;
	}
}

template <typename T>
bool QueueClass<T>::IsQueueEmpty()
{
	if (mFront == nullptr)
		return true;
	else
		return false;
}

template <typename T>
void QueueClass<T>::Enqueue(T data)
{
	_node *newNode = new Node();
	newNode->data = data;
	newNode->next = nullptr;

	if (mRear == nullptr)
		mFront = newNode;
	else
		mRear->next = newNode;

	mRear = newNode;
}

template<typename T>
T QueueClass<T>::Dequeue()
{
	_node *ptr;
	T returnData;

	if (!IsQueueEmpty()) {
		if (mFront == mRear) {
			mRear = nullptr;
		}
		ptr = mFront;
		mFront = mFront->next;

		returnData = ptr->data;
		delete ptr;
	}
	else {
		throw new std::exception("Queue is empty");
	}

	return returnData;
}