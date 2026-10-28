typedef char *va_list;
#define va_start(ap, last) (ap = (char *)__builtin_next_arg(last) - (__builtin_args_info(2) < 8 ? (8 - __builtin_args_info(2)) * 8 : 0))
typedef struct Ptn Ptn;
typedef struct ReadPacket { int id, unknown04, size; } ReadPacket;
extern Ptn rootPtn;
extern char B_001507B8[];
extern int strlen(const char *);
extern int vsprintf(char *, const char *, va_list);
extern void iosJumpRecoverPoint(const char *, ...);
extern void nicosysdSendDataStart(void *, int, Ptn *, int);
extern void nicosysdSendDataWrite(void *, const void *, int);
extern void nicosysdExec(int, int, int);
extern void func_000DFA98(int, ReadPacket *);

int csvMakeBlockWriteData(int id, const char *format, ...)
{
    char buffer[0x20];
    int response[4];
    int command = 2006;
    int size;
    va_list args;
    va_start(args, format);
    B_001507B8[0x1000] = 0;
    vsprintf(B_001507B8, format, args);
    if (B_001507B8[0x1000] != 0)
        iosJumpRecoverPoint("csvMakeBlockWriteData:buffer over\n");
    size = strlen(B_001507B8) + 1;
    nicosysdSendDataStart(buffer, 1001, &rootPtn, size + 12);
    nicosysdSendDataWrite(buffer, &command, 4);
    nicosysdSendDataWrite(buffer, &id, 4);
    nicosysdSendDataWrite(buffer, &size, 4);
    nicosysdSendDataWrite(buffer, B_001507B8, size);
    nicosysdExec((int)buffer, (int)response, (int)func_000DFA98);
    return response[1];
}
