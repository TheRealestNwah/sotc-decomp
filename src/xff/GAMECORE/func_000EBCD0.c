extern void CAM_destructor_target(void *);
extern void ReleaseCollisionFinder(void *);

static void func_000EBCD0(char *cam)
{
    CAM_destructor_target(cam + 0x23C);
    ReleaseCollisionFinder(cam + 0x1800);
    ReleaseCollisionFinder(cam + 0x1814);
}
