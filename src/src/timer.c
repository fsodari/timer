#include "timer/timer.h"
#include <stdlib.h>

static void changed_time(void *instance, const uint32_t new_time);

struct timer_struct
{
    uint32_t counter;
    uint32_t period;
    source timer_source;
};

timer timer_new(source timer_source, uint32_t period)
{
    timer self = malloc(sizeof(*self));
    observer obv;

    if (self) {
        self->counter = 0;
        self->period = period;
        self->timer_source = timer_source;
        obv.instance = self;
        obv.notification = changed_time;

        source_attach(self->timer_source, &obv);
    }

    return self;
}

void timer_destroy(timer self)
{
    observer obv;
    if (self) {
        obv.instance = self;
        obv.notification = changed_time;
        source_detach(self->timer_source, &obv);
    }
    free(self);
}

void timer_set_period(timer self, uint32_t period)
{
    if (self) {
        self->period = period;
        self->counter = 0;
    }
}

uint32_t timer_get_period(const timer self)
{
    if (self) {
        return self->period;
    }

    return 0;
}

uint32_t timer_get_counter(timer self)
{
    if (self) {
        return self->counter;
    }

    return 0;
}

void timer_reset(timer self)
{
    if (self) {
        self->counter = 0;
    }
}

int timer_timeout(timer self, int reset)
{
    if (self) {
        if (self->counter >= self->period) {
            if (reset) {
                self->counter = 0;
            }
            return 1;
        }
    }
    return 0;
}

static void changed_time(void *instance, const uint32_t new_time)
{
    timer self = instance;
    (void)new_time;
    if (self) {
        if (self->counter++ >= self->period) {
            self->counter = self->period;
        }
    }
//    if (self) {
//        self->counter = new_time;
//    }
}