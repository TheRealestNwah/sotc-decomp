typedef int s128 __attribute__((mode(TI)));

extern s128 All1Vector;
extern s128 ZeroVector;
extern s128 IdentityQuaternion;
extern s128 ZeroPoint;
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern int CheckUnderVariableXZSurface(void *, void *, void *, void *);
extern void SetGeometryPointerNodePosState(void *, void *, int, void *, void *);
extern int ExecEff();

static int func_000913D0(void *a, void *b, void *ch, void *obj, void *c)
{
    char *cc = GetCharacterClass(ch);

    if (cc != 0) {
        char *lay = GetLayoutClass(obj);

        if (CheckUnderVariableXZSurface(0, *(void **)(lay + 0x134), *(void **)(lay + 0x134),
                                        *(char **)(cc + 0xE38) + *(short *)(cc + 0x370) * 4)) {
            if (*(float *)(lay + 0x90) < 0.5f)
                *(s128 *)(lay + 0x90) = All1Vector;
        } else if (0.5f < *(float *)(lay + 0x90)) {
            char geo[0x40];

            SetGeometryPointerNodePosState(geo, obj, 0, &IdentityQuaternion, &ZeroPoint);
            ExecEff(b, ch, c, a, geo);
            *(s128 *)(lay + 0x90) = ZeroVector;
        }
    }
    return 0;
}
