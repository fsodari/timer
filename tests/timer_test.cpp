#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include <iostream>

extern "C"
{
#include "timer/timer_observer.h"
#include "timer/timer_source.h"
}

TEST_GROUP(TIMER)
{
    timer_source source;
    timer_observer *observer;

    void setup()
    {
        source = timer_source_create();
        observer = timer_observer_create();
    }

    void teardown()
    {
        timer_source_destroy(source);
    }
};

TEST(TIMER, fail)
{
    FAIL("failedtimer");
}