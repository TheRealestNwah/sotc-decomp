typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    float x, y, z, w;
} __attribute__((aligned(8))) Float4;

typedef struct {
    short x, y, z;
} Short3;

typedef struct {
    float baseX, scaleX;
    float baseY, scaleY;
    float baseZ, scaleZ;
    Short3 *keys;
} PackedKeys;

typedef struct {
    short version;
    char pad2[4];
    unsigned short flags;
    char pad8[4];
    void *data;
} MotionTrack;

static void func_00031DB8(Vec4 *out, MotionTrack *track, int frame)
{
    if (track->version >= 6) {
        int kind = track->flags & 0xF;
        void *data = track->data;

        out->f[3] = 1.0f;
        if (kind != 0) {
            if (kind != 2) {
                Vec3 *v = (Vec3 *)data + frame;

                out->f[0] = v->x;
                out->f[1] = v->y;
                out->f[2] = v->z;
            } else {
                PackedKeys *p = data;
                Short3 *k = &p->keys[frame];

                out->f[0] = (float)k->x * p->scaleX * (1.0f / 32767.0f) + p->baseX;
                out->f[1] = (float)k->y * p->scaleY * (1.0f / 32767.0f) + p->baseY;
                out->f[2] = (float)k->z * p->scaleZ * (1.0f / 32767.0f) + p->baseZ;
            }
        } else {
            Vec3 *v = data;

            out->f[0] = v->x;
            out->f[1] = v->y;
            out->f[2] = v->z;
        }
    } else {
        Vec3 *base = track->data;
        union {
            Float4 s;
            s128 q;
        } t;
        Float4 f;

        f.x = base[frame].x;
        f.y = base[frame].y;
        f.z = base[frame].z;
        f.w = 1.0f;
        t.s = f;
        out->q = t.q;
    }
}
