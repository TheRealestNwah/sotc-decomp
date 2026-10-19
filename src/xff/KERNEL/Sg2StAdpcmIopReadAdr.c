extern int Sg2RemoteGetAdpStmAdr(int);

int Sg2StAdpcmIopReadAdr(int channel)
{
    return Sg2RemoteGetAdpStmAdr(channel);
}