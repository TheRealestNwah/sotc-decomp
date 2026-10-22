typedef struct { int unk0, unk4; void *direction; } MotionTrack;
typedef struct { char pad[4]; short frameCount; char pad6[10]; MotionTrack *tracks; } Motion;
static void func_00039FA8(void *, void *, int, int, float);
void GetMotionNS_RootDirInfo(void *output, Motion *motion, int selector, float frame)
{
    MotionTrack *track = &motion->tracks[selector];
    int whole;
    if (motion->frameCount == 1) {
        int integer = (int)frame;
        frame -= (float)integer;
    } else {
        int last = motion->frameCount - 1;
        frame -= (float)(last * (int)(frame / (float)last));
    }
    whole = (int)frame;
    func_00039FA8(output, track->direction, whole, whole + 1, frame - (float)whole);
}

