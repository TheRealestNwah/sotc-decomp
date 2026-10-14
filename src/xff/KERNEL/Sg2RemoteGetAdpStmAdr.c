extern char B_000DD340[];

int Sg2RemoteGetAdpStmAdr(int i)
{
    return ((int *)B_000DD340)[i];
}
