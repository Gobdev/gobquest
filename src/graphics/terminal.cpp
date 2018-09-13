#include <graphics/terminal.h>
#include <string>

using namespace std;

terminal::terminal(int x, int y, int width, int height) :
                   window (x, y, width, height){}

terminal::~terminal(){}

void terminal::update(){
    draw_border();
    int size = (int) history.size();
    int index = size > height - 3 ? size - height + 3 : 0;
    int start_y = index != 0 ? 0 : height - history.size() - 3;
    for (int i = index; i < size; i++){
        mvwprintw(_window, start_y + i - index, 0, history[i].c_str());
    }
    mvwprintw(_window, 0, width - 10, "%d", history.size());
    wmove(_window, height - 3, 0);
    refresh();
}

int terminal::run(){
    char c[150];
    bool cont = true;
    update();
    while(cont){
        wgetstr(_window, c);
        this -> str = string(c);
        this -> history.push_back(str);
        if (history.size() > 100){
            history.erase(history.begin());
        }
        update();
    }
    return 0;
}
