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

public:
    event_handler();
    void run(function<void()> f1, function<void()> f2);
    void do_next();

    template <class... Args>
    void emit(string description, Args&&... args){
        auto current_map = listeners<function<void(Args... args)>>;
        auto it = current_map.find(description);
        if (it != current_map.end()){
            function<void(Args... args)> func = it->second;
            event* a = new event_templated<Args...>(func, forward<Args>(args)...);
            high_prio.push(a);
        }
    }

    template <class T, class... Args>
    void emit_with_object(string description, T* obj, Args&&... args){
        auto current_map = listeners<function<void(T*, Args... args)>>;
        auto it = current_map.find(description);
        if (it != current_map.end()){
            function<void(T*, Args... args)> func = it->second;
            event* a = new event_templated_with_object<T, Args...>(func, obj, forward<Args>(args)...);
            high_prio.push(a);
        }
    }

    template <class... Args>
    void listen(string description, void func(Args... args)){
        function<void(Args... args)> a = func;
        auto p = std::pair<string, function<void(Args... args)>>(description, a);
        listeners<function<void(Args... args)>>.insert(p);
    }

    template <class T, class... Args>
    void listen_with_object(string description, void (T::*func)(Args... args)){
        function<void(T*, Args... args)> a = func;
        auto p = std::pair<string, function<void(T*, Args... args)>>(description, a);
        listeners<function<void(T*, Args... args)>>.insert(p);
    }

};

extern event_handler handler;

#endif //EVENT_HANDLER_H