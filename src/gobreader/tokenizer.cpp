#include <gobreader/token.h>
#include <gobreader/tokenizer.h>
#include <fstream>
#include <iostream>

using namespace std;

tokenizer::tokenizer(fs::path filepath) {
    ifstream file;
    file.open(filepath.string());
    tokens.push(token(START, ""));
    tokenize(file);
    file.close();
}

tokenizer::~tokenizer() {}

int tokenizer::get_token_count(){
    return tokens.size();
}

token tokenizer::get_current_token(){
    return tokens.front();
}

void tokenizer::tokenize(ifstream& file){
    string line;
    while (file.good()){
        std::getline(file, line);
        tokens.push(token(STRING, line));
    }
}

void tokenizer::print_all(){
    for (token t : tokens){
        cout << "token type: " << t.repr() << ", value: " << t.str << endl;
    }
}
