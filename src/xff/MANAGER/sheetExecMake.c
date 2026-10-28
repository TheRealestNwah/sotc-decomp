typedef struct Ptn Ptn;
typedef struct { int id, b, pos; void *buf; int size; } SendBuf;
typedef struct { char pad[8]; int size; } ReadPacket;

extern Ptn rootPtn;
extern int strlen(const char *);
extern void nicosysdSendDataStart(SendBuf *, int, Ptn *, int);
extern void nicosysdSendDataWrite(SendBuf *, void *, int);
extern void nicosysdExec(int, int, int);
extern void nicosysdEchoDdebugPrintReadCallBack(int, ReadPacket *);

int sheetExecMake(void)
{
    int response[4];
    char buffer[0x20];
    char command[] = "nicomkdata";
    int size = strlen(command) + 1;

    nicosysdSendDataStart((SendBuf *)buffer, 0x3EB, &rootPtn, size);
    nicosysdSendDataWrite((SendBuf *)buffer, command, size);
    nicosysdExec((int)buffer, (int)response, (int)nicosysdEchoDdebugPrintReadCallBack);
    return response[1];
}
