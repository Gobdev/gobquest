#include <controller/events/event_handler.h>

event_handler handler;

void temp(string str){
    string s = "Got command " + str + ". Amazing!";
    handler.emit<string>("print", s);
}

event_handler::event_handler(){
    this->listen<string>("input", temp);
}

void event_handler::run(function<void()> f1, function<void()> f2, function<void(string)> debug_print){
    int i = 0;
    while(true){
        try {
            // Check if terminal has new input
            //term->read_input();
            f1();
            if ((++i % 1000000) == 0){
                f2();
                //term->test();
            }
            do_next();
        } catch(exception& e){
            debug_print(string(e.what()));
        }
    }
}

void event_handler::do_next(){
    queue<event*>* q;
    if (high_prio.size() > 0 && high_prio_streak < 3){
        q = &high_prio;
        high_prio_streak++;
    } else if (low_prio.size() > 0){
        q = &low_prio;
        high_prio_streak = 0;
    } else {
        return;
    }
    event* e = q->front();
    e->run_function();
    q->pop();
    delete e;
}
