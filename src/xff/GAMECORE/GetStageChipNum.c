typedef struct { int a, b, on; char pad[0x4C]; int num; } Stg;
extern Stg D_0017A340;

int GetStageChipNum(void)
{
    Stg *s = &D_0017A340;

    if (s->on == 0) {
        return 0;
    }
    return s->num;
}
