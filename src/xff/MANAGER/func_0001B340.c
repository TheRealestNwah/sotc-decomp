typedef struct {
    char pad0[0x18];
    unsigned int flags;
} Model;

typedef struct {
    char pad0[0x18];
    union {
        long flags;
        struct {
            int lo;
            unsigned int type;
        } w;
    } u;
    char pad20[0x20];
    int index;
} ModelLayer;

#define F(n, m) ((int)(layer->u.flags >> (n)) & (m))

static int func_0001B340(Model *model, ModelLayer *layer)
{
    register unsigned int t __asm__("$5");
    if (F(12, 1)) {
        t = layer->u.w.type;
        if (t == 1) {
            return 0x14;
        }
        if (t != 2) {
            goto out;
        }
        return 0x16;
    }
    if (F(5, 1)) {
        if (model->flags & 1) {
            int tbl[6] = { 0x28, 0x20, 0x22, 0x20, 0x26, 0x28 };
            return tbl[layer->index];
        } else {
            int tbl[6] = { 0x2A, 0x20, 0x22, 0x20, 0x26, 0x28 };
            return tbl[layer->index];
        }
    }
    t = layer->u.w.type;
    if (t != 0) {
        if (t < 2) {
            if (!(model->flags & 1)) {
                if (!F(4, 1)) {
                    return F(17, 1) ? 0x1C : 0x10;
                }
                return 0x14;
            }
            if (F(4, 1)) {
                if (F(28, 1)) {
                    return 0x1E;
                }
                if (F(17, 1)) {
                    return 0x1A;
                }
                if (F(20, 7)) {
                    return 0x14;
                }
                return F(27, 1) ? 0x1C : 0x10;
            }
            return 0x10;
        }
        if (t == 2) {
            if (!(model->flags & 1)) {
                return !F(4, 1) ? 0x12 : 0x16;
            }
            if (F(4, 1) && !F(28, 1)) {
                return F(20, 7) ? 0x16 : 0x12;
            }
            return 0x10;
        }
    } else {
        if (!(model->flags & 1)) {
            return !F(4, 1) ? 0x18 : 0x1A;
        }
        if (F(4, 1)) {
            return 0x18;
        }
    }
out:
    return 0x10;
}
