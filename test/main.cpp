#include <gtest/gtest.h>
#include "gtest_camera.h"
#include "gtest_key.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
