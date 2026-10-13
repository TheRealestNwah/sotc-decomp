extern int B_0018A560;

void nico_IK_idDetect(void *arg0)
{
    B_0018A560 = (*(int *)((char *)(arg0) + 0x14)) & 0xFFFEFFFF;
}
