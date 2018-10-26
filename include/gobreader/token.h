#ifndef GOBREADER_TOKEN_H
#define GOBREADER_TOKEN_H
#include <string>
#include <map>

using namespace std;

enum token_type {
    INDENT, DEDENT, TEXT, NEWLINE, NAME, EXIT, PATH, COLON, END
};

const map<token_type, string> token_string = {
    {INDENT,  "indent" },
    {DEDENT,  "dedent" },
    {TEXT,    "text" },
    {NEWLINE, "newline"},
    {NAME,    "name"   },
    {EXIT,    "exit"   },
    {PATH,    "path"   },
    {COLON,   "colon"  },
};

struct token {
    token_type type;
    string str;
    token* next;
    token(token_type type, string str): type(type), str(str), next(NULL){};
    token(token_type type): type(type), str(""), next(NULL){};
    string repr(){ return token_string.at(type); };
};

#endif //GOBREADER_TOKEN_H
