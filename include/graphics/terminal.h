#ifndef TERMINAL_H
#define TERMINAL_H
#include <graphics/window.h>

class terminal : public window{

    public:
        terminal(int x, int y, int width, int height);
        ~terminal();
        int run();

    private:
        void update();
        string str;
        vector<string> history;
};


#endif
