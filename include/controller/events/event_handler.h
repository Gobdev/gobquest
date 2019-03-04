#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <controller/events/event.h>
#include <view/graphics/terminal.h>
#include <string>
#include <functional>
#include <map>
#include <queue>
#include <iostream>

using namespace std;

template<class T>
map<string, T> listeners;

class event_handler {
private:
    queue<event*> low_prio;
    queue<event*> high_prio;
    terminal* term;

public:
    event_handler();
    void run(terminal* term);
    void do_next();

    template <class... Args>
    void emit(string description, Args&&... args){
        auto current_map = listeners<function<void(Args... args)>>;
        auto it = current_map.find(description);
        if (it != current_map.end()){
            function<void(Args... args)> func = it->second;
            cout << description << " event noted!" << endl;
            event* a = new event_templated<Args...>(func, forward<Args>(args)...);
            high_prio.push(a);
        }
    }

    template <class... Args>
    void listen(string description, void func(Args... args)){
        function<void(Args... args)> a = func;
        auto p = std::pair<string, function<void(Args... args)>>(description, a);
        listeners<function<void(Args... args)>>.insert(p);
    }

};

extern event_handler handler;

#endif //EVENT_HANDLER_H
