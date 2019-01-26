#include "timer/observer.h"
#include <stdlib.h>

observer *observer_create(void)
{
    observer *self = malloc(sizeof(*self));
    if (self) {

    }

    return self;
}

void observer_destroy(observer *self)
{
    if (self) {
        free(self);
    }
}
