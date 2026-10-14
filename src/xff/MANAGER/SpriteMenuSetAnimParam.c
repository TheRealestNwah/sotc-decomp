#define NULL ((void *)0)
void SpriteMenuSetAnimParam(void *arg0, int arg1, int arg2, int arg3, float fparg0)
{
    int temp_v0;
    unsigned int temp_v1;

    if ((arg0 != NULL) && ((temp_v1 = (*(unsigned int *)((char *)(arg0) + 8)), temp_v0 = (temp_v1 >> 0x1B) & 0xF, (temp_v0 == 0)) || (arg3 != 0))) {
        if (temp_v0 != arg1) {
            (*(float *)((char *)(arg0) + 0xC)) = fparg0;
        }
        (*(unsigned int *)((char *)(arg0) + 8)) = (unsigned int) ((((temp_v1 & 0x87FFFFFF) | ((arg1 & 0xF) << 0x1B)) & 0x7FFFFFFF) | (arg2 << 0x1F));
    }
}
