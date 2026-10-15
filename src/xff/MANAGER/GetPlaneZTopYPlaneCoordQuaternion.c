extern void GetPlaneTopDir(float *, void *);
extern void GetQuaternionByAxisDirZY(void *, float *, void *);

void GetPlaneZTopYPlaneCoordQuaternion(void *q, void *plane)
{
    float dir[4] __attribute__((aligned(16)));
    GetPlaneTopDir(dir, plane);
    GetQuaternionByAxisDirZY(q, dir, plane);
}
