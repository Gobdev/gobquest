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
        void update();

        void test();
        void noted();

    private:
        string str;
        vector<string> history;
};



#endif
