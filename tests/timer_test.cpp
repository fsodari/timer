#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include <iostream>

extern "C"
{
#include "timer/timer.h"
}

uint32_t total_ticks = 0;

static void timer_ticks(source timer_source, uint32_t ticks)
{
    for (uint32_t i = 0; i < ticks; i++) {
        source_update(timer_source, total_ticks++);
    }
}

TEST_GROUP(TIMER)
{
    source timer_source;

    void setup()
    {
        timer_source = source_create();
        total_ticks = 0;
    }

    void teardown()
    {
        source_destroy(timer_source);
    }
};

TEST(TIMER, createanddestroy)
{
    timer t1, t2;
    uint32_t counter;
    int timedout;

    t1 = timer_new(timer_source, 10);
    CHECK(t1);
    t2 = timer_new(timer_source, 20);
    CHECK(t2);

    counter = timer_get_counter(t1);
    CHECK_EQUAL(0, counter);
    counter = timer_get_counter(t2);
    CHECK_EQUAL(0, counter);

    timer_ticks(timer_source, 10);

    counter = timer_get_counter(t1);
    CHECK_EQUAL(10, counter);
    counter = timer_get_counter(t2);
    CHECK_EQUAL(10, counter);

    timedout = timer_timeout(t1, 0);
    CHECK(timedout);
    timedout = timer_timeout(t2, 0);
    CHECK_FALSE(timedout);

    timer_destroy(t1);
    timer_destroy(t2);
}