/* Parked draft: debug overlay for collision edges. Each entry is {object, packed reference,
   edge index, pad}; draws every edge as a line between two corner points of the referenced
   collision shape. Written from the m2c draft; not yet compared closely. */
#ifdef NONMATCHING
extern int *GetGlDebugSw(void);
extern char *GetLayoutClass(int);
extern void func_000999E0(float *, int, char *, int);
extern void func_0009AE78(float *, int, char *, int);
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

    if (*GetGlDebugSw() != 0) {
        triangleDispSetup();
        trianglePolyColor(1, -1.0f, -1.0f, -1.0f, -1.0f);
        if (count > 0) {
            e = entries;
            n = count;
            do {
                n--;
                if (*e != 0) {
                    triangleDispSetup();
                    trianglePolyColor(1, -1.0f, -1.0f, -1.0f, -1.0f);
                    func_000A6240(e, 0, -1, 0.6f, 0.8f, 1.0f, 1.0f, 0.7f, 0.5f, 0.2f);
                }
                e += 4;
            } while (n != 0);
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
                char *layout = GetLayoutClass(e[0]);
                float v[8] __attribute__((aligned(16)));

                e += 4;
                if ((int)packed < 0) {
                    func_000999E0(v, 0, layout, node);
                } else {
                    char *res = *(char **)(layout + 0x154 + 0x20);
                    func_0009AE78(v, 0, res + 0x28, *(int *)(res + 0x24));
                }
                n--;
                glBegin(1);
                glVertex4fv(&v[idx * 4]);
                glVertex4fv(&v[RO_001407D8[idx] * 4]);
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
