#include <gtest/gtest.h>
#include <cstdlib>
#include <model/gobreader/linked_list.h>
#include <model/gobreader/tokenizer.h>
#include <sstream>
#include <iostream>

using namespace std;

const string test_dir = string(std::getenv("GOBTEST_DIR")) + "/gobreader/gobfiles/";

vector<token_type> simple_token_order = {
    TEXT, COLON, INDENT, NAME, TEXT, EXIT, INDENT, TEXT, TEXT, DEDENT,
    DEDENT, TEXT, COLON, INDENT, NAME, TEXT, EXIT, INDENT, TEXT, TEXT,
    DEDENT, DEDENT, END
};

TEST (GobreaderTokenTest, CreateToken) {
    token* a = new token(TEXT, "test");
    EXPECT_EQ(a->str, "test");
    EXPECT_EQ(a->type, TEXT);
    delete a;
}

TEST (GobreaderTokenizerTest, CreateTokenizer){
    tokenizer t(fs::path(test_dir + "simple.gob"));
    uint i = 0;
    for (token current_token : t){
        EXPECT_EQ(current_token.type, simple_token_order[i]);
        i++;
    }
    EXPECT_EQ(i, simple_token_order.size());
}

TEST (GobreaderLinkedListTest, CreateLinkedList){
    linked_list<string> a;
    a.push("test");
    a.push("test2");
    a.push("test3");
    vector<string> results = {"test", "test2", "test3"};
    int i = 0;
    for (string b : a){
        EXPECT_EQ(b, results[i]);
        i++;
    }
    a.pop();
    a.pop();
    for (string b : a){
        EXPECT_EQ(b, "test");
    }
}

TEST (GobreaderLinkedListTest, CreateReversedLinkedList){
    linked_list<string> a;
    a.push("test");
    a.push("test2");
    a.push("test3");
    vector<string> results = {"test3", "test2", "test"};
    int i = 0;
    for (auto b = a.rbegin(); b != a.rend(); b--){
        EXPECT_EQ(*b, results[i]);
        i++;
    }
    a.pop();
    a.pop();
    for (string b : a){
        EXPECT_EQ(b, "test");
    }
}
