extern int D_00087E18(int *group);
extern int isysDeleteAllGroup();

int scriptIntrAllDeleteSubThread(int a, int b, int c, int d)
{
    return isysDeleteAllGroup(a, (int)D_00087E18, c, d);
}
