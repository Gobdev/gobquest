#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <functional>
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
#include <algorithm>

using namespace std;

extern function<void(string)> debug_print_function;

class debug_stream {
private:
    ostringstream inner_stream;

public:
    inline debug_stream(){
        inner_stream = ostringstream(ostringstream::ate);
    }

    void flush(){
        debug_print_function(inner_stream.str());
        inner_stream.str("");
    }

    void print_newlines(){
        string str = inner_stream.str();
        string::size_type pos = 0;
        while ((pos = str.find('\n')) != string::npos) {
            debug_print_function(str.substr(0, pos));
            str = str.substr(pos + 1);
        }
        inner_stream.str(str);
    }

    template<class T>
    friend debug_stream& operator<<(debug_stream& os, const T &input);
};


template<class T>
debug_stream& operator<<(debug_stream& os, const T &input){
    os.inner_stream << input;
    os.print_newlines();
    return os;
}

extern debug_stream debug;


#endif //DEBUGGER_H
