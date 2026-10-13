void ForceGameLightFlagEnvelope(void *arg0)
{
    (*(int *)((char *)(arg0) + 0x2C)) = (int) (((*(int *)((char *)(arg0) + 0x2C)) | 0x20000) & 0xFFFEFFFF);
}
