extern void *GetLayoutClass();

void SCRPlayerRotateStop(void)
{
    void *temp_v1;

    temp_v1 = (*(void **)((char *)(GetLayoutClass()) + 0x19C));
    (*(float *)((char *)(temp_v1) + 0x50)) = (float) ((*(float *)((char *)(temp_v1) + 0x50)) * 0.5f);
}
