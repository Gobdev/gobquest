#include <iostream>
#include <graphics/terminal.h>
#include <graphics/dialog_window.h>
#include <entities/player.h>
#include <cstdlib> 
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

#define WIDTH 30
#define HEIGHT 10
#define DEFAULT_PATH "/usr/local/gobquest"

string welcome_screen(string message, int rows, int cols){
    dialog_window win = dialog_window(cols/4, rows/4, cols/2, rows/2, message);
    const char* env_p = getenv("GOBQUEST_DIR");
    fs::path path = env_p ? fs::path(string(env_p)) : fs::path(DEFAULT_PATH);
    if (fs::is_directory(path)){
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(path); dir_itr != end_iter; ++dir_itr){
            if (fs::is_directory(dir_itr->status())){
              win.add_option(dir_itr->path().filename().string());
            }
        }
    }
    win.add_option("test");
    return win.show();
}

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "");
    int highlight = 1;
    int choice = 0;
    int c, return_code;
    initscr();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
    clear();
    string select = welcome_screen("Welcome to Gobquest!", LINES, COLS);
    clear();
    welcome_screen(select, LINES, COLS);
    clear();
    //noecho();
    //cbreak();	/* Line buffering disabled. pass on everything */
    terminal term(0, 0, COLS * 3 / 4, LINES);
    term.run();
    endwin();
    return return_code;
}
