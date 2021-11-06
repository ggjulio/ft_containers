// https://github.com/catchorg/Catch2/blob/v2.x/docs/own-main.md#top
#define CATCH_CONFIG_RUNNER
#include "tests.hpp"

#define xstre(s) stre(s)
#define stre(s) #s

int main (int argc, char * argv[])
{
    int result = Catch::Session().run( argc, argv );

    std::cout << "Namespace tested: " << xstre(NS_NAME) << std::endl;
    return result;
}
