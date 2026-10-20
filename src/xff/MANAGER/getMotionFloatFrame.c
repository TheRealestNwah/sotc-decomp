typedef struct { char pad[4]; short frameCount; } Motion;
extern void GetMotionFloatFrameNoCaribration(void *, void *, int, float);
void getMotionFloatFrame(void *output, Motion *motion, int selector, float frame)
{
    float original = frame;
    if (motion->frameCount == 1) {
        int integer = (int)frame;
        frame -= (float)integer;
    } else {
        int last = motion->frameCount - 1;
        frame -= (float)(last * (int)(frame / (float)last));
    }
    if (frame == 0.0f && original > 0.0f)
        frame = (float)(motion->frameCount - 1);
    GetMotionFloatFrameNoCaribration(output, motion, selector, frame);
}
