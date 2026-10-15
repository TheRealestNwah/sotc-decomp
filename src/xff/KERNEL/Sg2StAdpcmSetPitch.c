extern int Sg2RemoteSend(int, int, int, int);

int Sg2StAdpcmSetPitch(unsigned long id, unsigned int pitch)
{
    if (pitch <= 0x2EE00 && id != 0) {
        Sg2RemoteSend(0x1B, id & 0xFFFFFF, (id >> 24) & 0xFFFFFF, pitch);
        return 0;
    }
    return -1;
}
