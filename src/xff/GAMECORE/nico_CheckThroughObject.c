typedef struct {
    char pad0[0x134];
    int a;
    int b;
} Layout;

typedef struct {
    char pad0[8];
    void *obj;
} Target;

extern Layout *GetLayoutClass(void);
extern int ClipCollisionDirectCallBackOneObj(void *, int, int, void *, int, int, int, int);

int nico_CheckThroughObject(void *arg0, Target *t)
{
    char buf[0x50];
    void *obj;
    Layout *l;

    if (t != 0) {
        obj = t->obj;
        if (obj == 0) {
            return 0;
        }
        l = GetLayoutClass();
        if (ClipCollisionDirectCallBackOneObj(buf, l->b, l->a, obj, 0, 0, 0, 0) != 0) {
            return 1;
        }
    }
    return 0;
}
