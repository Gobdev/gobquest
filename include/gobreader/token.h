#ifndef GOBREADER_TOKEN_H
#define GOBREADER_TOKEN_H
#include <string>
#include <map>

using namespace std;

enum token_type {
    START = 0, INDENT, DEDENT, STRING, NEWLINE, NAME, EXIT, PATH
};

const map<token_type, string> token_string = {
    {START, "start"},
    {INDENT, "indent"},
    {DEDENT, "dedent"},
    {STRING, "string"},
    {NEWLINE, "newline"},
    {NAME, "name"},
    {EXIT, "exit"},
    {PATH, "path"},
};

struct token {
    token_type type;
    string str;
    token* next;
    token(token_type type, string str): type(type), str(str), next(NULL){};
    string repr(){ return token_string.at(type); };
};

#endif //GOBREADER_TOKEN_H
