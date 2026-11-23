typedef struct {
    char pad0[0x10];
    int flags;
    int w14;
    int w18;
    float w1C, w20, w24, w28;
    char pad2C[8];
    float w34, w38;
    char pad3C[0x38];
    int w74;
    int w78;
} MenuItemS;
typedef union { MenuItemS s; int i[2]; } MenuItem;
typedef struct {
    MenuItem *item;
    char pad4[8];
    int wC;
    char pad10[0xC];
} MenuSlot;
typedef struct {
    int a : 9;
    unsigned int mode : 2;
    int cur : 10;
    int sel : 10;
    unsigned int top : 1;
} MenuBitsS;
typedef union { MenuBitsS s; int w; } MenuBits;
typedef struct {
    int w0;
    MenuBits bits;
} MenuSub;
typedef struct {
    char pad0[4];
    MenuSlot *slots;
    unsigned int lo : 4;
    unsigned int count : 10;
    unsigned int hi : 18;
    char padC[0x28];
    MenuSub sub;
} MenuS;
typedef union { MenuS s; int i[2]; } Menu;

static inline int findSel(Menu *m)
{
    int i;
    for (i = 0; i < m->s.count; i++) {
        MenuItem *e = m->s.slots[i].item;
        if ((e->s.flags & 0xC02) == 2 && e->s.w18 == -1 && e->s.w14 == m->s.sub.bits.s.cur)
            return 1;
    }
    return 0;
}

typedef union { float f[2]; int i[2]; } OutU;
static int func_00094D40(OutU *out, Menu *m, MenuItem *ref)
{
    MenuSub *sub = &m->s.sub;
    MenuSlot *sel = 0;
    float dy = 0.0f;
    MenuItem *it = 0;
    MenuItem *found = 0;
    MenuBits b = sub->bits;
    int t = ref->s.w14;
    float dx = dy;
    int i;

    if (b.s.a == 0)
        return -1;
    if (!findSel(m) && (b.w & 0x600) == 0) {
        int start = b.s.cur;
        while (!findSel(m)) {
            it = m->s.slots[++sub->bits.s.cur].item;
            if (sub->bits.s.cur == start) {
                sub->bits.s.cur = -1;
                return -1;
            }
            if (it->s.w14 == sub->bits.s.cur && it->s.w74 == t)
                break;
            if (sub->bits.s.cur != sub->bits.s.a)
                continue;
            sub->bits.s.cur = 0;
            break;
        }
    }
    for (i = 0; i < m->s.count; i++) {
        int fl;
        it = m->s.slots[i].item;
        fl = it->s.flags;
        if (!(fl & 2))
            continue;
        if (it->s.w18 == -1) {
            if ((sub->bits.w & 0x600) == 0 && it->s.w14 == sub->bits.s.cur && it->s.w74 == t)
                goto hit;
            continue;
        } else {
            if (it->s.w74 != t)
                continue;
            if (!((sub->bits.w & 0x600) == 0x200 && it->s.w14 == sub->bits.s.cur && it->s.w18 == sub->bits.s.sel)) {
                if (!(fl & 0x100))
                    continue;
            }
        }
    hit:
        sel = &m->s.slots[i];
        found = it;
        break;
    }
    if (found == 0)
        return 0;
    switch (found->s.w78) {
    case 0:
        out->f[0] = found->s.w1C;
        out->f[1] = found->s.w20 - found->s.w28 * found->s.w38 * 0.5f;
        break;
    case 2:
        out->f[0] = found->s.w1C + found->s.w24 * found->s.w34 * 0.5f;
        out->f[1] = found->s.w20;
        break;
    case 3:
        out->f[0] = found->s.w1C;
        out->f[1] = found->s.w20 + found->s.w28 * found->s.w38 * 0.5f;
        break;
    default:
        out->f[0] = found->s.w1C - found->s.w24 * found->s.w34 * 0.5f;
        out->f[1] = found->s.w20;
        found->s.w78 = 1;
        break;
    }
    switch (it->s.w78) {
    case 0:
        dy = -ref->s.w38 * 0.5f * ref->s.w28;
        break;
    case 2:
        dx = ref->s.w34 * 0.5f * ref->s.w24;
        break;
    case 3:
        dy = ref->s.w38 * 0.5f * ref->s.w28;
        break;
    default:
        dx = -ref->s.w34 * 0.5f * ref->s.w24;
        break;
    }
    out->f[0] += dx;
    out->f[1] += dy;
    if (it->s.flags & 0x100)
        out->f[0] += it->s.w34 * sel->wC * 0.0625f - it->s.w34 * 0.5f;
    return 1;
}
