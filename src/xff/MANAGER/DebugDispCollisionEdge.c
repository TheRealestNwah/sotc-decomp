/* Parked draft: debug overlay for collision edges. Each entry is {object, packed reference,
   edge index, pad}; draws every edge as a line between two corner points of the referenced
   collision shape. Right size (205 words), ~99 diffs: count/entries/e register rotation in the
   first loop and the second loop's layout/ends scheduling. */
#ifdef NONMATCHING
extern int *GetGlDebugSw(void);
extern char *GetLayoutClass(int);
extern void func_000999E0(float **, int, char *, int, int);
extern void func_0009AE78(float **, int, char *, int, int, int, int, int);
extern void func_000A6240(int *, int, int, float, float, float, float, float, float, float);
extern void glBegin(int);
extern void glBlendFunc(int, int);
extern void glColor4f(float, float, float, float);
extern void glEnable(int);
extern void glEnd(void);
extern void glLoadMatrixf(void *);
extern void glVertex4fv(float *);
extern void glZOffset(float);
extern void iosDlPopLayer(void);
extern void iosDlPushLayer(int);
extern void triangleDispSetup(void);
extern void trianglePolyColor(int, float, float, float, float);
extern char UnitMatrix[];
extern int RO_001407D8[];

void DebugDispCollisionEdge(int *entries, int count)
{
    int *e;
    int n;
    float *ends[2];
    float *pts[4];

    if (*GetGlDebugSw() != 0) {
        triangleDispSetup();
        trianglePolyColor(1, -1.0f, -1.0f, -1.0f, -1.0f);
        if (count > 0) {
            e = entries;
            n = count;
        loop:
            n--;
            if (*e != 0) {
                triangleDispSetup();
                trianglePolyColor(1, -1.0f, -1.0f, -1.0f, -1.0f);
                func_000A6240(e, 0, -1, 0.6f, 0.8f, 1.0f, 1.0f, 0.7f, 0.5f, 0.2f);
            }
            e += 4;
            if (n != 0)
                goto loop;
        }
        glLoadMatrixf(UnitMatrix);
        glEnable(3);
        iosDlPushLayer(0x17);
        glBegin(2);
        glBlendFunc(5, 6);
        glZOffset(1.08f);
        glEnd();
        glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
        glBegin(8);
        glEnable(7);
        glBlendFunc(5, 1);
        glEnd();
        if (count > 0) {
            e = entries;
            n = count;
            do {
                unsigned int packed = e[1];
                int idx = e[2];
                int node = (packed >> 24) & 0x7F;
                int low = packed & 0xFFFFFF;
                char *layout = GetLayoutClass(e[0]);
                char *sh = layout + 0x154;

                int neg = e[1];

                e += 4;
                if (neg < 0) {
                    func_000999E0(pts, 0, layout, node, low);
                } else {
                    char *res = *(char **)(sh + 0x20);
                    char *q = *(char **)(*(char **)(layout + 0x184) + 0x20);
                    func_0009AE78(pts, 0, res + 0x28, *(int *)(res + 0x24), *(int *)(sh + 8), *(int *)(q + 8),
                                  *(int *)(q + 0x14),
                                  *(int *)(q + 0x18) + (*(int **)(*(int *)(q + 8) + node * 0x90 + 0x54))[low] * 64);
                }
                n--;
                ends[0] = pts[idx];
                ends[1] = pts[RO_001407D8[idx]];
                glBegin(1);
                glVertex4fv(ends[0]);
                glVertex4fv(ends[1]);
                glEnd();
            } while (n != 0);
        }
        glBegin(8);
        glBlendFunc(5, 6);
        glEnd();
        glBegin(8);
        glZOffset(1.0f);
        glEnable(8);
        glBlendFunc(5, 6);
        glEnd();
        iosDlPopLayer();
        glEnable(3);
    }
}
#endif
