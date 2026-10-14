extern void initgc();
extern void initgcchartest();
extern void initgcmain();
extern void initgcmaingp();

int gamecore(void) {
    initgc();
    initgcmain();
    initgcmaingp();
    initgcchartest();
    return 0;
}
