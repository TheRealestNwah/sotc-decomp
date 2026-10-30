typedef unsigned int u_long128 __attribute__((mode(TI)));

extern int getNearPoint(char *, int, int *, int *, void *, void *, int, int);
extern u_long128 *getPointDataByAreaIdx(char *, int, int);
extern void execPointListSort(char *, void *, void *);

#define W(type, o) (*(type *)(pw + (o)))

static void func_000F5D30(char *pw)
{
    int area = -1;
    int point = -1;

    W(int, 0x408) = 0;
    W(int, 0x380) = 0;
    if (getNearPoint(pw, 1, &area, &point, pw + 0x434, pw, 0, 0)) {
        W(int, 0x88) = area;
        W(int, 0x8C) = point;
        W(int, 0x40C) = 1;
        W(u_long128, 0x60) = W(u_long128, 0x70) = *getPointDataByAreaIdx(pw, area, point);
        execPointListSort(pw, pw + 0x2038, pw + 0x70);
        if (!getNearPoint(pw, 0, (int *)(pw + 0x80), (int *)(pw + 0x84), pw + 0x2038, pw + 0x70, !W(int, 0x39C), 1)) {
            W(int, 0x80) = area;
            W(int, 0x84) = point;
        }
    } else {
        W(int, 0x80) = -1;
        W(int, 0x84) = -1;
        W(int, 0x40C) = 0;
    }
}
