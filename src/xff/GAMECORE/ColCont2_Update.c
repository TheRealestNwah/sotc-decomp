typedef struct {
    long long lo, hi;
} V128;

typedef struct {
    long long attr;
    long long prevAttr;
    int linked;
    char link[0xC];
    int hasLink;
    float timer;
} ColCont2;

extern V128 RO_0017D530;
extern char gcGlobalVar[];
extern int nico_GetPlayerCharacterRidingHorseObject(int);
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);
extern long long GetGeometryPointerCharColAttr(void *);
extern int GetGeometryPointerObject(void *);
extern int SCRGetFirstObj(void *);
extern int ClipCollisionDirect(void *, void *, void *, void *);
extern void DeleteTwoWayLink(void *);
extern void AddTwoWayLinkNext(void *, void *);

void ColCont2_Update(ColCont2 *c, int obj0)
{
    float pos[4] __attribute__((aligned(16)));
    float hit[0x14] __attribute__((aligned(16)));
    int horse = nico_GetPlayerCharacterRidingHorseObject(obj0);
    int obj = obj0;
    char *lay;
    char *chr;

    if (horse)
        obj = horse;
    lay = GetLayoutClass(obj);
    chr = GetCharacterClass(obj);

    if (*(int *)(lay + 0x124) != 0) {
        long long a = GetGeometryPointerCharColAttr(lay + 0xC0);
        int o = GetGeometryPointerObject(lay + 0xC0);

        if (obj == horse || o != SCRGetFirstObj(gcGlobalVar + 0x2B4)) {
            c->attr = a;
            c->prevAttr = a;
            if (c->hasLink) {
                c->linked = 0;
                c->hasLink = 0;
                DeleteTwoWayLink(c->link);
            }
            c->linked = GetGeometryPointerObject(GetLayoutClass(obj) + 0xC0);
            if (c->linked) {
                AddTwoWayLinkNext(GetLayoutClass(c->linked) + 0x118, c->link);
                {
                    register int one __asm__("$3") = 1;
                    c->hasLink = one;
                }
            }
        }
    } else {
        if (chr[0x362] != 0) {
            register V128 *ro __asm__("$2") = &RO_0017D530;
            __asm__ __volatile__("ld $3, 0x8(%0)
"
                                 "ld $4, 0x0(%0)
"
                                 "sd $3, 0x8(%1)
"
                                 "sd $4, 0x0(%1)
"
                                 "lw %0, 0x134(%2)
"
                                 "lqc2 vf5, 0x0(%1)
"
                                 "lqc2 vf6, 0x0(%0)
"
                                 "vadd.xyz vf5, vf5, vf6
"
                                 "sqc2 vf5, 0x0(%1)
"
                                 : "+r"(ro) : "r"(pos), "r"(lay) : "$3", "$4", "memory");
            if (ClipCollisionDirect(hit, *(char **)(lay + 0x134), pos, gcGlobalVar + 0x230) != 0)
                c->attr = GetGeometryPointerCharColAttr(hit);
            else
                c->attr = 0;
            c->prevAttr = c->attr;
            c->linked = 0;
            if (c->hasLink) {
                c->hasLink = 0;
                DeleteTwoWayLink(c->link);
            }
        }
    }
    if ((int)(c->attr & 1) != 0)
        c->timer = c->timer + *(float *)(gcGlobalVar + 0x180);
    else
        c->timer = 0.0f;
}
