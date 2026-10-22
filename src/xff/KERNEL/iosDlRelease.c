typedef struct {
    int work[2];
    int adrs[2];
    int ptr;
    int layer_num;
    int cur;
} DlBufs;
extern volatile DlBufs B_00065018;
extern void iosFree(void *);

void iosDlRelease(void)
{
    int index;
    for (index = 0; index < 2; index++) {
        if (B_00065018.adrs[index])
            iosFree((void *)B_00065018.adrs[index]);
        if (B_00065018.work[index])
            iosFree((void *)B_00065018.work[index]);
    }
}
