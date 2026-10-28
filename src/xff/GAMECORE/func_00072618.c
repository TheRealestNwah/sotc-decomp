typedef struct {
    char pad[0x314];
    int binding[10];
} OptionBindings;
typedef struct {
    int values[7];
    int binding[10];
    int controls[5];
} OptionSnapshot;
extern OptionBindings gcGlobalVar;
extern OptionSnapshot B_0018B6A8;
extern int (*D_0017AD70[])(void);
extern int getZoomKey(void), getInterestKey(void), getBossInterestKey(void);
extern void *memcpy(void *, const void *, unsigned int);
static void func_00072618(void)
{
    B_0018B6A8.values[0] = D_0017AD70[0]();
    B_0018B6A8.values[1] = D_0017AD70[1]();
    B_0018B6A8.values[2] = D_0017AD70[2]();
    B_0018B6A8.values[3] = D_0017AD70[3]();
    B_0018B6A8.values[4] = D_0017AD70[4]();
    B_0018B6A8.values[5] = D_0017AD70[5]();
    B_0018B6A8.values[6] = D_0017AD70[6]();
    memcpy(B_0018B6A8.binding, gcGlobalVar.binding, sizeof(gcGlobalVar.binding));
    B_0018B6A8.binding[8] = getZoomKey();
    B_0018B6A8.binding[9] = getInterestKey();
    B_0018B6A8.binding[7] = getBossInterestKey();
    B_0018B6A8.controls[0] = D_0017AD70[7]();
    B_0018B6A8.controls[1] = D_0017AD70[8]();
    B_0018B6A8.controls[2] = D_0017AD70[9]();
    B_0018B6A8.controls[3] = D_0017AD70[10]();
    B_0018B6A8.controls[4] = D_0017AD70[11]();
}
