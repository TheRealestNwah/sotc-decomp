extern void Kite_StartEventCheck(void *, int);
extern void Kite_EndEventCheck(char *);
extern int func_0009BC48(char *);
extern int func_0009BDC8(char *);
extern int func_0009BFA0(char *);

#define W(type, o) (*(type *)(ai + (o)))

static inline void startEvent(char *ai)
{
    Kite_StartEventCheck(ai + 0x590, W(int, 0x500));
}

static void func_0009D088(char *ai)
{
    switch (W(int, 0x1A8)) {
    case 0:
        W(int, 0x1AC) = 8;
        Kite_EndEventCheck(ai + 0x590);
        break;
    case 1:
        if (func_0009BC48(ai)) {
            W(int, 0x1AC) = 8;
            Kite_EndEventCheck(ai + 0x590);
        }
        break;
    case 2:
        if (func_0009BDC8(ai)) {
            W(int, 0x1AC) = 8;
            Kite_EndEventCheck(ai + 0x590);
        }
        break;
    case 3:
        if (func_0009BFA0(ai)) {
            W(int, 0x1AC) = 8;
            Kite_EndEventCheck(ai + 0x590);
        }
        break;
    case 4:
        if (func_0009BC48(ai)) {
            W(int, 0x1AC) = 8;
            Kite_EndEventCheck(ai + 0x590);
        }
        break;
    case 5:
        if (func_0009BDC8(ai)) {
            W(int, 0x1AC) = 8;
            Kite_EndEventCheck(ai + 0x590);
        }
        break;
    case 6:
        if (func_0009BFA0(ai)) {
            W(int, 0x1AC) = 8;
            Kite_EndEventCheck(ai + 0x590);
        }
        break;
    case 7: {
        int ok = W(int, 0x190) == 0xC;
        if (ok) {
            W(int, 0x1AC) = W(int, 0x504);
            startEvent(ai);
        }
        break;
    }
    }
}
