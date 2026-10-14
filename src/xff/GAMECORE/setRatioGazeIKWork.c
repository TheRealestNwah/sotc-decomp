void setRatioGazeIKWork(void *actor, float x, float y, float z) {
    void *work = *(void **)((char *)actor + 0x110C);

    if (work != 0) {
        if (*(float *)((char *)work + 0x34) != x ||
            *(float *)((char *)work + 0x38) != y ||
            *(float *)((char *)work + 0x3C) != z) {
            *(float *)((char *)work + 0x70) = 1.0f;
        }
        *(float *)((char *)work + 0x34) = x;
        *(float *)((char *)work + 0x38) = y;
        *(float *)((char *)work + 0x3C) = z;
    }
}
