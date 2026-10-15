extern int func_00087DF0(int *group);
extern int isysDeleteAllGroup();

int scriptIntrAllDeleteJump(int a, int b, int c, int d)
{
    return isysDeleteAllGroup(a, (int)func_00087DF0, c, d);
}
