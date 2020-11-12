#include <stdlib.h>
#include "Queue_UsingList_C.h"
// NOTE: if using template, need include implement cpp
// refer to https://stackoverflow.com/questions/456713/why-do-i-get-unresolved-external-symbol-errors-when-using-templates
//https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl
//#include "QueueClass.h"
#include "QueueClass.cpp"
#include <memory>
#include <iostream>

/*
I have question in some code about dequeue from book "資料結構理論與實務─以C語言實作" p.6-15.
I consider some odd piece of code order:
	ptr = front;
	front = front->next;
	temp = ptr->data;

In order to understand, I create this project.
Then I would like to write queue with c++ class.

2020.11.07
Ha ha, I understand!
First, ptr get address storing in front.
Then, front get address storing in front->next.
I am confused by describe of book："ptr指向front".
It's seem that I have long way to go~
*/

void TestClass()
{
	std::unique_ptr<QueueClass<int>> queue(new QueueClass<int>());
	
	int input[100], output[100];
	int select = 1; 
	int numOfInput = 0;
	int numOfOutput = 0;
	int i, temp;
	printf("鏈結串列的佇列處理......\n");
	while (select != 3) {
		printf("[1]存入 [2]取出 [3]顯示全部內容 ==> ");
		std::cin >> select;
		switch (select)
		{
		case 1:
			std::cout << "Please type storing value" << numOfInput << std::endl;
			std::cin >> temp;
			queue->Enqueue(temp);
			input[numOfInput++] = temp;
			break;
		case 2:
			if (!queue->IsQueueEmpty()) {
				temp = queue->Dequeue();
				printf("取出佇列的元素: %d\n", temp);
				std::cout << "Get element from queue: " << temp << std::endl;
				output[numOfOutput++] = temp;
			}
			break;
		default:
			break;
		}
	}

	printf("輸入佇列的元素： ");
	for (i = 0; i < numOfInput; i++) {
		printf("[%d]", input[i]);
	}

	std::cout << "\nHave been take out" << std::endl;
	for(i = 0; i < numOfOutput; i++)
		printf("[%d]", output[i]);

	printf("\n剩下的佇列的元素： ");
	while (!queue->IsQueueEmpty())
		printf("[%d]", queue->Dequeue());
	printf("\n");
}

void main(int argc, char** argv)
{
	//TestQueue_UsingList_C();
	TestClass();

	system("pause");
}