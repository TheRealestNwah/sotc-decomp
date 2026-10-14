extern void sceSifCheckStatRpc(void *);
extern unsigned char B_000DD440[1];

void Sg2RemoteSyncStatus(void)
{
    sceSifCheckStatRpc(&B_000DD440);
}
