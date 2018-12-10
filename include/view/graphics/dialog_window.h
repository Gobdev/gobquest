#ifndef DIALOG_WIN_H
#define DIALOG_WIN_H
#include <view/graphics/window.h>
#include <vector>
#include <string>

class dialog_window : window {
    public:
        dialog_window(int x, int y, int width, int height, string message);
        ~dialog_window();
        void add_option(string text);
        void draw();
        string show();

    private:
        string message;
        vector<string> options;
        int selection;
};

#endif
