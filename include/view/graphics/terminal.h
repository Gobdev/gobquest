#ifndef TERMINAL_H
#define TERMINAL_H
#include <view/graphics/window.h>
#include <controller/events/event_handler.h>
#include <controller/debugger/debugger.h>

class unicode_string : public string {
public:
    unicode_string() : string() {};
    unicode_string(const char* c) : string(c) {};

    inline size_t unicode_length() const {
        size_t length = 0;
        for (size_t current = 0; current < size(); current++){
            while(((*this)[current] & 0xC0) == 0xC0){
                current++;
            }
            length++;
        }
        return length;
    }

    void insert(size_t pos, size_t length, char c){
        for (size_t current = 0; current < pos && current < size(); current++){
            size_t extra_chars = 0;
            unsigned char val = (*this)[current];
            if ((val >> 5) == 0x6){         // UTF-8 char with 2
                extra_chars = 1;
            } else if ((val >> 4) == 0xE){  // UTF-8 char with 3 characters
                extra_chars = 2;
            } else if ((val >> 3) == 0x1E){ // UTF-8 char with 4 characters
                extra_chars = 3;
            }
            for (size_t extra = 0; extra < extra_chars && current + extra < size() - 1; extra++){
                val = (*this)[current + extra];
                if ((val & 0xC0) == 0x80){
                    pos++;
                } else {             // If this else statement is reached, data is corrupted.
                    break;
                }
            }
        }
        debug << "Inserting at: " << pos << endl;
        string::insert(pos, length, c);
    }
};

class terminal : public window{

    public:
        terminal(int x, int y, int width, int height);
        ~terminal();
        void read_input();
        void print_string(string str);
        void update();

        void test();
        void noted();

        void print_debug(string str);

    private:
        void add_line(string line);
        void add_line_inner(string line);
        unicode_string str;
        vector<string> history;
        vector<unicode_string> input_history;
        size_t history_pos = 0;
        size_t cursor_pos = 0;
        size_t str_length = 0;

        // Handler for standard ascii keys
        void add_char(char c);
        const unicode_string& current_string();
        size_t unicode_length(const string& s);

        // Specific key handlers
        void enter_key();
        void delete_key();
        void backspace_key();
        void left_key();
        void right_key();
        void up_key();
        void down_key();
        void home_key();
        void end_key();
        void set_current_string();
};



#endif
