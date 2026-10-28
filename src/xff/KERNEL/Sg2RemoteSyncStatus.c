extern int sceSifCheckStatRpc(void *);
extern unsigned char B_000DD440[];
int Sg2RemoteSyncStatus(void)
{
    return sceSifCheckStatRpc(B_000DD440);
}
