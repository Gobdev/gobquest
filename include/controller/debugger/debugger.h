#ifndef DEBUGGER_H
#define DEBUGGER_H
#include <functional>
#include <string>

using namespace std;

extern function<void(string)> debug_print_function;

inline void debug_print(string s){
    debug_print_function(s);
}

#endif //DEBUGGER_H
