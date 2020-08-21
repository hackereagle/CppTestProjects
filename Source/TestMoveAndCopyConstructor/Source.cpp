#include <iostream>

class MyClass
{
public:
	MyClass() 
	{
		std::cout << "normal constructor" << std::endl;
	}

	MyClass(const MyClass&)
	{
		std::cout << "copy constructor" << std::endl;
	}

	MyClass(MyClass&&)
	{
		std::cout << "move constructor" << std::endl;
	}

	~MyClass() {}

private:

};

MyClass makeMyClass()
{
	MyClass c;
	return c;
}

void main()
{
	MyClass c1;
	MyClass c2(makeMyClass());
	system("pause");
}