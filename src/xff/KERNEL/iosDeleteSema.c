extern void LoaderSysDeleteExternalSemaList(int sema);
extern int DeleteSema(int sema);

int iosDeleteSema(int sema)
{
    LoaderSysDeleteExternalSemaList(sema);
    return DeleteSema(sema);
}
