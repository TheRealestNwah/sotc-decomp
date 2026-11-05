typedef int s128 __attribute__((mode(TI)));

typedef struct LayoutClass {
    char pad0[0x90];
    s128 color;
    char padA0[0x94];
    int pos;
    char pad138[4];
    int rot;
} LayoutClass;

typedef struct QuatPos {
    s128 rot;
    s128 pos;
} QuatPos;

extern s128 All1Vector;
extern int D_00139F78;
extern int D_00139F7C;
extern int D_00139F80;
extern int D_00139F84;
extern int D_00139F88;
extern s128 B_0015E420;
extern s128 B_0015E430;
extern s128 B_0015E440;
extern LayoutClass *GetLayoutClass(void *, void *);
extern int GetCharacterClass(void *);
extern void GetGeometryPointerQuatPos(QuatPos *, void *);
extern void func_000ED618(int, int);

#ifdef NONMATCHING
/* 57 diffs: global address materialization and quad loads scheduled differently around the sq stores */
void ExecEff(int a0, void *obj, int a2, int a3, void *geom)
{
    if (obj != 0) {
        LayoutClass *l = GetLayoutClass(obj, geom);

        D_00139F78 = (int)obj;
        D_00139F7C = GetCharacterClass(obj);
        B_0015E430 = *(s128 *)l->pos;
        B_0015E440 = *(s128 *)l->rot;
        B_0015E420 = l->color;
        D_00139F84 = a2;
        D_00139F88 = a3;
        D_00139F80 = (int)geom;
    } else {
        QuatPos qp;

        GetGeometryPointerQuatPos(&qp, geom);
        B_0015E430 = qp.pos;
        B_0015E440 = qp.rot;
        B_0015E420 = All1Vector;
        D_00139F84 = a2;
        D_00139F88 = a3;
        D_00139F80 = (int)geom;
        D_00139F78 = 0;
        D_00139F7C = 0;
    }
    func_000ED618(a0, 0);
}
#endif
