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

template<class... Args>
class function_holder{
public:
    virtual event* create_event(Args... args) = 0;
};

template<class... Args>
class function_holder_static : public function_holder<Args...> {
private:
    function<void(Args... args)> func;

public:
    function_holder_static(void func(Args... args)) : func(func) {};

    event* create_event(Args... args) {
        return new event_templated<Args...>(func, forward<Args>(args)...);;
    }
};

template<class T, class... Args>
class function_holder_member : public function_holder<Args...> {
private:
    function<void(T*, Args... args)> func;
    T* obj;

public:
    function_holder_member(void (T::*func)(Args... args), T* obj) : func(func), obj(obj) {};

    event* create_event(Args... args) {
        return new event_templated_with_object<T, Args...>(func, obj, forward<Args>(args)...);
    }
};

class event_handler {
private:
    queue<event*> low_prio;
    queue<event*> high_prio;

public:
    event_handler();
    void run(function<void()> f1, function<void()> f2);
    void do_next();

    template <class... Args>
    void emit(string description, Args... args){
        auto current_map = listeners<function_holder<Args...>*>;
        auto it = current_map.find(description);
        if (it != current_map.end()){
            function_holder<Args...>* holder = it->second;
            event* a = holder->create_event(forward<Args>(args)...);
            high_prio.push(a);
        }
    }

    template <class... Args>
    void listen(string description, void func(Args... args)){
        function_holder<Args...>* a = new function_holder_static<Args...>(func);
        auto p = std::pair<string, function_holder<Args...>*>(description, a);
        listeners<function_holder<Args...>*>.insert(p);
    }

    template <class T, class... Args>
    void listen(string description, void (T::*func)(Args... args), T* obj){
        function_holder<Args...>* a = new function_holder_member<T, Args...>(func, obj);
        auto p = std::pair<string, function_holder<Args...>*>(description, a);
        listeners<function_holder<Args...>*>.insert(p);
    }

};

extern event_handler handler;

#endif //EVENT_HANDLER_H
