typedef struct { unsigned char fields[16]; } MotionOption;
typedef struct {
    unsigned char pad0[4];
    short frames;
    unsigned char pad6[0x16];
    MotionOption *options;
} Motion;
extern void func_00032E98(void *, void *, void *, MotionOption *, int, float);
void GetMotionOptionNodeFloatFrameDirectResource(void *a, void *b, void *c, Motion *motion, int node, float frame)
{
    func_00032E98(a,b,c,&motion->options[node],motion->frames,frame);
}
