#include <events/event.h>
#include <string>
#include <iostream>

using namespace std;

event::event(void (*func)(event*), string payload){
    this->payload = payload;
    this->func_ptr = func;
}

string event::get_payload(){
    return payload;
}

void event::run_function(){
    func_ptr(this);
}
