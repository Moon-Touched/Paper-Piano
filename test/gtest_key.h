#ifndef GTEST_KEY_H
#define GTEST_KEY_H
#include <gtest/gtest.h>
#include "key.h"

class Test_Key
{
public:
    bool checkC()
    {
        Key keyC("C","sounds/do1.mp3");
        keyC.press();
        return true;
    }
    bool checkD()
    {
        Key keyD("D","sounds/re1.mp3");
        keyD.press();
        return true;
    }
    bool checkE()
    {
        Key keyE("E","sounds/mi1.mp3");
        keyE.press();
        return true;
    }
    bool checkF()
    {
        Key keyF("F","sounds/fa1.mp3");
        keyF.press();
        return true;
    }
    bool checkG()
    {
        Key keyG("G","sounds/so1.mp3");
        keyG.press();
        return true;
    }
    bool checkA()
    {
        Key keyA("A","sounds/la1.mp3");
        keyA.press();
        return true;
    }
    bool checkB()
    {
        Key keyB("B","sounds/xi1.mp3");
        keyB.press();
        return true;
    }
};

TEST(test_key,checkC)
{
    Test_Key test;
    EXPECT_EQ(test.checkC(), true);
}

TEST(test_key,checkD)
{
    Test_Key test;
    EXPECT_EQ(test.checkD(), true);
}
TEST(test_key,checkE)
{
    Test_Key test;
    EXPECT_EQ(test.checkE(), true);
}

TEST(test_key,checkF)
{
    Test_Key test;
    EXPECT_EQ(test.checkF(), true);
}

TEST(test_key,checkG)
{
    Test_Key test;
    EXPECT_EQ(test.checkG(), true);
}

TEST(test_key,checkA)
{
    Test_Key test;
    EXPECT_EQ(test.checkA(), true);
}

TEST(test_key,checkB)
{
    Test_Key test;
    EXPECT_EQ(test.checkB(), true);
}

#endif
