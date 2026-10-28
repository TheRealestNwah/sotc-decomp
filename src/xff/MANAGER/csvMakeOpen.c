typedef struct Ptn Ptn;
typedef struct ReadPacket { int id, unknown04, size; } ReadPacket;
extern Ptn rootPtn;
extern int strlen(const char *);
extern int iosSPrintf(char *, const char *, ...);
extern void nicosysdSendDataStart(void *, int, Ptn *, int);
extern void nicosysdSendDataWrite(void *, const void *, int);
extern void nicosysdExec(int, int, int);
extern void func_000DFA98(int, ReadPacket *);

int csvMakeOpen(const char *name)
{
    char buffer[0x20];
    int response[4];
    int command;
    int size;
    int length = strlen(name);
    char filename[length + 60];
    command = 1000;
    size = length + 60;
    length += 68;
    iosSPrintf(filename, "%s", name);
    nicosysdSendDataStart(buffer, 1001, &rootPtn, length);
    nicosysdSendDataWrite(buffer, &command, 4);
    nicosysdSendDataWrite(buffer, &size, 4);
    nicosysdSendDataWrite(buffer, filename, size);
    nicosysdExec((int)buffer, (int)response, (int)func_000DFA98);
    return response[1];
}
