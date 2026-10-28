typedef struct Ptn Ptn;
typedef struct ReadPacket { int id, unknown04, size; } ReadPacket;
extern Ptn rootPtn;
extern void nicosysdSendDataStart(void *, int, Ptn *, int);
extern void nicosysdSendDataWrite(void *, void *, int);
extern void nicosysdExec(int, int, int);
static void func_000DFA98(int, ReadPacket *);

int csvMakeClose(int id)
{
    char buf[0x20];
    int res[4];
    int cmd = 2000;
    nicosysdSendDataStart(buf, 0x3E9, &rootPtn, 8);
    nicosysdSendDataWrite(buf, &cmd, 4);
    nicosysdSendDataWrite(buf, &id, 4);
    nicosysdExec((int)buf, (int)res, (int)func_000DFA98);
    return res[1];
}
