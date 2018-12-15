#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <controller/events/event.h>
#include <view/graphics/terminal.h>
#include <queue>

class event_handler {
private:
    queue<event_interface> low_prio;
    queue<event_interface> high_prio;
    terminal term;

public:
    event_handler();
    void run();
};

#endif //EVENT_HANDLER_H
