extern void *GetScriptLayoutClass(void *);

int ForwardTime__DemoMan(void *actor, float fparg0)
{
    float temp_f1;
    void *temp_v1;

    temp_v1 = (*(void **)((char *)(GetScriptLayoutClass(actor)) + 0x2D8));
    temp_f1 = fparg0 - (*(float *)((char *)(temp_v1) + 0x34));
    (*(float *)((char *)(temp_v1) + 0x38)) = fparg0;
    (*(float *)((char *)(temp_v1) + 0x34)) = fparg0;
    (*(float *)((char *)(temp_v1) + 0x3C)) = (float) (fparg0 * 30.0f);
    (*(float *)((char *)(temp_v1) + 0x24)) = (float) ((*(float *)((char *)(temp_v1) + 0x24)) + temp_f1);
    return 1;
}
