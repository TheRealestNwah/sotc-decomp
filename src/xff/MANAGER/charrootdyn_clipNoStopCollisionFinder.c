extern int func_00064660();
extern int ClipCollisionFinderCallBack();

int charrootdyn_clipNoStopCollisionFinder(int a, int b, int c, int d)
{
    return ClipCollisionFinderCallBack(a, b, c, d, func_00064660, 0);
}
