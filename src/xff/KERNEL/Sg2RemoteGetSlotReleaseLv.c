extern char B_000DD280[];

int Sg2RemoteGetSlotReleaseLv(int i)
{
    return ((int *)B_000DD280)[i];
}
