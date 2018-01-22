#include <gtest/gtest.h>
#include <graphics/window.h>

class test_window : window {
    public:
        test_window(int x, int y, int width, int height);
        int get_color_pair();
};

test_window::test_window(int x, int y, int width, int height) :
        window(x, y, width, height){}

int test_window::get_color_pair(){
    return colorPair;
}

TEST (WindowTest, DefaultColorPair) {
    test_window w(10, 10, 20, 20);
    ASSERT_EQ (w.get_color_pair(), 2);
}
