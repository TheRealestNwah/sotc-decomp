/* Parked draft: main script loop of the tail of a boss (gextail). Per frame: finds the geometry
   under the layout, resets the script control and advances a small state machine at +0x24/+0x28
   (1: wait for the owner's sub-object to be armed, then 2; 2: until the tail-death control mode or
   func_000B4690 reports done, then 3), runs func_000B48A8, and by state keeps the tail points
   (+0x50/+0x60/+0x70) in sync with the layout (state 1 also forwards bow/sound-bow damage to the
   owner). When the layout falls below y = -1000 it disables layout access and idles forever.
   32 diffs left: the armed check computes sltu where the Original branches, layout/owner sit in
   swapped s-registers, and gcc reuses the +0x13C pointer load the Original reloads after the store. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

extern int ControlMode_GEX_TAIL_DEATH;
extern int AI_CheckDamage_Bow(int, int);
extern int AI_CheckDamage_SoundBow(int, int);
extern void AI_OptFloatFrameSample(int, int);
extern void CharaCtrlResetAllScriptCtrlStatus(int);
extern char *GetCharacterClass(int);
extern int GetGeometryPointerObject(char *);
extern char *GetLayoutClass(int);
extern char *GetScriptCharacterClass(int);
extern void SetLayoutObjAccessSwitch(int, int);
extern int func_000B4690(char *, char *, char *);
extern void func_000B48A8(char *);
extern int isysGetThisSubThread(void);
extern void scrRunM(int);

static inline char isArmed(int owner)
{
    char *cc = *(char **)(GetScriptCharacterClass(owner) + 0x1200);
    int *sub;

    if (cc == 0)
        return 0;
    sub = *(int **)(cc + 0x10);
    if (sub == 0)
        return 0;
    if (*sub != 0)
        return 1;
    return 0;
}

static inline int isDone(char *p, char *pos, char *aux)
{
    if (*(int *)(GetCharacterClass(isysGetThisSubThread()) + 0x750) == ControlMode_GEX_TAIL_DEATH)
        return 1;
    return (*(int *)(p + 0x2C) = func_000B4690(p, pos, aux)) != 0;
}

static void func_000B4A80(char *p)
{
    int self = isysGetThisSubThread();
    char *pos = p + 0x30;
    char *aux = p + 0x40;
    int frame = (int)(p + 0x14);

    for (;;) {
        char *layout;
        int next;
        int t;

        *(int *)(p + 0x20) = GetGeometryPointerObject(GetLayoutClass(self) + 0xC0);
        CharaCtrlResetAllScriptCtrlStatus(isysGetThisSubThread());
        switch (*(int *)(p + 0x24)) {
        case 1: {
            int owner = *(int *)(p + 0x20);
            int ok = 1;

            if (owner != 0)
                ok = isArmed(owner);
            if (ok != 0)
                *(int *)(p + 0x28) = 2;
            break;
        }
        case 2:
            if (isDone(p, pos, aux))
                *(int *)(p + 0x28) = 3;
            break;
        case 0:
            break;
        }
        func_000B48A8(p);
        layout = GetLayoutClass(isysGetThisSubThread());
        next = *(int *)(p + 0x28);
        switch (next) {
        case 1: {
            int owner = *(int *)(p + 0x20);
            int th = isysGetThisSubThread();

            if ((AI_CheckDamage_Bow(0, th) != 0 || AI_CheckDamage_SoundBow(0, th) != 0) && owner != 0) {
                char *cc = *(char **)(GetScriptCharacterClass(owner) + 0x1200);
                if (cc != 0) {
                    int *sub = *(int **)(cc + 0x10);
                    if (sub != 0)
                        sub[1] = next;
                }
            }
            *(s128 *)(p + 0x60) = **(s128 **)(layout + 0x13C);
            *(s128 *)(p + 0x70) = **(s128 **)(layout + 0x13C);
            *(s128 *)(p + 0x50) = **(s128 **)(GetLayoutClass(*(int *)(p + 0x20)) + 0x134);
            break;
        }
        case 2:
            *(s128 *)(p + 0x50) = **(s128 **)(layout + 0x134);
            break;
        case 3:
            if (*(int *)(p + 0x2C) != 0)
                **(s128 **)(layout + 0x134) = *(s128 *)(p + 0x30);
            **(s128 **)(layout + 0x13C) = *(s128 *)(p + 0x60);
            break;
        }
        AI_OptFloatFrameSample(self, frame);
        *(int *)(p + 0x24) = *(int *)(p + 0x28);
        t = isysGetThisSubThread();
        if (!(*(float *)(*(char **)(GetLayoutClass(t) + 0x134) + 4) < -1000.0f)) {
            scrRunM(1);
            continue;
        }
        SetLayoutObjAccessSwitch(t, 0);
        for (;;)
            scrRunM(1);
    }
}
#endif
