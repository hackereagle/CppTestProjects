#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	std::string test = "cmd arg1 arg2 arg3";

	size_t pos = 0;
	std::string token;
	std::string delimiter = " ";
	while ((pos = test.find(delimiter)) != std::string::npos) {
		token = test.substr(0, pos);
		std::cout << token << std::endl;
		test.erase(0, pos + delimiter.length());
	}
	std::cout << "\n" << test << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}