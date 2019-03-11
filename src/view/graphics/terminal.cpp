#include <view/graphics/terminal.h>
#include <controller/events/event_handler.h>
#include <string>
#include <sstream>

using namespace std;

void f(){
    ;
}

terminal::terminal(int x, int y, int width, int height) :
                   window (x, y, width, height) {
    nodelay(_window, TRUE);
    keypad(_window, TRUE);
    handler.listen<terminal, string>("print", &terminal::print_string, this);
    update();
}

terminal::~terminal(){}

void terminal::noted(){
    history.push_back("Noted!");
    update();
}

void terminal::update(){
    draw_border();
    int size = (int) history.size();
    int index = size > height - 3 ? size - height + 3 : 0;
    int start_y = index != 0 ? 0 : height - history.size() - 3;
    for (int i = index; i < size; i++){
        mvwprintw(_window, start_y + i - index, 0, history[i].c_str());
    }
    mvwprintw(_window, 0, width - 10, "%d", history.size());
    if (str.size()){
        mvwprintw(_window, height - 3, 0, str.c_str());
    } else {
        wmove(_window, height - 3, 0);
    }
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

void terminal::read_input(){
    int c;
    while((c = wgetch(_window)) != ERR){
        switch(c){
            case KEY_ENTER:
            case 10:
                // Call event handler
                handler.emit<string>("input", this->str);
                add_line(this->str);
                this->str = "";
                break;
            case KEY_DC:
                delete_next();
                break;
            case KEY_BACKSPACE:
                backspace();
                break;
            case KEY_LEFT:
                left();
                break;
            case KEY_RIGHT:
                right();
                break;
            case KEY_UP:
                up();
                break;
            case KEY_DOWN:
                down();
                break;
            default:
                if (c >= 32){
                    this->str.push_back(c);
                } else {
                    ostringstream debug_str;
                    debug_str << "Got unexpected key: " << (int) c;
                    print_debug(debug_str.str());
                    print_debug(this->str);
                }
        }
    }
}


void terminal::delete_next(){}

void terminal::backspace(){}

void terminal::left(){}

void terminal::right(){}

void terminal::up(){}

void terminal::down(){}

void terminal::print_string(string str){
    size_t pos = 0;
    string token;
    while ((pos = str.find('\n')) != string::npos) {
        token = str.substr(0, pos);
        add_line(token);
        str.erase(0, pos + 1);
    }
    add_line(str);
}

void terminal::add_line_inner(string line){
    /**
     *  Add a line that is verified to be the correct length.
     *
     *  Note: This function should not be used directly except for in add_line,
     *        use add_line instead.
     */
    this->history.push_back(line);
    if (history.size() > 100){
        history.erase(history.begin());
    }
    update();
}

void terminal::add_line(string line){
    /**
     *  Splice a given line into segments that fit in the window and then
     *  add the segments to history and print them.
     */
    while((int) line.length() > width - 2){
        string sub = line.substr(0, width - 2);
        add_line_inner(sub);
        line.erase(0, width - 1);
    }
    add_line_inner(line);
}

void terminal::print_debug(string str){
    add_line("==DEBUG PRINT== " + str);
}

void terminal::test(){
    update();
}
