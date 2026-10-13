extern unsigned char B_00054800[1];
extern int D_000409B0;

void *GetLastQuaternion(void)
{
    return (D_000409B0 * 0x10) + (&B_00054800 - 0x10);
}
