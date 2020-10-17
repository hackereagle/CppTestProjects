// Here perform how X Macro working
// The example is a situation that we would print enumutation as string.

// general writing
/*#include <iostream>

enum eOption
{
	option1,
	option2,
	option3
};

int main(int argc, char* argv[])
{
	char* OptStr[] = {"option1", "option2", "option3" };

	for (int i = 0; i < 3; i++)
		printf("%s\n", OptStr[i]);

	system("pause");
	return 1;
}*/


// Here using X Macro
#include <iostream>

#define TABLE \
	SUBSTITUTED(option1, "option1") \
	SUBSTITUTED(option2, "option2") \
	SUBSTITUTED(option3, "option3") 

#define SUBSTITUTED(a, b) a, 
enum Option 
{
	TABLE
};
#undef SUBSTITUTED

int main(int argc, char* argv[])
{
#define SUBSTITUTED(a, b) b,
	char* OptStr[] = {TABLE};
#undef SUBSTITUTED

	for (int i = 0; i < 3; i++)
		printf("%s\n", OptStr[i]);

	system("pause");
	return 1;
}