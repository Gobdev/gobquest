#ifndef TERMINAL_H
#define TERMINAL_H
#include <view/graphics/window.h>

class terminal : public window{

    public:
        terminal(int x, int y, int width, int height);
        ~terminal();
        int run();
        string& read_command();
        void read_input();
        void update();
        void test();

    private:
        string str;
        vector<string> history;
};


#endif
