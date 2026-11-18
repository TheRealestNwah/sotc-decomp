typedef struct {
    char pad0[0x20];
    float pos[4];
    int arg;
    void *data;
    unsigned int *file;
    unsigned int *hdr[8];
} ISysPathObj;

extern unsigned int *getPointDataHeader(unsigned int *);
extern unsigned int *getLineDataHeader(unsigned int *);
extern unsigned int *getRootDataHeader(unsigned int *);
extern unsigned int *getGoalDataHeader(unsigned int *);
extern unsigned int *getSubDataHeader(unsigned int *);
extern unsigned int *getInterestDataHeader(unsigned int *);
extern unsigned int *getDeadDataHeader(unsigned int *);
extern unsigned int *getLayoutDataHeader(unsigned int *);
extern float *getPointData(unsigned int *, unsigned int);
extern float *getRootPointData(unsigned int *, unsigned int);
extern float *getGoalPointData(unsigned int *, unsigned int);
extern float *getSubPointData(unsigned int *, unsigned int);
extern float *getInterestPointData(unsigned int *, unsigned int);
extern float *getDeadPointData(unsigned int *, unsigned int);
extern float *getLayoutPointData(unsigned int *, unsigned int);

static inline void vecAddXYZ(float *d, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vadd.xyz vf5, vf5, vf6
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

int initISysPathObj(ISysPathObj *obj, union { float *p; int i; } *ofs, char *data, int arg)
{
    unsigned int i;
    float *p;

    if (ofs[0].p != 0) {
        obj->pos[0] = ofs[0].p[0];
        obj->pos[1] = ofs[0].p[1];
        obj->pos[2] = ofs[0].p[2];
        obj->pos[3] = 1.0f;
    } else {
        obj->pos[0] = 0.0f;
        obj->pos[3] = 1.0f;
        obj->pos[1] = 0.0f;
        obj->pos[2] = 0.0f;
    }
    obj->arg = arg;
    if (ofs[1].p != 0) {
        obj->pos[0] += ofs[1].p[0];
        obj->pos[1] += ofs[1].p[1];
        obj->pos[2] += ofs[1].p[2];
    }
    obj->data = data;
    obj->file = *(unsigned int **)(data + 8);
    if (obj->file != 0 && *obj->file == 0x68746171) {
        obj->hdr[0] = getPointDataHeader(obj->file);
        obj->hdr[1] = getLineDataHeader(obj->file);
        obj->hdr[2] = getRootDataHeader(obj->file);
        obj->hdr[3] = getGoalDataHeader(obj->file);
        obj->hdr[4] = getSubDataHeader(obj->file);
        obj->hdr[5] = getInterestDataHeader(obj->file);
        obj->hdr[6] = getDeadDataHeader(obj->file);
        obj->hdr[7] = getLayoutDataHeader(obj->file);
        if (ofs[0].p != 0) {
            if (obj->hdr[0] != 0) {
                for (i = 0; i < *obj->hdr[0]; i++) {
                    p = getPointData(obj->hdr[0], i);
                    vecAddXYZ(p, p, obj->pos);
                }
            }
            if (obj->hdr[2] != 0) {
                for (i = 0; i < *obj->hdr[2]; i++) {
                    p = getRootPointData(obj->hdr[2], i);
                    vecAddXYZ(p, p, obj->pos);
                }
            }
            if (obj->hdr[3] != 0) {
                for (i = 0; i < *obj->hdr[3]; i++) {
                    p = getGoalPointData(obj->hdr[3], i);
                    vecAddXYZ(p, p, obj->pos);
                }
            }
            if (obj->hdr[4] != 0) {
                for (i = 0; i < *obj->hdr[4]; i++) {
                    p = getSubPointData(obj->hdr[4], i);
                    vecAddXYZ(p, p, obj->pos);
                }
            }
            if (obj->hdr[5] != 0) {
                for (i = 0; i < *obj->hdr[5]; i++) {
                    p = getInterestPointData(obj->hdr[5], i);
                    vecAddXYZ(p, p, obj->pos);
                }
            }
            if (obj->hdr[6] != 0) {
                for (i = 0; i < *obj->hdr[6]; i++) {
                    p = getDeadPointData(obj->hdr[6], i);
                    vecAddXYZ(p, p, obj->pos);
                }
            }
            if (obj->hdr[7] != 0) {
                for (i = 0; i < *obj->hdr[7]; i++) {
                    p = getLayoutPointData(obj->hdr[7], i);
                    vecAddXYZ(p, p, obj->pos);
                }
            }
        }
        return 1;
    }
    return 0;
}
