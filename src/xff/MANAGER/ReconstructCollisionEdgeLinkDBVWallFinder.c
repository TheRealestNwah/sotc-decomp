typedef struct EdgeLink {
    int pad[3];
    void *prev;
    void *next;
} EdgeLink;

typedef struct {
    char pad0[0x1C];
    int (*collect)(void *, int *);
    int count;
    EdgeLink *links;
} EdgeLinkFinder;

extern void GetCollisionEdgePointerVertexPoint3(void **, EdgeLink *);
extern void GetCollisionEdgePointerVertexPoint(void **, EdgeLink *);

static inline int collectVWallLinks(EdgeLinkFinder *finder, int *size)
{
    int count = 0;
    int m = size[0];
    if (size[1] < m) {
        m = size[1];
    }
    if (m != 0) {
        EdgeLink *a;
        EdgeLink *links;
        int i;
        if (finder->collect != 0) {
        count = finder->collect(finder, size);
        a = finder->links;
        links = a;
        for (i = count - 1; i != -1; i--, a++) {
            void *va[4];
            void *vb[4];
            EdgeLink *b;
            int j;
            GetCollisionEdgePointerVertexPoint3(va, a);
            a->next = 0;
            a->prev = 0;
            b = links;
            for (j = count - 1; j != -1; j--, b++) {
                if (a == b) {
                    continue;
                }
                GetCollisionEdgePointerVertexPoint(vb, b);
                if (va[0] == vb[0] || va[0] == vb[1]) {
                    a->prev = b;
                }
                if (va[1] == vb[0] || va[1] == vb[1]) {
                    a->next = b;
                }
            }
        }
        }
    }
    finder->count = count;
    return count;
}

int ReconstructCollisionEdgeLinkDBVWallFinder(EdgeLinkFinder *finder, int *size)
{
    if (finder->count != 0) {
        return collectVWallLinks(finder, size);
    }
    return 0;
}
