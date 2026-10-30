extern unsigned char *B_000C5C0C;
extern int B_000C5C08;
extern void all_keyoff(int port);
extern void all_soundoff(int port);
extern int Sg2ModClose(int id);

static void func_000255C8(void)
{
    switch (B_000C5C0C[1]) {
    case 0x2F:
        all_keyoff(B_000C5C08);
        break;
    case 0x3F:
        Sg2ModClose(B_000C5C08);
        break;
    case 0x40:
        all_keyoff(B_000C5C08);
        Sg2ModClose(B_000C5C08);
        break;
    case 0x41:
        all_soundoff(B_000C5C08);
        Sg2ModClose(B_000C5C08);
        break;
    }
}
