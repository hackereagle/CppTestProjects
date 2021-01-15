#include <iostream>

struct Test1
{
    char a;
    int b;
    char c;
};

struct Test2
{
    char a;
    char b;
    int c;
};

struct Test3
{
    char a;
    char b;
    char c;
    int d;
};

int main(int argc, char* argv[])
{
    Test1 *test1 = new Test1;
    Test2 *test2 = new Test2;
    Test3 *test3 = new Test3;

    std::cout << "Test1 testing result:" << std::endl;
    std::cout << "size of Test1:" << sizeof(Test1) << std::endl;
    std::cout << "Test1 first field a offset:" << &(test2->a) - (char*)test2 << std::endl;
    std::cout << "Test1 first field b offset:" << &(test2->b) - (char*)test2 << std::endl;
    std::cout << "Test1 first field c offset:" << (char*)&(test2->c) - (char*)test2 << std::endl;

    std::cout << "\nTest2 testing result:" << std::endl;
    std::cout << "size of Test2:" << sizeof(Test2) << std::endl;
    std::cout << "Test2 first field a offset:" << &(test3->a) - (char*)test3 << std::endl;
    std::cout << "Test2 first field b offset:" << (char*)&(test1->b) - (char*)test1 << std::endl;
    std::cout << "Test2 first field c offset:" << &(test1->c) - (char*)test1 << std::endl;

    std::cout << "\nTest3 testing result:" << std::endl;
    std::cout << "size of Test3:" << sizeof(Test3) << std::endl;
    std::cout << "Test3 first field a offset:" << &(test3->a) - (char*)test3 << std::endl;
    std::cout << "Test3 first field b offset:" << &(test3->b) - (char*)test3 << std::endl;
    std::cout << "Test3 first field c offset:" << &(test3->c) - (char*)test3 << std::endl;
    std::cout << "Test3 first field d offset:" << (char*)&(test3->d) - (char*)test3 << std::endl;

    getchar();

    return EXIT_SUCCESS;
}