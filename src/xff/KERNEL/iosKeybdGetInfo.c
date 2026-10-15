extern int B_000C3980;
extern char B_000C3988[];
extern char B_000C39C0[];
extern void func_0001EFE8();
extern void WaitSema(int);
extern int sceSifCallRpc(void *, int, int, void *, int, void *, int, void *, void *);

void iosKeybdGetInfo(void *buf)
{
    WaitSema(B_000C3980);
    sceSifCallRpc(B_000C3988, 1, 1, B_000C39C0, 0x20, buf, 0x20, func_0001EFE8, 0);
}
