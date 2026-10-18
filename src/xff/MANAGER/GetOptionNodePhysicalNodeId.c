extern int GetMotionVersion(void *);
extern int GetMotionNbOptionNodes(void *);
extern int GetMotionOptionNodePhysicalId(void *, int);
int GetOptionNodePhysicalNodeId(void *options, void *motion, int node)
{
    int result = -1;
    if (*(int *)options <= 0 || GetMotionVersion(motion) < 5) {
        if (node < GetMotionNbOptionNodes(motion))
            result = node;
    } else {
        result = GetMotionOptionNodePhysicalId(motion, node);
    }
    return result;
}
