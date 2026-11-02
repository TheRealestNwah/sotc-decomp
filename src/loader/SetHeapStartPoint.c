extern int D_00139E04;

void SetHeapStartPoint(int point) {
    D_00139E04 = (point + 15) & ~15;
}
