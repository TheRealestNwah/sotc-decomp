typedef struct Link {
    struct Link *next;
    struct Link *prev;
} Link;

typedef struct {
    Link link;
    int data;
} FinderNode;

typedef struct {
    FinderNode *node;
    int data;
} Finder;

typedef struct {
    char pad[0xC];
    Finder *finders;
    FinderNode *nodes;
} CollisionFinders;

extern int DeleteTwoWayLink(Link *);

int DeleteCollisionFinder(CollisionFinders *c, int index)
{
    c->finders[index].node = 0;
    return DeleteTwoWayLink(&c->nodes[index].link);
}
