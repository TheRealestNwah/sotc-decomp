extern void *GetObjectAnimationFloatFrame(void *a, void *b, void *c, float f0, float f1);

void *GetAnimationClassObjectAnimation(void *obj, float *frame, void *b, void *c)
{
    return GetObjectAnimationFloatFrame(obj, b, c, frame[2], frame[3]);
}
