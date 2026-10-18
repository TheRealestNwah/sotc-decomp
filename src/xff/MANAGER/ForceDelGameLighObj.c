extern char *GetLightColMan(unsigned char *);
extern int isysAddGroupWithLinkParam(void *, void *, int, int);
extern void _isysDeleteGroup(void *, void *, int);

void ForceDelGameLighObj(unsigned char *o)
{
    char *m = GetLightColMan(o);
    unsigned char *l = o[8] != 0x1A ? 0 : o + 0x20;
    *(int *)(l + 0x2C) = 0;
    isysAddGroupWithLinkParam(o, m + 0x524, 0, 0);
    _isysDeleteGroup(o, m + 0x528, 0);
}
