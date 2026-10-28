typedef struct Ptn Ptn;
typedef struct ReadPacket { int id, unknown04, size; } ReadPacket;
extern Ptn rootPtn;
extern int strlen(const char *);
extern void nicosysdSendDataStart(void *, int, Ptn *, int);
extern void nicosysdSendDataWrite(void *, const void *, int);
extern void nicosysdExec(int, int, int);
extern void func_000DFA98(int, ReadPacket *);

int csvMakeDeleteSegment(int id, const char *name)
{
    char buffer[0x20];
    int response[4];
    int command;
    int size = strlen(name) + 1;
    command = 2001;
    nicosysdSendDataStart(buffer, 1001, &rootPtn, size + 12);
    nicosysdSendDataWrite(buffer, &command, 4);
    nicosysdSendDataWrite(buffer, &id, 4);
    nicosysdSendDataWrite(buffer, &size, 4);
    nicosysdSendDataWrite(buffer, name, size);
    nicosysdExec((int)buffer, (int)response, (int)func_000DFA98);
    return response[1];
}
