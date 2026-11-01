typedef struct {
    unsigned int on : 1;
    unsigned int press : 1;
    unsigned int release : 1;
    unsigned int repeat : 1;
    int pad[2];
} KeyState;

typedef struct {
    KeyState key0[256];
    int count0;
    KeyState key1[256];
    KeyState key2[256];
    int count1;
    int count2;
} KbWork;

extern KbWork B_0014A6C0;
extern void func_000CCAE8(void);
extern void usbdevAddCallbackFunc(void *, int);

static inline void clearKeys(KeyState *k)
{
    int i;

    for (i = 0; i < 256; i++) {
        k[i].repeat = 0;
        k[i].release = 0;
        k[i].press = 0;
        k[i].on = 0;
    }
}

void kbInit(void)
{
    B_0014A6C0.count2 = 0;
    B_0014A6C0.count1 = 0;
    B_0014A6C0.count0 = 0;
    clearKeys(B_0014A6C0.key1);
    clearKeys(B_0014A6C0.key2);
    clearKeys(B_0014A6C0.key0);
    usbdevAddCallbackFunc(func_000CCAE8, 1);
}
