typedef struct { int a; int stage; int b; } Seg;
extern void stagemanager_unloadstage(int);

void deleteSeamlessCommonLayout(char *s)
{
    int i = *(int *)(s + 0xC);
    Seg *p = *(Seg **)(s + 0x10);
    while (--i != -1) {
        if (p->stage >= 0) {
            stagemanager_unloadstage(p->stage);
            p->stage = -1;
        }
        p++;
    }
}
