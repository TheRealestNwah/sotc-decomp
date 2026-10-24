extern int getAnimObjResource(unsigned int *);

typedef struct {
    char pad[0x50];
    unsigned int resource;
} MotionK;

int GetMotKToMotP(MotionK *motion)
{
    if (motion != 0) {
        if (&motion->resource == 0)
            return 0;
        return getAnimObjResource(&motion->resource);
    }
    return 0;
}
