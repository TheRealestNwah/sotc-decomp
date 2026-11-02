extern int GetCollisionEdgePointerOtherSideDBData(void *data, void *edge);

static inline void CopyEdge(void *arg0, void *arg1)
{
    (*(int *)((char *)(arg0) + 0)) = (int) (*(int *)((char *)(arg1) + 0));
    (*(int *)((char *)(arg0) + 4)) = (int) (*(int *)((char *)(arg1) + 4));
    (*(int *)((char *)(arg0) + 8)) = (int) (*(int *)((char *)(arg1) + 8));
}

static inline void MakeEdge(char *pa0, char *pa1, int xa2)
{
    *(int *)(pa0 + 0x0) = *(int *)(pa1 + 0x0);
    *(int *)(pa0 + 0x4) = *(int *)(pa1 + 0x4);
    *(int *)(pa0 + 0x8) = xa2;
}

int GetCollisionEdgePointerOtherSideCollisionEdge(int *result, int *edge)
{
    int other[4];
    int candidateBuf[4];
    int *candidate;
    int back[4];
    int i;

    if (GetCollisionEdgePointerOtherSideDBData(other, edge) != 0) {
        candidate = candidateBuf;
        for (i = 0; i < 3; i++) {
            MakeEdge((char *)candidate, (char *)other, i);
            if (GetCollisionEdgePointerOtherSideDBData(back, candidate) != 0 &&
                back[0] == edge[0] && back[1] == edge[1]) {
                CopyEdge(result, candidate);
                return 1;
            }
        }
    }
    CopyEdge(result, edge);
    return 0;
}
