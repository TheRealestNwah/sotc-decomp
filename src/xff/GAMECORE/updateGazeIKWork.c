typedef int s128 __attribute__((mode(TI)));

void updateGazeIKWork(char *w, s128 *target)
{
    s128 *gaze = *(s128 **)(w + 0x110C);

    if (gaze) {
        *gaze = *target;
        ((float *)gaze)[3] = 1.0f;
    }
}
