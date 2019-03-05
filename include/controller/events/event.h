#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <tuple>
#include <utility>
#include <functional>

using namespace std;

class event {
public:
    virtual void run_function() = 0;
};

namespace helper
{
    template <int... Is>
    struct index {};

    template <int N, int... Is>
    struct gen_seq : gen_seq<N - 1, N - 1, Is...> {};

    template <int... Is>
    struct gen_seq<0, Is...> : index<Is...> {};
}

template <class... Args> class event_templated : public event {
private:
    function<void(Args... args)> func_ptr;
    tuple<Args...> payload;

public:
    event_templated(function<void(Args... args)> func,  Args&&... args) :
        func_ptr(forward<function<void(Args... args)>>(func)),
        payload(forward<Args>(args)...) {};

    template <class... Ts, int... Is>
    void func(std::tuple<Ts...>& tup, helper::index<Is...>){
        func_ptr(std::get<Is>(tup)...);
    }

    void func(std::tuple<Args...>& tup) {
        func(tup, helper::gen_seq<sizeof...(Args)>{});
    }

    void run_function() {
        func(payload);
    }
};

template <class T, class... Args> class event_templated_with_object : public event {
private:
    function<void(T*, Args... args)> func_ptr;
    tuple<Args...> payload;
    T* obj;

public:
    event_templated_with_object(function<void(T*, Args... args)> func,  T* obj, Args&&... args) :
        func_ptr(forward<function<void(T*, Args... args)>>(func)),
        payload(forward<Args>(args)...),
        obj(obj) {};

    template <class... Ts, int... Is>
    void func(std::tuple<Ts...>& tup, helper::index<Is...>){
        func_ptr(std::get<Is>(tup)...);
    }

    void func(std::tuple<Args...>& tup) {
        func(tup, helper::gen_seq<sizeof...(Args)>{});
    }

    void run_function() {
        function<void(Args... args)> f = bind(func_ptr, obj);
        f();
    }
};

#endif //EVENT_H
