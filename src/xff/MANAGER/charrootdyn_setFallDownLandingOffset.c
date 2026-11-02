typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

typedef struct CharRootDyn {
    char pad0[0x134];
    void *parent;
    char pad138[0xA80 - 0x138];
    Vector3 fallDownLandingOffset;
} CharRootDyn;

extern void charrootdyn_getLocalOffsetFromParentGPwithGPCoordinate(float *, void *, void *);

static inline void CopyVector3(Vector3 *dst, float *src)
{
    dst->x = src[0];
    dst->y = src[1];
    dst->z = src[2];
}

void charrootdyn_setFallDownLandingOffset(CharRootDyn *dyn, void *pos)
{
    float offset[4];

    charrootdyn_getLocalOffsetFromParentGPwithGPCoordinate(offset, pos, dyn->parent);
    CopyVector3(&dyn->fallDownLandingOffset, offset);
}
