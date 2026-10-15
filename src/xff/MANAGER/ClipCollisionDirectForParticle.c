extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern int CollisionPlaneJudgeCallbackParticle();

int ClipCollisionDirectForParticle(void *a, void *b, void *c, void *d)
{
    return ClipCollisionDirectCallBack(a, b, c, d, 0, 0, 0, CollisionPlaneJudgeCallbackParticle, 0);
}
