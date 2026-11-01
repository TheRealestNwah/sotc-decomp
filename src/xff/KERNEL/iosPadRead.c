typedef struct {
    int data[0x78 / 4];
} PadData;
extern PadData iosDefaultPadData[];

void iosPadRead(int port, PadData *out)
{
    *out = iosDefaultPadData[port];
}
