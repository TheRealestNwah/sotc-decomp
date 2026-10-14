void ForceFogColFlagEnvelope(void *arg0)
{
    (*(int *)((char *)(arg0) + 0x40)) = (int) (((*(int *)((char *)(arg0) + 0x40)) | 0x800) & ~0x400);
}
