/* A union: its member accesses get alias set 0, which keeps the int loads
   from g ordered after the float stores, as in the Original. */
typedef union {
    float f[16];
    int i[16];
} ModeParam;

extern int is_boss_interest_mode_game_camera(int);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))

void get_game_camera_mode_local_parameter(ModeParam *d, char *g)
{
    int mode = I(g, 0x1360);
    char *cm = P(g, 0x1370);

    d->f[0] = 0;
    d->f[1] = 0;
    d->f[2] = 0;
    d->f[3] = 0;
    d->f[4] = 0;
    d->f[5] = 0;
    d->f[6] = 0;
    d->f[7] = 4.5f;
    d->f[8] = 2.0f;
    d->f[9] = 2.0f;
    d->f[10] = 2.0f;
    d->f[11] = 0.5f;
    d->f[12] = 0.5f;
    d->f[13] = 0.5f;
    d->f[14] = 45.0f;
    d->f[15] = 1.0f;

    if (mode == 1) {
        d->f[0] = F(P(g, 0x2C44), 0xC);
        d->f[1] = F(cm, 0x4C);
        d->f[2] = F(cm, 0x50);
        d->f[3] = F(cm, 0x54);
        d->f[4] = F(cm, 0x58);
        d->f[5] = F(cm, 0x5C);
        d->f[6] = F(cm, 0x60);
        d->f[7] = F(cm, 0x150);
        d->f[8] = F(cm, 0x128);
        d->f[9] = F(cm, 0x12C);
        d->f[10] = F(cm, 0x130);
        d->f[11] = F(cm, 0x134);
        d->f[12] = F(cm, 0x138);
        d->f[13] = F(cm, 0x13C);
        d->f[14] = F(cm, 0x160);
        d->f[15] = F(cm, 0x164);
    } else if (mode == 2) {
        d->f[0] = F(P(g, 0x2D20), 0x4);
        d->f[1] = F(cm, 0x4C);
        d->f[2] = F(cm, 0x50);
        d->f[3] = F(cm, 0x54);
        d->f[4] = F(cm, 0x58);
        d->f[5] = F(cm, 0x5C);
        d->f[6] = F(cm, 0x60);
        d->f[7] = F(cm, 0x150);
        d->f[8] = F(cm, 0x128);
        d->f[9] = F(cm, 0x12C);
        d->f[10] = F(cm, 0x130);
        d->f[11] = F(cm, 0x134);
        d->f[12] = F(cm, 0x138);
        d->f[13] = F(cm, 0x13C);
        d->f[14] = F(cm, 0x160);
        d->f[15] = F(cm, 0x164);
    } else if (mode == 3) {
        char *p = P(g, 0x2DE0);
        d->f[0] = F(p, 0x4);
        d->f[1] = F(p, 0x94);
        d->f[2] = F(p, 0x98);
        d->f[3] = F(p, 0x9C);
        d->f[4] = F(p, 0xA0);
        d->f[5] = F(p, 0xA4);
        d->f[6] = F(p, 0xA8);
        d->f[7] = F(p, 0xAC);
        d->f[8] = F(p, 0xB0);
        d->f[9] = F(p, 0xB4);
        d->f[10] = F(p, 0xB8);
        d->f[11] = F(p, 0xBC);
        d->f[12] = F(p, 0xC0);
        d->f[13] = F(p, 0xC4);
        d->f[14] = F(p, 0xC8);
        d->f[15] = F(p, 0xCC);
    } else if (mode == 4) {
        char *p = P(g, 0x2ED0);
        d->f[0] = F(p, 0x4);
        d->f[1] = F(p, 0xA8);
        d->f[2] = F(p, 0xAC);
        d->f[3] = F(p, 0xB0);
        d->f[4] = F(p, 0xB4);
        d->f[5] = F(p, 0xB8);
        d->f[6] = F(p, 0xBC);
        d->f[7] = F(p, 0xC0);
        d->f[8] = F(p, 0xC4);
        d->f[9] = F(p, 0xC8);
        d->f[10] = F(p, 0xCC);
        d->f[11] = F(p, 0xD0);
        d->f[12] = F(p, 0xD4);
        d->f[13] = F(p, 0xD8);
        d->f[14] = F(p, 0xDC);
        d->f[15] = F(p, 0xE0);
    } else if (mode == 5) {
        char *p = P(g, 0x2FF0);
        d->f[0] = F(p, 0x4);
        d->f[1] = F(p, 0xA8);
        d->f[2] = F(p, 0xAC);
        d->f[3] = F(p, 0xB0);
        d->f[4] = F(p, 0xB4);
        d->f[5] = F(p, 0xB8);
        d->f[6] = F(p, 0xBC);
        d->f[7] = F(p, 0xC0);
        d->f[8] = F(p, 0xC4);
        d->f[9] = F(p, 0xC8);
        d->f[10] = F(p, 0xCC);
        d->f[11] = F(p, 0xD0);
        d->f[12] = F(p, 0xD4);
        d->f[13] = F(p, 0xD8);
        d->f[14] = F(p, 0xDC);
        d->f[15] = F(p, 0xE0);
    } else if (mode == 6) {
        d->f[0] = F(P(g, 0x3120), 0x4);
        d->f[1] = F(cm, 0x4C);
        d->f[2] = F(cm, 0x50);
        d->f[3] = F(cm, 0x54);
        d->f[4] = F(cm, 0x58);
        d->f[5] = F(cm, 0x5C);
        d->f[6] = F(cm, 0x60);
        d->f[14] = F(cm, 0x160);
        d->f[15] = F(cm, 0x164);
        if (is_boss_interest_mode_game_camera(I(g, 0x1364)) == 1) {
            char *p = P(g, 0x2ED0);
            d->f[7] = F(p, 0xC0);
            d->f[8] = F(p, 0xC4);
            d->f[9] = F(p, 0xC8);
            d->f[10] = F(p, 0xCC);
            d->f[11] = F(p, 0xD0);
            d->f[12] = F(p, 0xD4);
            d->f[13] = F(p, 0xD8);
        } else {
            d->f[7] = F(cm, 0x150);
            d->f[8] = F(cm, 0x128);
            d->f[9] = F(cm, 0x12C);
            d->f[10] = F(cm, 0x130);
            d->f[11] = F(cm, 0x134);
            d->f[12] = F(cm, 0x138);
            d->f[13] = F(cm, 0x13C);
        }
    } else {
        d->f[0] = F(P(g, 0x2C44), 0xC);
        d->f[1] = F(cm, 0x4C);
        d->f[2] = F(cm, 0x50);
        d->f[3] = F(cm, 0x54);
        d->f[4] = F(cm, 0x58);
        d->f[5] = F(cm, 0x5C);
        d->f[6] = F(cm, 0x60);
        d->f[7] = F(cm, 0x150);
        d->f[8] = F(cm, 0x128);
        d->f[9] = F(cm, 0x12C);
        d->f[10] = F(cm, 0x130);
        d->f[11] = F(cm, 0x134);
        d->f[12] = F(cm, 0x138);
        d->f[13] = F(cm, 0x13C);
        d->f[14] = F(cm, 0x160);
        d->f[15] = F(cm, 0x164);
    }
}
