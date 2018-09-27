#include <gtest/gtest.h>
#include <cstdlib>
#include <gobreader/linked_list.h>
#include <gobreader/tokenizer.h>
#include <iostream>

using namespace std;

const string test_dir = string(std::getenv("GOBTEST_DIR")) + "/gobreader/gobfiles/";

TEST (GobreaderTokenTest, CreateToken) {
    token* a = new token(STRING, "test");
    EXPECT_EQ(a->str, "test");
    EXPECT_EQ(a->type, STRING);
    delete a;
}

TEST (GoreaderTokenizerTest, CreateTokenizer){
    tokenizer t(fs::path(test_dir + "simple.gob"));
    t.print_all();
    EXPECT_EQ(t.get_current_token().repr(), "start");
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
