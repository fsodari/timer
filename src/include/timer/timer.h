#ifndef TIMER_TIMER_H
#define TIMER_TIMER_H

#include "timer/observer.h"
#include "timer/source.h"

typedef struct timer_struct * timer;

timer timer_new(source timer_source, uint32_t period);
void timer_destroy(timer self);
void timer_set_period(timer self, uint32_t period);
uint32_t timer_get_period(const timer self);
uint32_t timer_get_counter(const timer self);
void timer_reset(timer self);
int timer_timeout(timer self, int reset);

#endif //TIMER_TIMER_H
