#ifdef NONMATCHING
/* 63 diffs, same length (143 words). Draft from the asm; sibling of nico_kameBodyExpression with different formulas: reads the four MotRootHeightAdjust expression points (FR, FL, RR, RL), calls _setRootXYZHPB with roll -0.1 * side, 0.2 * the leg sum, 0.4 * the front/rear difference, 12 * that difference and -3 * side, then four _setNodeHPBIllegal calls (hip B_L / B_R at 12 * the front sum, jowan L / R at 5 * the front sum). The shared 12.0f in a local ($f26 in the Original) got the length right. Remaining differences are float register assignment (Original: FR $f23, zero $f21, RR $f22, hip $f25; ours picks $f21/$f22/$f23) and a swapped $s2/$s3 pair for the two ints. Permuter (12 workers, 12 min): 4130 -> 2925. */
typedef struct {
    int pad0;
    unsigned int bits;
    int node;
} NodeDef;

extern char *GetCharacterClass(void *);
extern float getexpressiondatapoint(int, int);
extern void _setRootXYZHPB(int, int, void *, void *, void *, float, float, float, float, float, float);
extern void _setNodeHPBIllegal(int, int, int, void *, float, float, float);
extern NodeDef *MotRootHeightAdjustNodeDef_LEO_FRONT_RIGHT;
extern NodeDef *MotRootHeightAdjustNodeDef_LEO_FRONT_LEFT;
extern NodeDef *MotRootHeightAdjustNodeDef_LEO_REAR_RIGHT;
extern NodeDef *MotRootHeightAdjustNodeDef_LEO_REAR_LEFT;
extern NodeDef *SkelFocusDef_LEOBone_B_HIP_B_L;
extern NodeDef *SkelFocusDef_LEOBone_B_HIP_B_R;
extern NodeDef *SkelFocusDef_LEOBone_F_JOWAN_L;
extern NodeDef *SkelFocusDef_LEOBone_F_JOWAN_R;

void nico_leoBodyExpression(void *obj)
{
    char *c = GetCharacterClass(obj);
    int exp = *(int *)(c + 0x338);
    int a0 = *(int *)(c + 0x358);
    int a1 = *(int *)(c + 0x2E8);
    float k = 12.0f;
    float fr = getexpressiondatapoint(exp, (MotRootHeightAdjustNodeDef_LEO_FRONT_RIGHT->bits >> 18) & 0xFFF);
    float fl = getexpressiondatapoint(exp, (MotRootHeightAdjustNodeDef_LEO_FRONT_LEFT->bits >> 18) & 0xFFF);
    float rr = getexpressiondatapoint(exp, (MotRootHeightAdjustNodeDef_LEO_REAR_RIGHT->bits >> 18) & 0xFFF);
    float rl = getexpressiondatapoint(exp, (MotRootHeightAdjustNodeDef_LEO_REAR_LEFT->bits >> 18) & 0xFFF);
    float front = fr + fl;
    float hip = front * k;
    float side = (fl + rl) - (fr + rr);
    float fb = front - rr - rl;

    _setRootXYZHPB(a0, a1, c + 0x470, c + 0x40, c + 0x90, side * -0.1f, ((fl + rl) + fr + rr) * 0.2f, fb * 0.4f, 0.0f, fb * k, side * -3.0f);
    _setNodeHPBIllegal(SkelFocusDef_LEOBone_B_HIP_B_L->node, a0, a1, c + 0x470, 0.0f, hip, 0.0f);
    _setNodeHPBIllegal(SkelFocusDef_LEOBone_B_HIP_B_R->node, a0, a1, c + 0x470, 0.0f, hip, 0.0f);
    front *= 5.0f;
    _setNodeHPBIllegal(SkelFocusDef_LEOBone_F_JOWAN_L->node, a0, a1, c + 0x470, 0.0f, front, 0.0f);
    _setNodeHPBIllegal(SkelFocusDef_LEOBone_F_JOWAN_R->node, a0, a1, c + 0x470, 0.0f, front, 0.0f);
}
#endif
