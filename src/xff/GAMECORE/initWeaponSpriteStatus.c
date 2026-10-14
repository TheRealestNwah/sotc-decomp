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
extern int D_0017B044;
extern int D_0017B048;

void initWeaponSpriteStatus(void)
{
    int i;

    for (i = 0; i < 9; i++) {
        WeaponSprite *s = &B_0019CD48[i];

        s->active = 0;
        s->x = s->y = 0.0f;
        s->scale = 0.5f;
        s->size = 64.0f;
        s->rot = 0.0f;
        s->visible = 1;
        s->alpha = 0.0f;
    }
    D_0017B044 = -1;
    D_0017B048 = -1;
}
