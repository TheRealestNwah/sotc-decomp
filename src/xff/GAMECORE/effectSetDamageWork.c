typedef struct {
    float pos[10][16];
    float val[10];
    int count;
} DamageWork;

/* Same layout as DamageWork; the store through it forces count to be reloaded. */
typedef union {
    DamageWork s;
    char raw[0x2AC];
} DamageWork0;

extern DamageWork B_0018A6C0;
extern char B_0018A970[];
extern char *GetDamageClass(void *);
extern void CopyGeometryPointer(void *dst, void *src);

void effectSetDamageWork(void *obj, float v)
{
    char *p = GetDamageClass(obj) + 0x10;
    int i, j;
    float tmp[16];

    CopyGeometryPointer(B_0018A970, p);
    if (B_0018A6C0.count < 10) {
        ((DamageWork0 *)&B_0018A6C0)->s.val[B_0018A6C0.count] = v;
        CopyGeometryPointer(B_0018A6C0.pos[B_0018A6C0.count], p);
        B_0018A6C0.count++;
    } else if (B_0018A6C0.val[0] <= v) {
        B_0018A6C0.val[0] = v;
        CopyGeometryPointer(B_0018A6C0.pos[0], p);
    }
    for (i = 0; i < B_0018A6C0.count; i++) {
        for (j = i; j < B_0018A6C0.count; j++) {
            if (B_0018A6C0.val[j] < B_0018A6C0.val[i]) {
                int t = B_0018A6C0.val[i];
                B_0018A6C0.val[i] = B_0018A6C0.val[j];
                B_0018A6C0.val[j] = t;
                CopyGeometryPointer(tmp, B_0018A6C0.pos[i]);
                CopyGeometryPointer(B_0018A6C0.pos[i], B_0018A6C0.pos[j]);
                CopyGeometryPointer(B_0018A6C0.pos[j], tmp);
            }
        }
    }
}
