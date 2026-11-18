typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern Vec4 ZeroPoint, XUnitVector, YUnitVector, ZUnitVector;
extern int D_0017B680;
extern void memset(void *, int, int);
extern void *get_cur_camera_target(int);
extern void *GAMEUTIL_get_boss_obj(void);
extern void *getBossCloudObj(void);
extern void *GAMEUTIL_get_obj_from_stagelayout_sheet(int);
extern int GAMEUTIL_get_boss_interest_position(Vec4 *, int);
extern void GAMEUTIL_get_local_quaternion(Vec4 *, void *);
extern char *GetLayoutClass(void *);
extern int GAMEUTIL_check_and_get_normalize_vector(Vec4 *, int, Vec4 *);
extern int CAM_get_camera_space_axisXY(int, Vec4 *, Vec4 *, float);
extern void GetQuaternionByAxisDirZY(Vec4 *, Vec4 *, Vec4 *);
extern int GAMEUTIL_get_node_quaternion_posi_by_id_extend(Vec4 *, Vec4 *, void *, int, int, int);
extern void GetStabYRotQuaternion(Vec4 *, Vec4 *);
extern void GAMEUTIL_get_xyz_axis_from_quaternion(Vec4 *, Vec4 *, Vec4 *, Vec4 *);

static inline void subXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void scaleXYZ(Vec4 *out, Vec4 *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

void CAM_get_base_space_posi_and_axisXYZ(Vec4 *posi, Vec4 *axisX, Vec4 *axisY, Vec4 *axisZ, int type, int sheet,
                                         void *objArg, int node, int arg8, int arg9, int camId, int stab)
{
    Vec4 q;
    Vec4 tgt;
    Vec4 ax;
    Vec4 dir;
    void *obj;
    int ok;
    int r;

    ok = 0;
    obj = 0;
    memset(&q, 0, 0x10);
    q.f[3] = 1.0f;
    if (type == 1) {
    } else if (type == 2 || type == 8) {
        obj = get_cur_camera_target(camId);
    } else if (type == 3) {
        obj = GAMEUTIL_get_boss_obj();
    } else if (type == 4) {
        obj = getBossCloudObj();
    } else if (type == 7) {
        void *b = GAMEUTIL_get_boss_obj();
        if (b != 0)
            obj = b;
        else
            obj = getBossCloudObj();
    } else if (type == 5) {
        obj = GAMEUTIL_get_obj_from_stagelayout_sheet(sheet);
    } else if (type == 6) {
        obj = objArg;
    } else {
        obj = 0;
    }
    if (obj != 0) {
        if (type == 7) {
            if (GAMEUTIL_get_boss_interest_position(posi, 1) == 1) {
                GAMEUTIL_get_local_quaternion(&q, obj);
                ok = 1;
            }
        } else if (type == 8) {
            r = GAMEUTIL_get_boss_interest_position(&tgt, 1);
            if (r == 1) {
                posi->q = (*(Vec4 **)(GetLayoutClass(obj) + 0x134))->q;
                subXYZ(&dir, posi, &tgt);
                if (GAMEUTIL_check_and_get_normalize_vector(&dir, 0, &dir) == r
                    && CAM_get_camera_space_axisXY(0, &ax, &dir, 0.0f) == r) {
                    GetQuaternionByAxisDirZY(&q, &dir, &ax);
                    ok = 1;
                }
            }
        } else {
            ok = GAMEUTIL_get_node_quaternion_posi_by_id_extend(&q, posi, obj, node, arg8, arg9) == 1;
        }
    }
    if (ok == 1) {
        if (stab == 1)
            GetStabYRotQuaternion(&q, &q);
        GAMEUTIL_get_xyz_axis_from_quaternion(axisX, axisY, axisZ, &q);
        if (type == 8 && D_0017B680 == 1)
            scaleXYZ(axisX, axisX, -1.0f);
    } else {
        posi->q = ZeroPoint.q;
        axisX->q = XUnitVector.q;
        axisY->q = YUnitVector.q;
        axisZ->q = ZUnitVector.q;
    }
}
