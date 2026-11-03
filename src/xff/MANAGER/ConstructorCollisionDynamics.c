#ifdef NONMATCHING /* the two 1.0f stores to the local are scheduled after the struct copy in the original */
typedef struct {
    int unk0[3];
    float unkC;
    int unk10;
    float unk14;
    int unk18[6];
} __attribute__((aligned(8))) CollisionDynamics;

extern void *memset(void *, int, unsigned int);

void ConstructorCollisionDynamics(CollisionDynamics *out)
{
    CollisionDynamics tmp;
    memset(&tmp, 0, sizeof(tmp));
    tmp.unkC = 1.0f;
    tmp.unk14 = 1.0f;
    *out = tmp;
}
#endif
