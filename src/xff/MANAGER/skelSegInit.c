extern void func_00081198(void *, int *);
extern void func_00081388(int *, void *);

typedef struct {
    char pad0[8];
    char *definition;
    char padC[12];
    int refs[2];
    int finalRef;
} SkeletonSegment;

typedef struct {
    char pad0[12];
    int count;
    SkeletonSegment *segments;
} SkeletonSegments;

void skelSegInit(SkeletonSegments *work)
{
    int remaining = work->count;
    SkeletonSegment *segment = work->segments;

    for (--remaining; remaining != -1; --remaining) {
        int *reference = segment->refs;
        int pair = 1;
        void *skeleton = *(void **)(segment->definition + 0x20);
        do {
            func_00081198(skeleton, reference++);
        } while (--pair != -1);
        func_00081388(&segment->finalRef, skeleton);
        segment++;
    }
}
