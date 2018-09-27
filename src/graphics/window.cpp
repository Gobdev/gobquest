#include <graphics/window.h>
#include <string>

using namespace std;

window::window(int x, int y, int width, int height){
    this -> x = x;
    this -> y = y;
    this -> width = width;
    this -> height = height;
    box_window = newwin(this -> height, this -> width,
                        this -> y, this -> x);
    _window = newwin(this -> height - 2, this -> width - 2,
                     this -> y + 1, this -> x + 1);
    wborder(_window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    setNormalWindow();
}

window::~window(){
    wborder(box_window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
  	wrefresh(box_window);
  	delwin(_window);
  	delwin(box_window);
}

void window::draw_border(){
    wattron(box_window, COLOR_PAIR(colorPair));
    box(box_window, 0, 0);
    wattroff(box_window, COLOR_PAIR(colorPair));
}

void window::refresh(){
    wrefresh(box_window);
    wrefresh(_window);
}

void window::setCurrentWindow(){
    this -> colorPair = 1;
}

void window::setNormalWindow(){
    this -> colorPair = 2;
}
