#include "../Logger/Logger.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    Logger::GetInsance()->AsyncWrite((char*)"test");

    getchar();
    return EXIT_SUCCESS;
}