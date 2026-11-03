typedef struct { char pad0[0x178]; float time; char pad17C[0x2B0 - 0x17C]; char list[4]; } GcGlobal;
extern GcGlobal gcGlobalVar;
extern void *SCRGetFirstObj(void *);
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern void *isysGetThisSubThread(void);
extern int nico_returnPlayerRidingFlag(void *);
extern int _gameFlagChk(int);
extern void _gameFlagSet(int);
extern void spritedisplay(void *, int);
extern void scrRun(void);

void checkpoint_alert(void)
{
    void *obj = SCRGetFirstObj(gcGlobalVar.list);
    char *layout = GetLayoutClass(obj);
    char *chara = GetCharacterClass(obj);
    void *th = isysGetThisSubThread();
    unsigned long st = 0x200000;
    unsigned long mask = 0x1E00000;
    float start = 0.0f;

    while (!_gameFlagChk(0x108)) {
        if (!nico_returnPlayerRidingFlag(obj) && *(int *)(layout + 0x124)) {
            if ((*(unsigned long *)(chara + 0x690) & mask) == st) {
                start = gcGlobalVar.time;
            }
            if (_gameFlagChk(0x47)) {
                _gameFlagSet(0x108);
            }
        }
        if (start != 0.0f && gcGlobalVar.time - start < 2.0f) {
            spritedisplay(th, 1);
        } else {
            spritedisplay(th, 0);
        }
        scrRun();
    }
}
