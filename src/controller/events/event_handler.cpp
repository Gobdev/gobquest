#include <controller/events/event_handler.h>

event_handler handler;

event_handler::event_handler(){}

void event_handler::run(terminal* term){
    this->term = term;
    int i = 0;
    while(true){
        // Check if terminal has new input
        term->read_input();
        if ((++i % 1000000) == 0){
            term->test();
        }
        //do_next();
    }
}

void event_handler::do_next(){
    queue<event*> q = high_prio.size() > 0 ? high_prio : low_prio;
    if (q.size() <= 0){
        return;
    }
    event* a = q.front();
    a->run_function();
    q.pop();
}
