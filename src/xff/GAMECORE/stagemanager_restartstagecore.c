extern int initstage();

int stagemanager_restartstagecore(int a, int b, int c, int d)
{
    return initstage(a, b, c, -1, d, 1);
}
