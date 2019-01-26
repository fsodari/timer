#ifndef TIMER_OBSERVER_H
#define TIMER_OBSERVER_H

#include <stdint.h>

typedef void (*change_notification)(void *instance, const uint32_t new_value);

typedef struct
{
    void *instance;
    change_notification notification;
} observer;

#endif
