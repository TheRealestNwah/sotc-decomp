typedef struct {
    int pad[2];
    int trigger;
} PadManagerData;

extern PadManagerData padManagerData;
extern signed char *D_00136E78;

static inline int padBit(int key)
{
    return 1 << key;
}

int spriteMenuCheckSelectPushPad(void)
{
    signed char *keys = D_00136E78;
    int trigger = padManagerData.trigger;
    return (trigger & padBit(keys[0])) ? 1 : (trigger & padBit(keys[1])) ? -1 : 0;
}
