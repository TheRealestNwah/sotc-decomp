extern char B_000DD408[];

int Sg2RemoteGetDspChangeStatus(int i)
{
    return ((int *)B_000DD408)[i];
}
