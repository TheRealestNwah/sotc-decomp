extern unsigned char B_000E11C0;
extern void (*B_000E11C8)(int, int, int);
extern unsigned char B_000E11D0[];
extern int B_000E19D0;
extern int B_000E19D4;

static void func_0002CD00(unsigned char *p)
{
    unsigned char **cur = (unsigned char **)(p + 0x60);
    unsigned char ctrl;
    unsigned char val;
    int pass = 0;
    int status;
    int loop;

    ctrl = *(*cur)++;
    val = *(*cur)++;
    switch (ctrl) {
    case 99:
        switch (val) {
        case 20:
            p[0x69] = p[0x68];
            *(unsigned char **)(p + 0x6C) = *cur;
            break;
        case 30:
            loop = *(int *)(p + 0x70);
            if (loop != 0x7F) {
                int next = loop - 1;

                *(int *)(p + 0x70) = next;
                loop = next;
            }
            if (loop > 0) {
                p[0x68] = p[0x69];
                *cur = *(unsigned char **)(p + 0x6C);
            }
            break;
        default:
            pass = 1;
            break;
        }
        break;
    case 90:
        if (B_000E11C8)
            B_000E11C8(B_000E11C0, p[0x68] & 0xF, val);
        break;
    case 102:
        *(int *)(p + 0x70) = val;
        break;
    default:
        pass = 1;
        break;
    }
    if (pass) {
        status = p[0x68];
        if (B_000E19D4 != status) {
            B_000E19D4 = status;
            B_000E11D0[B_000E19D0++] = status;
        }
        B_000E11D0[B_000E19D0++] = ctrl;
        B_000E11D0[B_000E19D0++] = val;
    }
}
