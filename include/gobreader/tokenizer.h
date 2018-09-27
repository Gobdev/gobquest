#ifndef GOBREADER_TOKENIZER_H
#define GOBREADER_TOKENIZER_H
#include <string>
#include <gobreader/token.h>
#include <gobreader/linked_list.h>
#include <boost/filesystem.hpp>

using namespace std;

namespace fs = boost::filesystem;

class tokenizer {

    public:
        tokenizer(fs::path filepath);
        ~tokenizer();
        /*void tokenize();
        std::string get_token_value();
        bool is_done();
        bool next_is(Token_Type type);
        bool lookahead(Token_Type type);
        void print_all();*/
        token get_current_token();
        int get_token_count();

    private:
        void tokenize(ifstream& file);
        /*void create_new_token(token_type type, std::string token_string);*/
        linked_list<token> tokens;

};


#endif //GOBREADER_TOKENIZER_H
