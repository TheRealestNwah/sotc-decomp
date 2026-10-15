typedef struct { char pad[0x10]; int v; } Info;
extern Info D_0017B8D0;
extern void initScriptObj(unsigned char *, Info *);

void initEventScriptObj(unsigned char *o, int *a)
{
    unsigned char *s;
    D_0017B8D0.v = a[0];
    initScriptObj(o, &D_0017B8D0);
    s = o[8] != 0x20 ? 0 : o + 0x20;
    *(int *)(s + 0x70) = a[1];
    *(int *)(s + 0x74) = a[2];
}
