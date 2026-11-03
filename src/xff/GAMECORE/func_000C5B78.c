typedef struct {
    char pad0[0xC];
    int value;
} SpritePartsDef;

typedef struct {
    int pad0[3];
    int flags;
    int active;
    float limit;
    float time;
} TimeAttack;

typedef struct { char pad[0x180]; float speed; } GcGlobal;

extern float getDemoBarFade(void);
extern float getFadeValue(void);
extern int MakeStrHashValue(const char *string);
extern int SpriteMenuGetLayerNoByHash(unsigned char *menu, int name);
extern SpritePartsDef *SpriteMenuGetPartsDefByHash(unsigned char *menu, int layer, int name);
extern void SpriteMenuSetDispFlag(unsigned char *o, int i, int disp);
extern GcGlobal gcGlobalVar;
extern const char RO_00180850[];
extern const char RO_00180868[];
extern const char RO_00180888[];

static int func_000C5B78(unsigned char *menu, TimeAttack *ta, int *state)
{
    int limit;
    int time;

    if (ta->active) {
        if (getDemoBarFade() == 1.0f && getFadeValue() == 0.0f) {
            ta->time += gcGlobalVar.speed;
        }
        limit = ta->limit * 100.0f;
        time = ta->time * 100.0f;
        SpriteMenuGetPartsDefByHash(menu, MakeStrHashValue(RO_00180850), MakeStrHashValue(RO_00180868))->value = time;
        SpriteMenuGetPartsDefByHash(menu, MakeStrHashValue(RO_00180850), MakeStrHashValue(RO_00180888))->value = limit - time;
    }
    if (ta->flags & 0x20) {
        ta->flags &= ~0x20;
        SpriteMenuSetDispFlag(menu, SpriteMenuGetLayerNoByHash(menu, MakeStrHashValue(RO_00180850)), 0);
        return 1;
    }
    return 0;
}
