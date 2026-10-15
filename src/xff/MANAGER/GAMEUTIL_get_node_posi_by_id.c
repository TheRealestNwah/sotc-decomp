typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
extern char *GetLayoutClass(void *);
extern void GetMotionNodePos(Vec4 *, void *, int, int);

int GAMEUTIL_get_node_posi_by_id(Vec4 *out, void *o, int id)
{
    if (o == 0)
        return 0;
    if (id == -1)
        out->q = (*(Vec4 **)(GetLayoutClass(o) + 0x134))->q;
    else
        GetMotionNodePos(out, o, id, 1);
    return 1;
}
