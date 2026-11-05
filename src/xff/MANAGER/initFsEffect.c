typedef struct {
    int f0;
    unsigned int flags;
    char pad8[0x58];
} FsEffect;

extern FsEffect B_00147310;
extern FsEffect *FsEffect_DEFAULT;
extern void *memcpy(void *, const void *, unsigned int);

typedef struct {
    char pad0[0x10];
    FsEffect *effect;
} FsEffectOwner;

static inline void setFsEffect(FsEffect *e)
{
    if (e != 0) {
        memcpy(&B_00147310, e, 0x60);
    }
}

void initFsEffect(FsEffectOwner *owner)
{
    if (owner->effect->flags & 0xF0000000) {
        setFsEffect(owner->effect);
    }
    setFsEffect(FsEffect_DEFAULT);
}
