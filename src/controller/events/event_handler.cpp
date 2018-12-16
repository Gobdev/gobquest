#include <controller/events/event_handler.h>


event_handler::event_handler() : term(terminal(0, 0, COLS * 3 / 4, LINES)){
    term.update();
}

void event_handler::run(){
    int i = 0;
    while(true){
        // Check if terminal has new input
        term.read_input();
        if ((++i % 100000) == 0){
            term.test();
        }
        // Check queue
    }
}
