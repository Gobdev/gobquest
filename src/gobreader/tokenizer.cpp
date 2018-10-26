#include <gobreader/token.h>
#include <gobreader/tokenizer.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

tokenizer::tokenizer(){}

tokenizer::tokenizer(fs::path filepath) {
    tokenize(filepath);
}

void tokenizer::tokenize(fs::path filepath){
    ifstream file;
    file.open(filepath.string());
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

void tokenizer::parse_indents(string& line){
    for (uint i = 0; i < indents.size(); i++){
        string indent = indents[i];
        if (line.substr(0, indent.size()) == indent){
            line = line.substr(indent.size());
        } else {
            for (uint j = 0; j < indents.size() - i; j++){
                tokens.push(token(DEDENT));
            }
            indents.erase(indents.begin() + i, indents.end());
            break;
        }
    }
    uint idx = 0;
    for (; idx < line.size(); idx++){
        if (line[idx] != ' ' && line[idx] != '\t'){
            break;
        }
    }
    if (idx > 0){
        tokens.push(token(INDENT, line.substr(0, idx)));
        indents.push_back(line.substr(0, idx));
        line = line.substr(idx);
    }
}

void tokenizer::tokenize(ifstream& file){
    string line;
    size_t pos;
    while (file.good()){
        std::getline(file, line);
        parse_indents(line);
        while(!line.empty()){
            if (line.substr(0, 5) == "name:"){
                tokens.push(token(NAME, "name:"));
                line = line.substr(5);
            } else if (line.substr(0, 5) == "exit:"){
                tokens.push(token(EXIT, "exit:"));
                line = line.substr(5);
            } else if ((pos = line.find(':')) != string::npos){
                tokens.push(token(TEXT, line.substr(0, pos)));
                tokens.push(token(COLON, ":"));
                line = line.substr(pos + 1);
            } else {
                tokens.push(token(TEXT, line));
                break;
            }
        }
    }
    tokens.push(token(END));
}

void tokenizer::print_all(){
    for (token t : tokens){
        cout << "token type: " << t.repr() << ", value: " << t.str << endl;
    }
}


linked_iterator<token> tokenizer::begin(){
    return tokens.begin();
}

linked_iterator<token> tokenizer::end(){
    return tokens.end();
}
