extern char *padSysGet(int port, int slot);

int iosPadChkConnect(int port)
{
    return (unsigned int)(*(int *)(padSysGet(port, 0) + 0x118) - 1) < 2;
}
