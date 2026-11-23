/* Draws a marker sprite for each tree in every world layout area whose
 * fruits have not all been taken, mapped onto the menu map. */

typedef int q128 __attribute__((mode(TI)));
typedef union { q128 q; struct { float x, y, z, w; } v; } Vec4;
typedef struct { unsigned short id; short x; short pad4; short z; char pad8[4]; short ox; short oz; } Item;

extern int DldSysUndefSymbol;
extern char *getWorldLayoutHead(void);
extern int stagemanager_getNbWorldLayoutDatas(void);
extern void stagemanager_getCenterFromAreaId(Vec4 *, int);
extern int nico_checkTreeAllFruitsAlreadyTaken(unsigned short);
extern char rootPtn[];
extern void *spriteCreateObject(char *, int);
extern void spriteSetColor(void *, int, int, int, int);
extern void spriteSetScale(void *, float, float);
extern void spriteSetBlendMode(void *, int, int, int);
extern void spriteSetPosition(void *, float, float);
extern void spriteSetRotation(void *, float);
extern void spriteDrawSprite(void *, int, float, float, float, float, float, float, int, int);
extern void spriteDeleteObject(void *);

#define W(type, o) (*(type *)(menu + (o)))

static inline char *resolve2(unsigned int *h, unsigned int v)
{
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline char *resolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline void draw(char *menu, int ptn, int pri, float x, float y, float sc)
{
    void *spr = spriteCreateObject(rootPtn, ptn);
    spriteSetColor(spr, 0x80, 0x80, 0x80, 0x80);
    spriteSetScale(spr, sc, sc);
    spriteSetBlendMode(spr, 1, 0, 1);
    spriteSetPosition(spr, x, y);
    spriteSetRotation(spr, 0.0f);
    spriteDrawSprite(spr, 0xFFFFFF, W(float, 0x48) + W(float, 0x50), W(float, 0x4C) + W(float, 0x54), 1.0f, 1.0f, 0.0f, W(float, 0x14), pri, -1);
    spriteDeleteObject(spr);
}

static void func_000CE058(char *menu)
{
    char *lay;
    unsigned int n;
    int area;
    unsigned int *h;
    unsigned int v;
    char *t;
    int off;
    Vec4 c, p, m;
    Item *it;
    int cnt, ptn, i;
    float sc, x, z;
    int pri;
    void *spr;

    lay = getWorldLayoutHead();
    if (lay == 0)
        return;
    n = stagemanager_getNbWorldLayoutDatas();
    for (area = 0; n-- != 0; area++, lay += 0x9C) {
        h = (unsigned int *)(lay + 0x1C);
        v = *h;
        it = (Item *)resolve2(h, v);
        if (it == 0)
            continue;
        off = v & 0x3FFFF;
        t = off != 0 ? *(char **)((char *)h - off) : 0;
        cnt = (t != 0 && t != (char *)DldSysUndefSymbol) ? *(int *)(t + 0xC) : 0;
        ptn = *(int *)(resolve((unsigned int *)((char *)it + 8)) + 0xC);
        stagemanager_getCenterFromAreaId(&c, area);
        i = cnt;
        for (; i-- != 0; it++) {
            if (nico_checkTreeAllFruitsAlreadyTaken(it->id) != 0)
                continue;
            p.q = c.q;
            p.v.x = -(p.v.x - it->x - it->ox);
            p.v.y = 0.0f;
            p.v.z = -(p.v.z - it->z - it->oz);
            sc = W(float, 0x18);
            pri = W(int, 0x58) - 0x18;
            m.q = p.q;
            m.v.x = m.v.x / 600.0f * W(float, 0x40) * 0.1f * sc;
            m.v.y = m.v.y * -0.067f;
            m.v.z = -(m.v.z / 600.0f * W(float, 0x40) * 0.1f + m.v.y) * sc * 0.85714281f;
            p.q = m.q;
            x = p.v.x;
            z = p.v.z;
            if (ptn != 0)
                draw(menu, ptn, pri, x, z, sc);
        }
    }
}
