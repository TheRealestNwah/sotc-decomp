extern void *GetLayoutClass(void *);

void SCRPlayerRotateStop(void *actor)
{
    void *temp_v1;

    temp_v1 = (*(void **)((char *)(GetLayoutClass(actor)) + 0x19C));
    (*(float *)((char *)(temp_v1) + 0x50)) = (float) ((*(float *)((char *)(temp_v1) + 0x50)) * 0.5f);
}
