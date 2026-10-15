typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern void nicosysdSendDataStart(void *, int, Ptn *, int);
extern void nicosysdSendDataWrite(void *, void *, int);
extern void nicosysdExec(void *, void *, void *);
static void func_000DFA98(void);

int csvMakeClose(int id)
{
    char buf[0x20];
    int res[4];
    int cmd = 2000;
    nicosysdSendDataStart(buf, 0x3E9, &rootPtn, 8);
    nicosysdSendDataWrite(buf, &cmd, 4);
    nicosysdSendDataWrite(buf, &id, 4);
    nicosysdExec(buf, res, func_000DFA98);
    return res[1];
}
