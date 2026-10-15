extern int Sg2RemoteSend(int, int, int, int);

int Sg2StAdpcmSetVolume(unsigned long id, unsigned int l, int r)
{
    if (l < 0x4000 && r >= 0 && r < 0x4000 && id != 0) {
        Sg2RemoteSend(0x1A, id & 0xFFFFFF, (id >> 24) & 0xFFFFFF, (l << 16) | r);
        return 0;
    }
    return -1;
}
