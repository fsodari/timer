#include "timer/source.h"
#include "list/list.h"

static int observer_cmp(const void *s1, const void *s2);

struct source_struct
{
    list timer_list;
};

source source_create(void)
{
    source self = malloc(sizeof(*self));
    if (self) {
        self->timer_list = list_create(sizeof(observer));
        if (self->timer_list == NULL) {
            free(self);
            self = NULL;
        }
    }

    return self;
}

void source_destroy(source self)
{
    if (self) {
        list_destroy(self->timer_list);
        free(self);
    }
}

void source_attach(source self, const observer *o)
{
    if (self) {
        if (self->timer_list) {
            if (o) {
                list_append(self->timer_list, o);
            }
        }
    }
}

void source_detach(source self, const observer *o)
{
    int index;
    if (self) {
        if (self->timer_list) {
            if (o) {
                index = list_find_index(self->timer_list, o, observer_cmp);
                if (index >= 0) {
                    list_remove(self->timer_list, index);
                }
            }
        }
    }
}

// Call this function in the interrupt
void source_update(source self, uint32_t new_value)
{
    observer x;
    size_t i, size;
    if (self) {
        if (self->timer_list) {
            size = list_size(self->timer_list);
            for (i = 0; i < size; i++) {
                list_get(self->timer_list, &x, i);
                x.notification(x.instance, new_value);
            }
        }
    }
}

static int observer_cmp(const void *s1, const void *s2)
{
    const observer *t1 = (const observer*)s1, *t2 = (const observer*)s2;

    // Compare the pointer to instance
    if (t1->instance == t2->instance) {
        return 1;
    } else {
        return 0;
    }
}
