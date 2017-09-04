#include <graphics/window.h>
#include <string>

using namespace std;

window::window(int x, int y, int width, int height){
    this -> x = x;
    this -> y = y;
    this -> width = width;
    this -> height = height;
    this -> history;
    box_window = newwin(height, width, y, x);
    _window = newwin(height - 2, width - 2, y + 1, x + 1);
    wborder(_window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    update();

}

window::~window(){
    wborder(box_window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(box_window);
	delwin(_window);
	delwin(box_window);
}

void window::setCurrentWindow(){
    this -> colorPair = 1;
}

void window::setNormalWindow(){
    this -> colorPair = 2;
}

void window::update(){
    wattron(box_window, COLOR_PAIR(colorPair));
    box(box_window, 0, 0);
    wattroff(box_window, COLOR_PAIR(colorPair));
    int index = history.size() > height - 3 ? history.size() - height + 3 : 0;
    int start_y = index != 0 ? 0 : height - history.size() - 3;
    for (int i = index; i < history.size(); i++){
        mvwprintw(_window, start_y + i - index, 0, history[i].c_str());
    }
    wmove(_window, height - 3, 0);
    wrefresh(box_window);
    wrefresh(_window);
}

int window::run(){
    char c[150];
    bool cont = true;
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
