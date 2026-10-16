typedef struct {
    long w[4];
} AttainRange;

extern char *getSCRDataCtrlWork(void *);
extern void setSCRAttainRange(void *, int);
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern int chkAttainExecLayout(void *, void *, void *, void *);
extern void setAttainRangeStruct(void *, AttainRange *);

int SCRConditionAttainRange(void *a, int b, int c, int d, int e, int f, int g, int i, int range)
{
    char *w = getSCRDataCtrlWork(a);
    AttainRange save;
    int r;

    save = *(AttainRange *)(w + 0x3E0);
    setSCRAttainRange(w, range);
    r = chkAttainExecLayout(w, w + 0x60, GetLayoutClass(a), GetCharacterClass(a));
    setAttainRangeStruct(w, &save);
    return r == 1;
}
