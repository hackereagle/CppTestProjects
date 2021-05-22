#include <stdio.h>
#include <stdlib.h>

int main(int agrc, char** agrv)
{
	int value = 0;
	int* ptr = &value;
	long long int ptr_int = (long long int)ptr;

	printf("Test int value pointer to long long int:\n");
	printf("\tint value = %d\n", value);
	printf("\tvalue address = %p\n", ptr);
	printf("\tvalue address long long int type = %llx\n", ptr_int);


	*(int*)ptr_int = 2;
	printf("\nTest long long int to int value pointer:\n");
	printf("\tint value = %d\n", value);
	printf("\tvalue address = %p\n", ptr);
	printf("\tvalue address long long int type = %llx\n", ptr_int);

	getchar();
	return EXIT_SUCCESS;
}