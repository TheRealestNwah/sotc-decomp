typedef struct {
    char pad[0x180];
    float dt;
} GVar;

extern GVar gcGlobalVar;
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);

void ColCont_Update(long *cc, void *obj, int keep)
{
    if (*(int *)(GetLayoutClass(obj) + 0x124) == 0) {
        float dt = gcGlobalVar.dt;

        *(float *)(cc + 1) += dt;
        if (keep == 0) {
            *(float *)(cc + 1) += gcGlobalVar.dt;
            if (0.5f < *(float *)(cc + 1)) {
                *(int *)(cc + 1) = 0;
                cc[0] = 0;
            }
        }
    } else {
        cc[0] = *(long *)(GetCharacterClass(obj) + 0x690);
    }
}
