#include "gtest/gtest.h"
#include <string>
#include <controller/debugger/debugger.h>

// Set up global constants.
function<void(string)> debug_print_function;
debug_stream debug;

void f(string s){}

int main(int argc, char **argv){
    debug_print_function = f;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
