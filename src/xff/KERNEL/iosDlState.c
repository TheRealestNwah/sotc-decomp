/* Display-list state fields accessed by these getters. */
typedef struct {
    char pad0[0x14];
    int layer_num;
    int work_buf;
    int layer;
    char pad20[0x10];
} DlState;

extern volatile DlState B_00065018;

int iosDlGetWorkBufId(void)
{
    volatile DlState *dl = &B_00065018;

    return dl->work_buf;
}

int iosDlGetLayer(void)
{
    volatile DlState *dl = &B_00065018;

    return dl->layer;
}

int iosDlGetLayerNum(void)
{
    volatile DlState *dl = &B_00065018;

    return dl->layer_num;
}
