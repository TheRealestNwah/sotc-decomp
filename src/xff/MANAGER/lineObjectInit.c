extern int (*D_00136050[])(int);
extern int B_00148730[];
extern char B_00148798[];
extern void isysInitGroup(void *);

void lineObjectInit(void)
{
    int i;

    for (i = 0; i < 26; i++) {
        if (D_00136050[i] != 0)
            B_00148730[i] = D_00136050[i](i & 1);
    }
    isysInitGroup(B_00148798);
}
