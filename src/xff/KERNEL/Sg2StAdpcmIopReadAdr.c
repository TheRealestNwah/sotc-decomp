extern int Sg2RemoteGetAdpStmAdr();

int Sg2StAdpcmIopReadAdr(int a, int b, int c, int d)
{
    return Sg2RemoteGetAdpStmAdr(a, b, c, d);
}
