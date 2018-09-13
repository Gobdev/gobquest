#ifndef GOBREADER_TOKEN_H
#define GOBREADER_TOKEN_H
#include <string>

using namespace std;

enum token_type {
    START, INDENT, DEDENT, STRING, NEWLINE, NAME, EXIT, PATH
};

struct token {
    token_type type;
    string str;
    token* next;
    token(token_type type, string str): type(type), str(str), next(NULL){};
};

#endif //GOBREADER_TOKEN_H
