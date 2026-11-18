typedef struct Seg {
    int res;
    int base;
    int count;
    int addr;
    int tag;
    struct Seg *next;
} Seg;

typedef struct AdpcmUser {
    char pad0[0x38];
    unsigned long flags;
    char pad40[0x70 - 0x40];
    int start;
    int end;
    char pad78[0x264 - 0x78];
    Seg *free;
    Seg *head;
    Seg *tail;
    Seg *done;
    int res;
    int pos;
    int addr;
} AdpcmUser;

extern void func_000DB530(AdpcmUser *, int, int *, int *, int *);

#define ASSERT(c) do { if (!(c)) __asm__ __volatile__("break 0"); } while (0)

static void func_000DB778(AdpcmUser *o, int n, int arg)
{
    int got, res, pos;

    o->flags |= 1L << 34;
    while (n > 0) {
        int remain;
        int addr, base, cur;

        func_000DB530(o, n, &got, &res, &pos);
        addr = o->addr;
        cur = o->res;
        remain = got;
        base = o->pos;
        if (!(addr < o->end)) {
            __asm__ __volatile__("break 0");
        }
        while (remain > 0) {
            int chunk = (o->end - addr) / 2048;
            Seg *t;

            if (remain < chunk) {
                chunk = remain;
            }
            t = o->tail;
            ASSERT(chunk > 0);
            if (t != 0 && t->res == cur && t->base + t->count == base && t->addr + (t->count << 11) == addr) {
                t->count += chunk;
            } else {
                Seg *s = o->done;
                Seg *prev = 0;
                Seg *e;

                while (s != 0) {
                    Seg *next = s->next;
                    if (s->count == 0 || (unsigned int)(s->tag - 0xDEAF) < 2) {
                        s->next = o->free;
                        o->free = s;
                        if (prev != 0) {
                            prev->next = next;
                        } else {
                            o->done = next;
                        }
                    } else {
                        prev = s;
                    }
                    s = next;
                }
                e = o->free;
                if (e != 0) {
                    o->free = e->next;
                    e->next = 0;
                }
                e->addr = addr;
                e->base = base;
                e->count = chunk;
                e->res = cur;
                e->next = 0;
                if (*(int *)&o->tail != 0) {
                    o->tail->next = e;
                } else {
                    o->head = e;
                }
                o->tail = e;
            }
            o->addr += chunk << 11;
            o->pos += chunk;
            if (o->addr == o->end) {
                o->addr = o->start;
            }
            remain -= chunk;
            base = o->pos;
            addr = o->addr;
        }
        n -= got;
        o->res = res;
        o->pos = pos;
    }
}
