#include <view/graphics/terminal.h>
#include <controller/events/event_handler.h>
#include <string>

using namespace std;

void f(){
    ;
}

terminal::terminal(int x, int y, int width, int height) :
                   window (x, y, width, height) {
    nodelay(_window, TRUE);
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
            default:
                this->str.push_back(c);
        }
    }
}

void terminal::print_string(string str){
    size_t pos = 0;
    string token;
    add_line(str);
    /*while ((pos = str.find('\n')) != string::npos) {
        token = str.substr(0, pos);
        add_line(token);
        str.erase(0, pos + 1);
    }*/
}

void terminal::add_line(string line){
    this->history.push_back(line);
    if (history.size() > 100){
        history.erase(history.begin());
    }
    update();
}

void terminal::test(){
    update();
}
