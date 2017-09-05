#include <iostream>
#include <graphics/terminal.h>

using namespace std;

#define WIDTH 30
#define HEIGHT 10

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "");
    int highlight = 1;
    int choice = 0;
    int c, return_code;
    initscr();
	start_color();
    clear();
    //noecho();
    //cbreak();	/* Line buffering disabled. pass on everything */
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
    terminal term(0, 0, COLS * 3 / 4, LINES);
    term.run();
    endwin();
    return return_code;
}
