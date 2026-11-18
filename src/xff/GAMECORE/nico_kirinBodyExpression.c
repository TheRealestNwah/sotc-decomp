typedef struct {
    int pad0;
    unsigned int bits;
    int node;
} NodeDef;

extern char *GetCharacterClass(void *);
extern float getexpressiondatapoint(int, int);
extern void _setRootXYZHPB(int, int, void *, void *, void *, float, float, float, float, float, float);
extern void _setNodeHPBIllegal(int, int, int, void *, float, float, float);
extern NodeDef *MotRootHeightAdjustNodeDef_KIRIN_FRONT_RIGHT;
extern NodeDef *MotRootHeightAdjustNodeDef_KIRIN_FRONT_LEFT;
extern NodeDef *MotRootHeightAdjustNodeDef_KIRIN_REAR_RIGHT;
extern NodeDef *MotRootHeightAdjustNodeDef_KIRIN_REAR_LEFT;
extern NodeDef *SkelFocusDef_BOSS_GENERALBone_HARA;
extern NodeDef *SkelFocusDef_BOSS_GENERALBone_MUNE;
extern NodeDef *SkelFocusDef_BOSS_GENERALBone_KUBI;
extern NodeDef *SkelFocusDef_BOSS_GENERALBone_KUBI_B;
extern NodeDef *SkelFocusDef_BOSS_GENERALBone_KATA_L;
extern NodeDef *SkelFocusDef_BOSS_GENERALBone_KATA_R;
extern NodeDef *SkelFocusDef_BOSS_GENERALBone_KOSI;
extern NodeDef *SkelFocusDef_BOSS_GENERALBone_MATA_L;
extern NodeDef *SkelFocusDef_BOSS_GENERALBone_MATA_R;
extern NodeDef *SkelFocusDef_BOSS_TAIL_A;

static inline float MIN(float a, float b)
{
    float r;
    if (a <= b)
        r = a;
    else
        r = b;
    return r;
}

#ifdef NONMATCHING /* 13 diffs: same length; the original materializes the float argument copies (mov.s $f14,$f27 for the HARA call, mov.s $f12,$f23 for KATA_L) before the integer argument copies, plus one mov.s $f14,$f20 placement and one addiu $t0,$s1,0x90 position */
void nico_kirinBodyExpression(void *obj)
{
    char *c = GetCharacterClass(obj);
    void *p = c + 0x470;
    int exp = *(int *)(c + 0x338);
    int a0 = *(int *)(c + 0x358);
    int a1 = *(int *)(c + 0x2E8);
    double k = 0.049999999999999996;
    float fr = getexpressiondatapoint(exp, (MotRootHeightAdjustNodeDef_KIRIN_FRONT_RIGHT->bits >> 18) & 0xFFF);
    float fl = getexpressiondatapoint(exp, (MotRootHeightAdjustNodeDef_KIRIN_FRONT_LEFT->bits >> 18) & 0xFFF);
    float rr = getexpressiondatapoint(exp, (MotRootHeightAdjustNodeDef_KIRIN_REAR_RIGHT->bits >> 18) & 0xFFF);
    float rl = getexpressiondatapoint(exp, (MotRootHeightAdjustNodeDef_KIRIN_REAR_LEFT->bits >> 18) & 0xFFF);
    float side = fl - fr;
    float rear = rl + rr;
    float fb = fl + fr - rl - rr;
    float rside = rr - rl;
    float x = ((rear * 2.0f - fl - fr) * k);
    float y = ((fr + rr * 5.0f - fl - rl * 5.0f) * k);
    float z = fb * k;

    _setRootXYZHPB(a0, a1, p, c + 0x40, c + 0x90, y, x, z, side + rside * 3.0f, fb, -(fl + rl - fr - rr));
    _setNodeHPBIllegal(SkelFocusDef_BOSS_GENERALBone_HARA->node, a0, a1, p, 0.0f, MIN(fl, fr) * -2.0f, side);
    _setNodeHPBIllegal(SkelFocusDef_BOSS_GENERALBone_MUNE->node, a0, a1, p, side * 2.0f, MIN(fl, fr) * -2.0f + rear, -((fr - fl) * 4.0f));
    _setNodeHPBIllegal(SkelFocusDef_BOSS_GENERALBone_KUBI->node, a0, a1, p, (fr - fl) * 5.0f + (rl - rr) * 2.0f, MIN(fl, fr) * 2.0f, 0.0f);
    _setNodeHPBIllegal(SkelFocusDef_BOSS_GENERALBone_KUBI_B->node, a0, a1, p, 0.0f, 0.0f, -(side * 3.0f));
    _setNodeHPBIllegal(SkelFocusDef_BOSS_GENERALBone_KATA_L->node, a0, a1, p, fl, fl * -8.0f + fr * -3.0f, fl * 20.0f);
    _setNodeHPBIllegal(SkelFocusDef_BOSS_GENERALBone_KATA_R->node, a0, a1, p, -fr, -(fr * 8.0f) - fl * 3.0f, fr * -20.0f);
    _setNodeHPBIllegal(SkelFocusDef_BOSS_GENERALBone_KOSI->node, a0, a1, p, 0.0f, MIN(rl, rr) * -4.0f, -((rl - rr) * 5.0f));
    _setNodeHPBIllegal(SkelFocusDef_BOSS_GENERALBone_MATA_L->node, a0, a1, p, rl * 5.0f, rl * -10.0f, rl * -10.0f);
    _setNodeHPBIllegal(SkelFocusDef_BOSS_GENERALBone_MATA_R->node, a0, a1, p, rr * -5.0f, rr * -10.0f, rr * 10.0f);
    _setNodeHPBIllegal(SkelFocusDef_BOSS_TAIL_A->node, a0, a1, p, rside * 3.0f, MIN(rl, rr), 0.0f);
}
#endif
