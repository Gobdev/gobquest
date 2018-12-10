#ifndef GOBREADER_TOKENIZER_H
#define GOBREADER_TOKENIZER_H
#include <string>
#include <model/gobreader/token.h>
#include <model/gobreader/linked_list.h>
#include <boost/filesystem.hpp>

using namespace std;

namespace fs = boost::filesystem;

class tokenizer {

    public:
        tokenizer();
        tokenizer(fs::path filepath);
        void tokenize(fs::path filepath);
        ~tokenizer();

        /*std::string get_token_value();
        bool is_done();
        bool next_is(Token_Type type);
        bool lookahead(Token_Type type);
        void print_all();*/
        token get_current_token();
        int get_token_count();
        void print_all();
        linked_iterator<token> begin();
        linked_iterator<token> end();

    private:
        void parse_indents(string& line);
        void tokenize(ifstream& file);
        /*void create_new_token(token_type type, std::string token_string);*/
        linked_list<token> tokens;
        vector<string> indents = {};

};


#endif //GOBREADER_TOKENIZER_H
