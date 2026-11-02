typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern void GetMotionNodeQuaternionPos(Vec4 *, Vec4 *, void *, int, int);
extern void GetMotionNodeQuaternionPosToolCoord(Vec4 *, Vec4 *, void *, int, int);

static inline int isExtendId(int id)
{
    int ret = 0;
    if (id > 0) {
        if (id & 0x10000) ret = 1;
    }
    return ret;
}

int GAMEUTIL_get_node_quaternion_posi_by_id_extend(Vec4 *quat, Vec4 *pos, void *object, int id, int toolCoord, int extToolCoord)
{
    if (object == 0) {
        return 0;
    }
    if (id == -1) {
        char *cc = GetCharacterClass(object);
        if (cc != 0) {
            quat->q = ((Vec4 *)(cc + 0x470))->q;
        } else {
            quat->q = (*(Vec4 **)(GetLayoutClass(object) + 0x13C))->q;
        }
        pos->q = (*(Vec4 **)(GetLayoutClass(object) + 0x134))->q;
    } else if (isExtendId(id) == 1) {
        if (extToolCoord == 1) {
            GetMotionNodeQuaternionPosToolCoord(quat, pos, object, id, 1);
        } else {
            GetMotionNodeQuaternionPos(quat, pos, object, id, 1);
        }
    } else if (toolCoord == 1) {
        GetMotionNodeQuaternionPosToolCoord(quat, pos, object, id, toolCoord);
    } else {
        GetMotionNodeQuaternionPos(quat, pos, object, id, 1);
    }
    return 1;
}
