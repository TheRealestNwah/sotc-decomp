typedef int s128 __attribute__((mode(TI)));
struct Quad { s128 q; };
extern struct Quad ZeroPoint;
extern struct Quad ZeroVector;

void constructor_camera_pause_rise(void *work)
{
    *(int *)work = 0;
    *(int *)((char *)work + 4) = 0;
    *(struct Quad *)((char *)work + 0x10) = ZeroPoint;
    *(struct Quad *)((char *)work + 0x20) = ZeroPoint;
    *(struct Quad *)((char *)work + 0x30) = ZeroVector;
    *(float *)((char *)work + 0x44) = 4.5f;
    *(float *)((char *)work + 0x40) = 4.5f;
    *(float *)((char *)work + 0x48) = 45.0f;
}