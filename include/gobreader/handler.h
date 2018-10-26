#ifndef HANDLER_H
#define HANDLER_H
#include <string>
#include <map>
#include <vector>
#include <gobreader/area.h>
#include <gobreader/tokenizer.h>

using namespace std;

namespace fs = boost::filesystem;

class handler {
    public:
        handler();
        ~handler();
        void read_file(fs::path filepath);

    private:
        tokenizer token_reader;
        void start();
        void error();
        void text();
        void textnl();
        void name();
        void exits();
        void exit();
        void exit_name();
        void path();
        void requirements();
        map<string, area*> area_map;
};

#endif // HANDLER_H
