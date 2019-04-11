#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <functional>
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
#include <algorithm>

using namespace std;

// The pointer to the debug function used by the debug_stream. (Set in main.cpp)
extern function<void(string)> debug_print_function;

class debug_stream {
private:
    ostringstream inner_stream;

public:
    inline debug_stream(){
        inner_stream = ostringstream(ostringstream::ate);
    }

    /**
     *  Flush the contents of the debug_stream into the terminal.
     */
    void flush(){
        print_newlines();
        debug_print_function(inner_stream.str());
        inner_stream.str("");
    }

    /**
     *  Print each line in the inner stream, and remove them from the stream.
     */
    void print_newlines(){
        string str = inner_stream.str();
        string::size_type pos = 0;
        while ((pos = str.find('\n')) != string::npos) {
            debug_print_function(str.substr(0, pos));
            str = str.substr(pos + 1);
        }
        inner_stream.str(str);
    }

    /**
     * Sends the input to the inner stream, then prints each row that has a
     * newline at the end of the inner stream via the debug function.
    */
    template <typename T>
    debug_stream& operator<<(const T& input) {
        inner_stream << input;
        print_newlines();
        return *this;
    }

    // Handles std::endl
    debug_stream& operator<<(std::ostream&(*f)(std::ostream&)) {
       flush();
       return *this;
    }
};

// Declares the debug stream object that is to be used when debugging.
extern debug_stream debug;


#endif //DEBUGGER_H
