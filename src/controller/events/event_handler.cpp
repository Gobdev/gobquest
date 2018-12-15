#include <controller/events/event_handler.h>


event_handler::event_handler() : term(terminal(0, 0, COLS * 3 / 4, LINES)){}

void event_handler::run(){
    term.run();
}
