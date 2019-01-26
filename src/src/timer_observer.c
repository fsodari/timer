#include "timer/timer_observer.h"
#include <stdlib.h>

timer_observer *timer_observer_create(void)
{
    timer_observer *self = malloc(sizeof(*self));
    if (self) {

    }

    return self;
}

void timer_observer_destroy(timer_observer *self)
{
    if (self) {
        free(self);
    }
}
