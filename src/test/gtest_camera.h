#ifndef GTEST_CAMERA_H
#define GTEST_CAMERA_H
#include <gtest/gtest.h>
#include "camera.h"

class Test_Camera
{
public:
    bool checkIsStart(int id)
    {
        camera.start(id);
        return true;
    }

    bool checkIsStop(int id)
    {
        camera.start(id);
        camera.stop();
        return true;
    }

    Camera camera;
};

TEST(camera_test, checkIsStart)
{
    Test_Camera test;
    EXPECT_EQ(test.checkIsStart(0), true);
}

TEST(camera_test, checkIsStop)
{
    Test_Camera test;
    EXPECT_EQ(test.checkIsStop(0), true);
}



#endif
