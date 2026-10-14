typedef int s128 __attribute__((mode(TI)));
struct Quad { s128 q; };
extern struct Quad ZeroPoint;
extern struct Quad ZeroVector;
void constructor_camera_lws_anime_data(void *work)
{
    *(int *)((char *)work + 4) = 0;
    *(int *)work = -1;
    *(int *)((char *)work + 8) = -1;
    *(struct Quad *)((char *)work + 0x10) = ZeroVector;
    *(struct Quad *)((char *)work + 0x20) = ZeroVector;
    *(struct Quad *)((char *)work + 0x30) = ZeroPoint;
    *(struct Quad *)((char *)work + 0x40) = ZeroPoint;
    *(int *)((char *)work + 0x50) = 0;
    *(int *)((char *)work + 0x54) = -1;
    *(struct Quad *)((char *)work + 0x60) = ZeroPoint;
    *(struct Quad *)((char *)work + 0x70) = ZeroPoint;
    *(int *)((char *)work + 0x80) = 0;
    *(int *)((char *)work + 0x84) = 0;
    *(int *)((char *)work + 0x88) = 0;
    *(float *)((char *)work + 0x8C) = 1.0f;
}