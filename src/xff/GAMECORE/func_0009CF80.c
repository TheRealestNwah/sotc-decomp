extern void *isysGetThisSubThread(void);
extern void Kite_StartEventCheck(void *, int);

#define W(type, o) (*(type *)(ai + (o)))

static inline int canStartFirst(char *ai)
{
    if (W(int, 0x500) < 0)
        return 0;
    if (W(float, 0xE0) < *(float *)(W(char *, 0x20) + 0x48))
        return 1;
    return 0;
}

static inline int canStart(char *ai)
{
    if (W(int, 0x2C)) {
        if (W(int, 0x500) != W(int, 0x520))
            return 1;
    } else if (W(int, 0x36C))
        return 1;
    return 0;
}

static void func_0009CF80(char *ai)
{
    int event;
    int ok;

    isysGetThisSubThread();
    if (W(int, 0x1AC) != 8)
        return;
    event = W(int, 0x504);
    switch (event) {
    case 0:
        ok = canStartFirst(ai);
        if (ok) {
            W(int, 0x1AC) = event;
            Kite_StartEventCheck(ai + 0x590, W(int, 0x500));
        }
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        ok = canStart(ai);
        if (ok) {
            W(int, 0x1AC) = event;
            Kite_StartEventCheck(ai + 0x590, W(int, 0x500));
        }
        break;
    case 7:
        break;
    case 8:
        W(int, 0x1AC) = W(int, 0x524);
        break;
    }
}
