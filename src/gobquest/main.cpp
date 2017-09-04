#include <iostream>
#include <graphics/window.h>
#include <pqxx/pqxx>

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
    window main_win(0, 0, COLS, LINES);
    main_win.run();
    endwin();
    return return_code;
}
