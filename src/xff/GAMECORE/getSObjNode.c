typedef struct { int id; int sub; char pad[0x58]; } SObjNode;
typedef struct { char pad[0x250]; SObjNode node[20]; int n; char pad2[0xC]; } SObjSet;
extern SObjSet B_0019B870, B_0019C250;

SObjNode *getSObjNode(int id)
{
    int j, i;
    for (j = 0; j < 2; j++) {
        SObjSet *s = j == 0 ? &B_0019B870 : &B_0019C250;
        for (i = 0; i < s->n; i++) {
            if (id == s->node[i].id)
                return &s->node[i];
        }
    }
    return 0;
}
