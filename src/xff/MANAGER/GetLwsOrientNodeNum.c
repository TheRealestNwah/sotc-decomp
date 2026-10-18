typedef struct { int type; int words[2]; } LwsOrientNode;
typedef struct { char pad[0x10]; LwsOrientNode *nodes; int count; } LwsOrient;
int GetLwsOrientNodeNum(LwsOrient *orient)
{
    int count = orient->count;
    int found = 0;
    int i;
    for (i = 0; i < count; ++i) {
        int offset = ((i << 1) + i) << 2;
        LwsOrientNode *node = (LwsOrientNode *)((char *)orient->nodes + offset);
        if (node->type == 14) {
            found = 1;
            break;
        }
    }
    return count - found;
}
