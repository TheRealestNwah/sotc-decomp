typedef unsigned int u128 __attribute__((mode(TI)));
extern int isysWakeupSubThread(unsigned char *);

/* Parked: 15 words differ; original reloads the stack pointer field after the quadword store */
#ifdef NONMATCHING
int isysStartSubThread(unsigned char *o, unsigned int arg)
{
    char *e;
    char *sp;
    switch (o[8]) {
    case 6:
    case 9:
    case 11:
    case 12:
    case 13:
    case 14:
    case 22:
    case 29:
    case 33:
        e = (char *)(o + 0x20);
        break;
    case 7:
    case 8:
    case 10:
    case 15 ... 21:
    case 23 ... 28:
    case 30 ... 32:
        e = 0;
        break;
    default:
        e = 0;
        break;
    }
    sp = *(char **)(e + 0x10);
    *(char **)(e + 0x10) = sp - 0x2C0;
    *(u128 *)(sp - 0x200) = arg;
    *(u128 *)(*(char **)(e + 0x10) + 0x270) = *(unsigned int *)(e + 4);
    *(int *)(e + 0x1C) = 0;
    return isysWakeupSubThread(o);
}
#else
extern int isysStartSubThread(unsigned char *o, unsigned int arg);
#endif
