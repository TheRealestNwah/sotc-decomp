extern void GAMEUTIL_set_parameter_col_plane_info_filter(char *, float, float);
extern void GAMEUTIL_doit_col_plane_info_filter(char *, char *, float);
extern int GAMEUTIL_get_boss_obj(void);
extern int GetCollisionCameraAttributeShareArrayNumber(int);
extern void GetCollisionCameraAttributeShareArray(void *, int);

#ifdef NONMATCHING /* 33 diffs: the original compares the zero in $s4 (found) against the count with slt and keeps best/found in $s3/$s4; the loop count test differs */
static void func_000D9028(char *c, char *arg1, float dt)
{
    char *f = c + 0x150;
    register long best __asm__("$19");
    float bestw;
    register int found __asm__("$20") = 0;
    int st;
    int obj;

    GAMEUTIL_set_parameter_col_plane_info_filter(f, 0.0f, 2.0f);
    GAMEUTIL_doit_col_plane_info_filter(f, arg1 + 0x27B0, dt);
    st = *(int *)(f + 8);
    if (st == 1 && (*(long *)(f + 0x10) & 1L)) {
        obj = GAMEUTIL_get_boss_obj();
        *(int *)(c + 0x18) = obj;
        if (obj != 0) {
            best = *(long *)(c + 0xC0);
            if (*(int *)(c + 0x1B0) == st) {
                float *p;
                int n;

                bestw = -1.0f;
                n = GetCollisionCameraAttributeShareArrayNumber(*(int *)(f + 0x50));
                *(int *)(c + 0x1C) = n;
                if (n >= 0xB)
                    __asm__ __volatile__("break 0");
                GetCollisionCameraAttributeShareArray(c + 0x20, *(int *)(f + 0x50));
                n = *(int *)(c + 0x1C);
                p = (float *)(c + 0x20);
                if (n > 0) {
                    do {
                        float w = p[2];

                        n--;
                        if (bestw < w) {
                            best = *(long *)p;
                            bestw = w;
                        }
                        p += 4;
                    } while (n != 0);
                }
            }
            *(long *)(c + 0xC0) = best;
            found = 1;
        }
    }
    if (found == 0) {
        *(int *)(c + 0x18) = 0;
        *(long *)(c + 0xC0) = -1;
        *(int *)(c + 0x1C) = 0;
    }
}
#endif
