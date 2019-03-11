#ifndef TERMINAL_H
#define TERMINAL_H
#include <view/graphics/window.h>
#include <controller/events/event_handler.h>

class terminal : public window{

    public:
        terminal(int x, int y, int width, int height);
        ~terminal();
        int run();
        string& read_command();
        void read_input();
        void print_string(string str);
        void update();

        void test();
        void noted();

        void print_debug(string str);

    private:
        void add_line(string line);
        void add_line_inner(string line);
        string str;
        vector<string> history;
        vector<string> input_history;
        size_t cursor_pos = 0;

        // Handler for standard ascii keys
        void add_char(char c);

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
};



#endif
