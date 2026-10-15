typedef struct {
    int v[5];
} CollisionFinder;

void CopyCollisionFinder(CollisionFinder *dst, CollisionFinder *src)
{
    *dst = *src;
}
