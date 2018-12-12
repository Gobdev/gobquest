#include <iostream>
#include <view/graphics/terminal.h>
#include <view/graphics/dialog_window.h>
#include <cstdlib>
#include <boost/filesystem.hpp>
#include <events/event.h>

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
    win.add_option("Quit");

    string ret = win.show();
    return ret;
}

void test(event* e){
    cout << e->get_payload() << endl;
}

int main(int argc, char* argv[]){
    event e(test, "this is the payload");
    e.run_function();
    return 0;
    setlocale(LC_ALL, "");
    int return_code = 0;
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    clear();
    string select = welcome_screen("Welcome to Gobquest!", LINES, COLS);
    clear();
    string a = "";
    if (select != "Quit"){
        terminal term(0, 0, COLS * 3 / 4, LINES);
        a = term.run();
        //a = term.read_command();
    }
    select = welcome_screen(a, LINES, COLS);
    endwin();
    return return_code;
}
