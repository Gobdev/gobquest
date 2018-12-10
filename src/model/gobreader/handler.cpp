#include <model/gobreader/handler.h>

handler::handler(){}

handler::~handler(){}


void handler::read_file(fs::path filepath){
    token_reader.tokenize(filepath);
}

void handler::error(){

}

void handler::start(){

}
