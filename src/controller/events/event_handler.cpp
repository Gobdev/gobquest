#include <controller/events/event_handler.h>

event_handler handler;

void temp(string str){
    string s = "Got command " + str + ". Amazing!";
    handler.emit<string>("print", s);
}

event_handler::event_handler(){
    this->listen<string>("input", temp);
}

void event_handler::run(function<void()> f1, function<void()> f2){
    int i = 0;
    while(true){
        // Check if terminal has new input
        //term->read_input();
        f1();
        if ((++i % 1000000) == 0){
            f2();
            //term->test();
        }
        do_next();
    }
}

void event_handler::do_next(){
    queue<event*>& q = high_prio.size() > 0 ? high_prio : low_prio;
    if (q.size() <= 0){
        return;
    }
    event* a = q.front();
    a->run_function();
    q.pop();
    delete a;
}
