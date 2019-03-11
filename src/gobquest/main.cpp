#include <iostream>
#include <view/graphics/dialog_window.h>
#include <boost/filesystem.hpp>
#include <controller/events/event_handler.h>

using namespace std;
namespace fs = boost::filesystem;

#define WIDTH 30
#define HEIGHT 10
#define DEFAULT_PATH "/usr/local/gobquest"

string welcome_screen(string message, int rows, int cols){
    clear();
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
    win.add_option("Quit");

    string ret = win.show();
    return ret;
}

terminal* term;

void wrapper1(){
    term->read_input();
}

void wrapper2(){
    term->test();
}

void debug_print(string s){
    term->print_debug("Exception caught : " + s);
}

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "");
    int return_code = 0;
    initscr();
    //noecho();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    //string select = welcome_screen("Welcome to Gobquest!", LINES, COLS);
    string select = "not quit";
    term = new terminal(0, 0, COLS * 3 / 4, LINES);
    if (select != "Quit"){
        handler.run(wrapper1, wrapper2, debug_print);
    }
    keypad(stdscr, 0);
    endwin();
    delete term;
    return return_code;
}
