typedef union {
    float values[4];
    long words[2];
} DebugColor;

extern void DebugDispVolumeShapeColor(void *, float *);

void DebugDispVolumeShape(void *shape)
{
    DebugColor color = {{1.0f, 1.0f, 1.0f, 1.0f}};

    DebugDispVolumeShapeColor(shape, color.values);
}
