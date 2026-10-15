extern char symbolDefModuleGroup[];
extern char needResolveModuleGroup[];
extern void _isysDeleteGroup(void *, void *, int);

void isysRemoveModuleObjGroup(char *m)
{
    char *x = *(char **)(m + 0x1C);
    if (*(int *)(x + 0x24) != 0) {
        _isysDeleteGroup(m, symbolDefModuleGroup, 0);
        x = *(char **)(m + 0x1C);
    }
    if (*(int *)(x + 0x1C) != 0)
        _isysDeleteGroup(m, needResolveModuleGroup, 0);
}
