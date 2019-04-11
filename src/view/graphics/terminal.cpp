#include <view/graphics/terminal.h>
#include <controller/events/event_handler.h>
#include <controller/debugger/debugger.h>
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
    handler.listen("print", this, &terminal::print_string);
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
    if (history_pos == 0){
        mvwprintw(_window, height - 3, 0, str.c_str());
    } else {
        mvwprintw(_window, height - 3, 0, input_history[input_history.size() - history_pos].c_str());
    }
    wmove(_window, height - 3, cursor_pos);
    refresh();
}

void terminal::read_input(){
    int c;
    while((c = wgetch(_window)) != ERR){
        switch(c){
            case KEY_ENTER:
            case 10:
                enter_key();
                break;
            case KEY_DC:
                delete_key();
                break;
            case KEY_BACKSPACE:
                backspace_key();
                break;
            case KEY_LEFT:
                left_key();
                break;
            case KEY_RIGHT:
                right_key();
                break;
            case KEY_UP:
                up_key();
                break;
            case KEY_DOWN:
                down_key();
                break;
            case KEY_HOME:
                home_key();
                break;
            case KEY_END:
                end_key();
                break;
            default:
                if (c >= 32 && c <= 255){
                    add_char(c);
                } else {
                    debug << "Got unexpected key: " << (int) c << endl;
                }
        }
        update();
    }
}


void terminal::add_char(char c){
    set_current_string();
    if (history_pos > 0){
        this->str = input_history[input_history.size() - history_pos];
        history_pos = 0;
    }
    this->str.insert(cursor_pos, 1, c);
    // For unicode: only update cursor_pos once per unicode character
    if (!(c & 0x80) || (c & 0xC0) != 0x80) {
        cursor_pos++;
    }
}

void terminal::enter_key(){
    set_current_string();
    handler.emit<string>("input", this->str);
    add_line(this->str);
    input_history.push_back(this->str);
    if (input_history.size() > 30){
        input_history.erase(input_history.begin());
    }
    this->str = unicode_string("");
    cursor_pos = 0;
    str_length = 0;
}

void terminal::delete_key(){
    set_current_string();
    if (cursor_pos != this->str.size()){
        this->str.erase(cursor_pos, 1);
    }
}

void terminal::backspace_key(){
    set_current_string();
    if (cursor_pos > 0){
        this->str.erase(cursor_pos - 1, 1);
        cursor_pos--;
    }
}

void terminal::left_key(){
    if (cursor_pos > 0){
        cursor_pos--;
    }
}

void terminal::right_key(){
    if (cursor_pos < current_string().unicode_length()){
        cursor_pos++;
    }
}

void terminal::up_key(){
    if (history_pos < input_history.size()){
        history_pos++;
        cursor_pos = input_history[input_history.size() - history_pos].unicode_length();
    }
}

void terminal::down_key(){
    if (history_pos > 0){
        history_pos--;
        if (history_pos == 0){
            cursor_pos = this->str.unicode_length();
        } else {
            cursor_pos = input_history[input_history.size() - history_pos].unicode_length();
        }
    }
}

void terminal::home_key(){
    cursor_pos = 0;
}

void terminal::end_key(){
    cursor_pos = current_string().unicode_length();
}

const unicode_string& terminal::current_string(){
    if (history_pos == 0){
        return this->str;
    } else {
        return input_history[input_history.size() - history_pos];
    }
}

void terminal::set_current_string(){
    /**
     *  Set current string that is being viewed in input history to the
     *  terminal's current input string.
     */
    if (history_pos != 0){
        this->str = input_history[input_history.size() - history_pos];
        history_pos = 0;
    }
}

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
