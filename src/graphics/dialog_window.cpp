#include <graphics/dialog_window.h>
#include <string>

using namespace std;

dialog_window::dialog_window(int x, int y, int width, int height, string message) :
               window (x, y, width, height){
    this -> message = message;
    this -> options = vector<string>();
    keypad(_window, TRUE);
}

dialog_window::~dialog_window(){}

void dialog_window::add_option(string text){
    this -> options.push_back(text);
}

void dialog_window::draw(){
    draw_border();
    int rows = 0;
    if (message.size() < width) {
        mvwprintw(_window, 0, (width - message.size()) / 2, message.c_str());
        rows++;
    } else {
        string message_copy = string(message);
        while(true){
            mvwprintw(_window, rows, 1, message_copy.substr(0, width - 2).c_str());
            rows++;
            if (message_copy.size() < width - 2 || rows >= height)
                break;
            message_copy = message_copy.substr(width - 2);
        }
    }
    rows++;
    for (int i = 0; i != options.size(); i++){
        if (rows + i >= height)
            break;
        if (i == selection)
            wattron(_window, COLOR_PAIR(1));
        mvwprintw(_window, rows + i, 1, options[i].c_str());
        wattroff(_window, COLOR_PAIR(1));
    }
    refresh();
    }

string dialog_window::show(){
    selection = 0;
    int c;
    bool cont = true;
    draw();
    curs_set(0);
    while(cont){
        c = wgetch(_window);
        switch(c){
            case KEY_DOWN:
                if (selection < options.size() - 1)
                    selection++;
                break;
            case KEY_UP:
                if (selection > 0)
                    selection--;
                break;
            case KEY_ENTER:
            case 10:
                cont = false;
            break;
        }
        draw();
    }
    curs_set(1);
    if (options.empty())
        return "";
    return options[selection];
}
