#include "timer/timer_source.h"
#include "list/list.h"

typedef timer_observer *timer_observer_ptr;
static int timer_cmp(const void *s1, const void *s2);

struct timer_source_struct
{
    list timer_list;
};

timer_source timer_source_create(void)
{
    timer_source self = malloc(sizeof(*self));
    if (self) {
        self->timer_list = list_create(sizeof(timer_observer_ptr));
        if (self->timer_list == NULL) {
            free(self);
            self = NULL;
        }
    }

    return self;
}

void timer_source_destroy(timer_source self)
{
    if (self) {
        list_destroy(self->timer_list);
        free(self);
    }
}

void timer_source_attach(timer_source self, const timer_observer *t)
{
    if (self) {
        if (self->timer_list) {
            if (t) {
                list_append(self->timer_list, t);
            }
        }
    }
}

void timer_source_detach(timer_source self, const timer_observer *t)
{
    int index;
    if (self) {
        if (self->timer_list) {
            if (t) {
                index = list_find_index(self->timer_list, t, timer_cmp);
                if (index >= 0) {
                    list_remove(self->timer_list, index);
                }
            }
        }
    }
}

// Call this function in the timer interrupt
void timer_source_update(timer_source self, uint32_t new_time)
{
    timer_observer x;
    size_t i, size;
    if (self) {
        if (self->timer_list) {
            size = list_size(self->timer_list);
            for (i = 0; i < size; i++) {
                list_get(self->timer_list, &x, i);
                x.notification(x.instance, new_time);
            }
        }
    }
}

// Just compares the address
static int timer_cmp(const void *s1, const void *s2)
{
    const timer_observer *t1 = (const timer_observer*)s1, *t2 = (const timer_observer*)s2;

    if (t1 == t2) {
        return 1;
    } else {
        return 0;
    }
}
