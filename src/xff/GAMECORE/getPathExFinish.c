typedef struct {
    char pad0[0x3CA4];
    int f3CA4;
    int f3CA8;
    int f3CAC;
} PathEx;

int getPathExFinish(PathEx *p, int kind)
{
    switch (kind) {
    case 2:
    case 3:
    case 4:
        return p->f3CA8;
    case 5:
    case 6:
    case 7:
    case 8:
        return p->f3CA4;
    case 9:
        return p->f3CAC;
    }
    return 0;
}
