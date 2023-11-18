#include <unity.h>
#include "cbuffer.h"

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_circular_buffer_empty_after_init()
{
    cbuffer_t buff;

    cbuffer_init(&buff);

    TEST_ASSERT_TRUE(cbuffer_empty(&buff));
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_circular_buffer_empty_after_init);

    UNITY_END();
}