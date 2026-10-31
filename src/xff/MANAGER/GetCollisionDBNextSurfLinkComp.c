typedef struct { char pad0[0x14]; char *links; char pad18[0x90 - 0x18]; } SurfGroup;
typedef struct { char pad0[8]; SurfGroup *groups; } CollisionData;
typedef struct { char pad0[0x20]; CollisionData *data; } CollisionDB;
typedef struct { void *obj; unsigned int value; } SurfLink;
extern char *GetLayoutClass(void *);

void *GetCollisionDBNextSurfLinkComp(SurfLink *link)
{
    int index = link->value & 0xFFFFFF;
    int group = (link->value >> 24) & 0x7F;
    CollisionDB *db = *(CollisionDB **)(GetLayoutClass(link->obj) + 0x184);
    SurfGroup *g = &db->data->groups[group];
    return g->links + index * 0x14 + 8;
}
