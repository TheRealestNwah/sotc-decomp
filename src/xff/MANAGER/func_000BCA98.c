typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { short type; short pad2; int count; int n; } ClothHeader;
typedef struct { char pad0[0xC]; Vec4 *prev; Vec4 *pts; char pad14[4]; } ClothStrand;
typedef struct { ClothHeader *header; char pad4[8]; ClothStrand *strands; char finder[0x80]; } Cloth;

extern void DebugDispCollisionFinder(void *, int, int);
extern void glEnable(int);
extern void glLoadMatrixf(void *);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern int glBegin(int); /* int: matches the register choice for the loop bounds */
extern void glEnd(void);
extern void glBlendFunc(int, int);
extern void glColor4f(float, float, float, float);
extern void glVertex3fv(void *);
extern char UnitMatrix[];

static void func_000BCA98(Cloth *cloth)
{
    ClothHeader *h = cloth->header;
    ClothStrand *s = cloth->strands;
    int i;
    int j;

    DebugDispCollisionFinder(cloth->finder, 0, 0);
    glEnable(3);
    glEnable(7);
    glLoadMatrixf(UnitMatrix);
    iosDlPushLayer(0x17);
    glBegin(8);
    glBlendFunc(5, 1);
    glEnd();
    glColor4f(0.0f, 0.19999999f, 0.19999999f, 1.0f);
    for (i = 0; i < h->count - 1; i++) {
        glBegin(5);
        for (j = 0; j < h->n; j++) {
            glVertex3fv(&s[i].pts[j]);
            glVertex3fv(&s[i + 1].pts[j]);
        }
        glEnd();
    }
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    for (i = 0; i < h->count; i++) {
        glBegin(2);
        for (j = 0; j < h->n; j++) {
            glVertex3fv(&s[i].pts[j]);
        }
        glEnd();
    }
    for (j = 0; j < h->n; j++) {
        glBegin(2);
        for (i = 0; i < h->count; i++) {
            glVertex3fv(&s[i].pts[j]);
        }
        glEnd();
    }
    iosDlPopLayer();
}
