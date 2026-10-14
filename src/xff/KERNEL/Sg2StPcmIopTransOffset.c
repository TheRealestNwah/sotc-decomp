extern int Sg2RemoteGetPcmStmTransOffset();

int Sg2StPcmIopTransOffset(int a, int b, int c, int d)
{
    return Sg2RemoteGetPcmStmTransOffset(a, b, c, d);
}
