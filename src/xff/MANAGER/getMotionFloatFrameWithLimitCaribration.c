extern void GetMotionFloatFrameNoCaribration(void *, void *, int, float);
extern void func_0003CF68(void *, void *, int, int);

void getMotionFloatFrameWithLimitCaribration(void *output, void *motion, int selector, float frame)
{
    short limit = *(short *)((char *)motion + 4);
    if ((float)limit <= frame) {
        func_0003CF68(output, motion, limit, selector);
        return;
    }
    GetMotionFloatFrameNoCaribration(output, motion, selector, frame);
}
