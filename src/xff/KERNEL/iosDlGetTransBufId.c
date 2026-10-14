typedef struct {
    char pad0[0x18];
    int work_buf;
} DlState;

extern volatile DlState B_00065018;

int iosDlGetTransBufId(void)
{
    volatile DlState *dl = &B_00065018;

    return dl->work_buf == 0;
}
