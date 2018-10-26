#include <graphics/terminal.h>
#include <string>

using namespace std;

terminal::terminal(int x, int y, int width, int height) :
                   window (x, y, width, height) {
   update();
}

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
    bool cont = true;
    while(cont){
        this->read_command();
    }
    return 0;
}

string& terminal::read_command(){
    char c[150];
    wgetstr(_window, c);
    this->str = string(c);
    this->history.push_back(str);
    if (history.size() > 100){
        history.erase(history.begin());
    }
    update();
    return this->str;
}
