extern char *GetCharacterClass(void *);
extern char *GetScriptLayoutClass(void *);
extern char *GetScriptAnimationClass(void *);
extern void CopyGeometryPointer(void *, void *);
extern int D_00139F68;

typedef struct Frame {
    char pad0[0x14];
    float t;
} Frame;

typedef struct Anim {
    char pad0[8];
    short count;
    char padA[2];
    float rate;
} Anim;

typedef struct Src {
    char pad0[4];
    Anim *anim;
    char pad8[8];
    char geom[1];
} Src;

typedef struct Dmg {
    int state;
    char pad4[0xC];
    char geom[0x40];
    Anim *anim;
    int count;
    float rate;
    char pad5C[8];
    float acc;
    float last;
} Dmg;

static inline Dmg *getDamageClass(char *o)
{
    switch (((unsigned char *)o)[8]) {
    case 9:
        return (Dmg *)(GetCharacterClass(o) + 0x200);
    case 0xB:
        return (Dmg *)(GetScriptLayoutClass(o) + 0x230);
    case 0xD:
        return (Dmg *)(GetScriptAnimationClass(o) + 0x230);
    case 0x16:
        return (Dmg *)(o + 0x290);
    }
    return 0;
}

#ifdef NONMATCHING
/* 29 diffs: target reloads s->anim after every store to the damage class */
static void func_000EB038(char *o, Src *s)
{
    Dmg *d = getDamageClass(o);
    float t, last;

    if (d->state >= 2) return;
    if (d->state < 0) return;
    if (d->count < 0 || d->count < s->anim->count) {
        CopyGeometryPointer(d->geom, s->geom);
        d->state = 1;
        d->anim = s->anim;
        last = d->last;
        t = ((Frame *)((char *)s->anim + D_00139F68 * 8))->t;
        d->last = t;
        d->acc += t - last;
        d->count = s->anim->count;
        d->rate = s->anim->rate * 0.033333333f;
    }
}
#endif
