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

char* OptStr[] = {"option1", "option2", "option3" };

const char* enum2str(eOption idx)
{
	return OptStr[idx];
}

int main(int argc, char* argv[])
{

	printf("%s\n", enum2str(eOption::option1));
	printf("%s\n", enum2str(eOption::option2));
	printf("%s\n", enum2str(eOption::option3));

	system("pause");
	return 1;
}*/


// Here using X Macro
#include <iostream>

// define TABLE
#define TABLE \
	SUBSTITUTED(option1, "option1") \
	SUBSTITUTED(option2, "option2") \
	SUBSTITUTED(option3, "option3") 

// using TABLE to generate enum
#define SUBSTITUTED(a, b) a, 
	enum eOption 
	{
		TABLE
	};
#undef SUBSTITUTED

// using TABLE to generate string array
#define SUBSTITUTED(a, b) b,
	char* OptStr[] = {TABLE};
#undef SUBSTITUTED

const char* enum2str(eOption idx)
{
	return OptStr[idx];
}

int main(int argc, char* argv[])
{

	printf("%s\n", enum2str(eOption::option1));
	printf("%s\n", enum2str(eOption::option2));
	printf("%s\n", enum2str(eOption::option3));

	system("pause");
	return 1;
}