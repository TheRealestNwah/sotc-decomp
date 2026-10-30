typedef struct {
    char pad0[4];
    char *model;
    char pad8[0x10 - 0x8];
    int mode;
    void *seg[8];
    void *anim;
    char pad38[0x84 - 0x38];
    int limit;
} Worm;

extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void modelResetSurface(int);
extern void *texSearchMopByName(char *);
extern void *texTransRequest(void *, int, int);
extern void gsRegBegin(void);
extern void gsReg(long, long);
extern void gsRegEnd(void);
extern void transMicroCode(int);
extern void meshDisp(void *);
extern void meshFlip(void *);
extern void func_00048A78(Worm *, void *, void *, void *, int, int);
extern void func_00048558(Worm *, void *);
extern void func_000487E0(Worm *, void *);

static void func_00049198(Worm *w, int a1, int a2, int level)
{
    int i;
    int n;

    if (level >= w->limit)
        return;
    if (w->mode == 0) {
        int ofs = 0;
        void *prev = 0;

        n = *(int *)(w->model + 0x50);
        for (i = 0; i < n; i++) {
            void *next;
            int more;

            if (i == n - 1) {
                next = 0;
                more = 0;
            } else {
                next = w->seg[i + 1];
                more = 1;
            }
            if (w->seg[i] != 0)
                func_00048A78(w, w->seg[i], prev, next, ofs, more);
            prev = w->seg[i];
            ofs += 0x1D;
        }
        for (i = 0; i < n; i++) {
            void *m = w->seg[i];

            if (m != 0) {
                iosDlPushLayer(0x12);
                modelResetSurface(0x12);
                texTransRequest(texSearchMopByName("boss_worm"), 0, 0);
                gsRegBegin();
                gsReg(0x47, 0x51001);
                gsReg(0x42, 0x8000000044);
                gsRegEnd();
                transMicroCode(10);
                meshDisp(m);
                meshFlip(m);
                iosDlPopLayer();
            }
        }
    } else if (w->mode == 1) {
        func_00048558(w, w->anim);
        func_000487E0(w, w->anim);
    }
}
