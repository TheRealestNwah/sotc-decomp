typedef struct {
    int id;

} SubAnim;

extern char *GetCharacterClass(int);
extern void func_00051CA0(void);
extern void func_000532C8(int, int, float);

int GetSubAnimation(int obj, float t)
{
    char *chara;
    SubAnim *sub;
    int n;

    if (t == 0.0f) {
        return 0;
    }
    func_00051CA0();
    chara = GetCharacterClass(obj);
    n = *(signed char *)(chara + 0xC94);
    sub = *(SubAnim **)(chara + 0x308);
    while (n--) {
        func_000532C8(obj, sub->id, t);
        sub++;
    }
    *(signed char *)(chara + 0xC94) = 0;
    return 1;
}
