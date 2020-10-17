#include <iostream>
#include <map>
#include <string>

// refer to  https://mropengate.blogspot.com/2015/12/cc-map-stl.html
void main()
{
	std::map<std::string, int*> test;
	test["Red"] = new int[3]{255, 0, 0};
	test["Green"] = new int[3]{0, 255, 0};
	test["Blue"] = new int[3]{0, 0, 255};

	std::cout << "red composite:" << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << (test["Red"])[i] << std::endl;
	}

	std::cout << "\nblue composite:" << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << (test["Blue"])[i] << std::endl;
	}

	delete [] test["Red"];

	system("pause");
}