extern int getAnimObjResource(int);

void InitGazeAddChannelDef(int *g, int res)
{
    g[2] = getAnimObjResource(res);
    g[3] = res;
    g[1] = 0;
    g[0] = 0;
}
