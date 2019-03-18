#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <functional>
#include <string>
#include <sstream>
#include <bitset>
#include <algorithm>

using namespace std;

extern function<void(string)> debug_print_function;

inline void debug_print(string s){
    debug_print_function(s);
}

inline void debug_print(int i){
    ostringstream debug_str;
    debug_str << "(int) " << i;
    debug_print_function(debug_str.str());
}

inline void debug_print(char c){
    ostringstream debug_str;
    std::bitset<8> x(c);
    debug_str << "(char) " << c << ", (" << (int) c << "), (" << x << ")";
    debug_print_function(debug_str.str());
}

inline void debug_print(size_t s){
    ostringstream debug_str;
    debug_str << "(size_t) " << s;
    debug_print_function(debug_str.str());
}

class debug_stream : public ostringstream{
public:

    debug_stream& operator<<(const string &a) {
        ostringstream& os = (std::ostringstream&)(*this);
        os << a;
        if (count(a.begin(), a.end(), '\n') > 0){
            debug_print_function(str());
            str("");
        }
        return (*this);
    }

    template<class T>
    debug_stream& operator <<(const T &t)
    {
        (std::ostringstream&)(*this) << t;
        return *this;
    }

    template<class T, class traits>
    debug_stream& operator <<(debug_stream<T, traits>& (*pf) (basic_ostream<T,traits>&))
    {
        (std::ostringstream&)(*this) << pf;
        return *this;
    }

    basic_ostream<charT,traits>& operator<<(basic_ostream<charT,traits>& (*pf) (basic_ostream<charT,traits>&));

};

/*ostringstream& operator<<(ostringstream& os, const string &a) {
    os << a;
    if (count(a.begin(), a.end(), '\n') > 0){
        debug_print_function(os.str());
        os.str("");
    }
    return os;
}*/

extern debug_stream debug;


#endif //DEBUGGER_H
