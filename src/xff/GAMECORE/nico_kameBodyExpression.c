typedef struct {
    int pad0;
    unsigned int bits;
} NodeDef;

extern char *GetCharacterClass(void *);
extern float getexpressiondatapoint(int, int);
extern void _setRootXYZHPB(int, int, void *, void *, void *, float, float, float, float, float, float);
extern NodeDef *MotRootHeightAdjustNodeDef_KAME_FRONT_RIGHT;
extern NodeDef *MotRootHeightAdjustNodeDef_KAME_FRONT_LEFT;
extern NodeDef *MotRootHeightAdjustNodeDef_KAME_REAR_RIGHT;
extern NodeDef *MotRootHeightAdjustNodeDef_KAME_REAR_LEFT;

void nico_kameBodyExpression(void *obj)
{
    char *c = GetCharacterClass(obj);
    int exp = *(int *)(c + 0x338);
    int a0 = *(int *)(c + 0x358);
    int a1 = *(int *)(c + 0x2E8);
    float fr = getexpressiondatapoint(exp, (MotRootHeightAdjustNodeDef_KAME_FRONT_RIGHT->bits >> 18) & 0xFFF);
    float fl = getexpressiondatapoint(exp, (MotRootHeightAdjustNodeDef_KAME_FRONT_LEFT->bits >> 18) & 0xFFF);
    float rr = getexpressiondatapoint(exp, (MotRootHeightAdjustNodeDef_KAME_REAR_RIGHT->bits >> 18) & 0xFFF);
    float rl = getexpressiondatapoint(exp, (MotRootHeightAdjustNodeDef_KAME_REAR_LEFT->bits >> 18) & 0xFFF);
    float front = fl + fr;
    float rear = rl + rr;
    float roll = (fl + rl) - (fr + rr);

    _setRootXYZHPB(a0, a1, c + 0x470, c + 0x40, c + 0x90, roll * -0.19999999f,
                   (front * 0.5f + (rear + rear)) * 0.19999999f - 1.0f, (front - rear) * 0.19999999f, 0.0f,
                   front * 1.5999999046325684f - rear * 1.4f, -roll);
}
