#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <tuple>
#include <utility>
#include <functional>

using namespace std;

class event_interface {
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

template <class... Args> class event : event_interface{
private:
    function<void(Args... args)> func_ptr;
    tuple<Args...> payload;

public:
    event(function<void(Args... args)> func,  Args&&... args) :
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

#endif //EVENT_H
