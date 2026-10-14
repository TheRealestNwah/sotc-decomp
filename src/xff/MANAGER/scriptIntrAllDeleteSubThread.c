extern char D_00087E18[];
extern int isysDeleteAllGroup();

int scriptIntrAllDeleteSubThread(int a, int b, int c, int d)
{
    return isysDeleteAllGroup(a, (int)D_00087E18, c, d);
}
