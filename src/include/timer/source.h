#ifndef TIMER_SOURCE_H
#define TIMER_SOURCE_H

#include "timer/observer.h"

typedef struct source_struct *source;

source source_create(void);
void source_destroy(source self);
void source_attach(source self, const observer *o);
void source_detach(source self, const observer *o);

void source_update(source self, uint32_t new_value);

#endif
