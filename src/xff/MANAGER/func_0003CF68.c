typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int unk0;
    int unk4;
    unsigned char *unk8;
    int unkC;
    int *unk10;
    int unk14;
} AnimSrc;

extern int func_00031438(s128 *out, int a, int b, int frame);
extern int GetObjectAnimationFloatFrame(void *out, void *motion, int index,
                                       float frame, float previousFrame);
extern void GetTRS_Onake_From_ObjectAnimation(void *anim, void *s, void *t, void *r, void *q);

void func_0003CF68(s128 *out, AnimSrc *src, int frame, int count) {
    int i;
    if (src->unk8 != 0) {
        if (count != src->unk14 && src->unk14 < count) {
            count = src->unk14;
        }
        for (i = 0; i < count; i++) {
            func_00031438(out + i, src->unk8[i], src->unk10[i], frame);
        }
    } else {
        struct { s128 s, t, r, q; } trs;
        char anim[0x60];
        for (i = 0; i < count; i++) {
            GetObjectAnimationFloatFrame(anim, src, i, (float)frame, (float)frame);
            GetTRS_Onake_From_ObjectAnimation(anim, &trs.s, &trs.t, &trs.r, &trs.q);
            out[i] = trs.t;
        }
    }
}
