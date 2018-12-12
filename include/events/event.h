#ifndef EVENT_H
#define EVENT_H

#include <events/event.h>
#include <string>

using namespace std;

class event {
private:
    void (*func_ptr)(event*);
    string payload;

public:
    event(void (*func)(event*), string payload);
    string get_payload();
    void run_function();
};

#endif //EVENT_H
