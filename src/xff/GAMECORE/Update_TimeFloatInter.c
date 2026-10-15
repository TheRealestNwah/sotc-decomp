extern unsigned char gcGlobalVar[];

void Update_TimeFloatInter(void *arg0)
{
    float temp_f0;
    float temp_f0_2;
    float temp_f1;
    float temp_f4;
    float temp_f5;

    temp_f0 = (*(float *)((char *)(arg0) + 0x10));
    if (temp_f0 > 0.0f) {
        temp_f4 = (*(float *)((char *)(arg0) + 0));
        temp_f1 = temp_f0 - (*(float *)((char *)(gcGlobalVar) + 0x180));
        temp_f5 = (*(float *)((char *)(arg0) + 8));
        (*(float *)((char *)(arg0) + 0x10)) = temp_f1;
        temp_f0_2 = (temp_f4 - temp_f1) / temp_f4;
        (*(float *)((char *)(arg0) + 0xC)) = (float) ((temp_f5 * temp_f0_2) + ((*(float *)((char *)(arg0) + 4)) * (1.0f - temp_f0_2)));
        if (temp_f1 <= 0.0f) {
            (*(float *)((char *)(arg0) + 0xC)) = temp_f5;
        }
    }
}
