#ifdef NONMATCHING
/* ~140 diffs, same length (146 words). Draft from the asm: weapon-icon fade slot update on B_0019CD48[idx] (WeaponSprite, see initWeaponSpriteStatus): dt = gcGlobalVar[+0x180] * 3.0; state 1 grows scale/size/rot (by dt*0.5, dt*128, dt) and at rot >= 1.0 sets state 2 and calls playerWeaponChangeIconMax((int)size), otherwise fills obj+0x30/34/40/44/8 and the colour bytes obj[4..7] and obj[0x4C]=val; state 3 mirrors it downward (state 0 at rot <= 0); then state 2 / state 0 write constant poses. Differences: the Original reads the 0.0 constant from rodata (RO_001803B4, modelled with a 1-element const array so gcc keeps the load), keeps B_0019CD48 hi in s4 and the static state/x/y/size field addresses as separate base+idx*32 sums (t0/t3), stores an uninitialised v0 at sp+0 (dead store) and saves f20/f21 at 0x40/0x48 (frame 0x50). Ours differs in nearly every register choice. */
typedef struct {
    int active;
    float x;
    float y;
    float scale;
    float size;
    float rot;
    int visible;
    float alpha;
} WeaponSprite;

extern WeaponSprite B_0019CD48[9];
extern char gcGlobalVar[];
extern void playerWeaponChangeIconMax(int);
static const float RO_001803B4[1] = { 0.0f };

static void func_000BF880(char *obj, int idx, int unused, int val)
{
    float x = B_0019CD48[idx].x;
    float y = B_0019CD48[idx].y;
    float dt = *(float *)(gcGlobalVar + 0x180) * 3.0f;
    struct { int junk[4]; } L;
    int unset;
    int c;
    float scale, size, rot;

    L.junk[0] = unset;
    if (B_0019CD48[idx].active == 1) {
        scale = B_0019CD48[idx].scale + dt * 0.5f;
        B_0019CD48[idx].scale = scale;
        B_0019CD48[idx].size = B_0019CD48[idx].size + dt * 128.0f;
        c = (int)B_0019CD48[idx].size;
        rot = B_0019CD48[idx].rot + dt;
        B_0019CD48[idx].rot = rot;
        if (1.0f <= rot) {
            B_0019CD48[idx].active = 2;
            playerWeaponChangeIconMax(c);
        } else {
            *(float *)(obj + 0x44) = scale;
            *(char *)(obj + 6) = c;
            *(char *)(obj + 7) = 0x80;
            *(float *)(obj + 8) = rot;
            *(float *)(obj + 0x30) = x;
            *(float *)(obj + 0x34) = y;
            *(float *)(obj + 0x40) = scale;
            *(char *)(obj + 4) = c;
            *(char *)(obj + 5) = c;
            *(char *)(obj + 0x4C) = val;
        }
    } else if (B_0019CD48[idx].active == 3) {
        scale = B_0019CD48[idx].scale - dt * 0.5f;
        B_0019CD48[idx].scale = scale;
        B_0019CD48[idx].size = B_0019CD48[idx].size - dt * 128.0f;
        c = (int)B_0019CD48[idx].size;
        rot = B_0019CD48[idx].rot - dt;
        B_0019CD48[idx].rot = rot;
        if (rot <= RO_001803B4[0]) {
            B_0019CD48[idx].active = 0;
        } else {
            *(float *)(obj + 0x44) = scale;
            *(char *)(obj + 6) = c;
            *(char *)(obj + 7) = 0x80;
            *(float *)(obj + 8) = rot;
            *(float *)(obj + 0x30) = x;
            *(float *)(obj + 0x34) = y;
            *(float *)(obj + 0x40) = scale;
            *(char *)(obj + 4) = c;
            *(char *)(obj + 5) = c;
            *(char *)(obj + 0x4C) = val;
        }
    }
    if (B_0019CD48[idx].active == 2) {
        *(char *)(obj + 0x4C) = val;
        *(float *)(obj + 0x30) = x;
        *(float *)(obj + 0x34) = y;
        *(char *)(obj + 7) = 0x80;
        *(float *)(obj + 8) = 1.0f;
        *(float *)(obj + 0x40) = 1.0f;
        *(float *)(obj + 0x44) = 1.0f;
        *(char *)(obj + 4) = 0x80;
        *(char *)(obj + 5) = 0x80;
        *(char *)(obj + 6) = 0x80;
    } else if (B_0019CD48[idx].active == 0) {
        *(char *)(obj + 0x4C) = val;
        *(float *)(obj + 0x30) = x;
        *(float *)(obj + 0x34) = y;
        *(float *)(obj + 0x44) = 0.5f;
        *(char *)(obj + 7) = 0x80;
        *(float *)(obj + 8) = RO_001803B4[0];
        *(float *)(obj + 0x40) = RO_001803B4[0];
        *(char *)(obj + 4) = 0;
        *(char *)(obj + 5) = 0;
        *(char *)(obj + 6) = 0;
    }
}
#endif
