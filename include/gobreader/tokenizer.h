#ifndef GOBREADER_TOKENIZER_H
#define GOBREADER_TOKENIZER_H
#include <boost/filestream.hpp>
#include <string>

namespace fs = boost::filestream;

enum token_type { start };

class token {
    public:
        token();
};

class tokenizer {
    
    public:
        tokenizer(fs::path filepath);
        ~tokenizer();

    private:
        
};


#endif
