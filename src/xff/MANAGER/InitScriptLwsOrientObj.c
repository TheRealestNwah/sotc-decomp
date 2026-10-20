extern int InitLwsOrientObj(unsigned char *, int *);
extern void initScriptObj(void *, void *, int);
extern void InitChildGroupManagerObj(unsigned char *);
void InitScriptLwsOrientObj(unsigned char *obj, int *def)
{
    unsigned char *cls;
    int *buffer;
    int *cb;
    InitLwsOrientObj(obj, def);
    initScriptObj(obj, def + 77, *(int *)obj);
    InitChildGroupManagerObj(obj);
    cls = obj[8] != 22 ? 0 : obj + 0x20;
    cb = (int *)(cls + 0x120C);
    buffer = (int *)(cls + 0x1204);
    buffer[1] = 0;
    buffer[0] = 0;
    *(int *)(cls + 0x1214) = 0;
    cb[0] = 0;
    cb[1] = 0;
}