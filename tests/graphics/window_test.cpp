#include <gtest/gtest.h>
#include <graphics/window.h>

class test_window : public window {
    public:
        test_window(int x, int y, int width, int height);
        int get_color_pair();
};

test_window::test_window(int x, int y, int width, int height) :
        window(x, y, width, height){}

int test_window::get_color_pair(){
    return colorPair;
}

TEST (WindowTest, DefaultNormalWindow) {
    test_window w(10, 10, 20, 20);
    EXPECT_EQ (w.get_color_pair(), 2);
}

TEST (WindowTest, SetCurrentWindow) {
    test_window w(10, 10, 20, 20);
    w.setCurrentWindow();
    EXPECT_EQ (w.get_color_pair(), 1);
}

TEST (WindowTest, SetNormalWindow) {
    test_window w(10, 10, 20, 20);
    w.setCurrentWindow();
    ASSERT_EQ (w.get_color_pair(), 1);
    w.setNormalWindow();
    EXPECT_EQ (w.get_color_pair(), 2);
}
