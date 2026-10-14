void ForceGlobalLightFlagEnvelope(void *arg0)
{
    (*(int *)((char *)(arg0) + 0x110)) = (int) (((*(int *)((char *)(arg0) + 0x110)) | 0x20000) & 0xFFFEFFFF);
}
