extern char *GetCharacterClass(int);

typedef struct {
    int a, b, c, d;
} MotionShiftCallBackEntry;

typedef struct {
    int n;
    MotionShiftCallBackEntry *e;
} MotionShiftCallBackTable;

int ResetCharacterObjMotionShiftCallBackEntryAll(int o)
{
    char *c = GetCharacterClass(o);
    if (c != 0) {
        MotionShiftCallBackTable *t = (MotionShiftCallBackTable *)(c + 0x2C8);
        int n = t->n;
        MotionShiftCallBackEntry *e = t->e;
        int i;
        for (i = 0; i < n; i++, e++) {
            e->a = 0;
            e->b = 0;
            e->c = 0;
            e->d = 0;
        }
        return 0;
    }
    return -1;
}
