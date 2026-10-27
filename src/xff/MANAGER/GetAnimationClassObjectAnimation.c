extern int GetObjectAnimationFloatFrame(void *out, void *motion, int index,
                                       float frame, float previousFrame);

int GetAnimationClassObjectAnimation(void *out, float *frame, void *motion, int index)
{
    return GetObjectAnimationFloatFrame(out, motion, index, frame[2], frame[3]);
}
