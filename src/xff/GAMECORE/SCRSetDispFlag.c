extern void SetLayoutObjAccessSwitch(void *obj, int on);
extern void SetScriptAnimationObjAccessSwitch(void *obj, int on);

/* Called through an inline helper: the original makes a normal call here,
   not a tail call like the layout case. */
static inline void setScriptSwitch(unsigned char *obj, int on)
{
    SetScriptAnimationObjAccessSwitch(obj, on);
}

void SCRSetDispFlag(unsigned char *obj, int on)
{
    switch (obj[8]) {
    case 9:
    case 10:
    case 11:
        SetLayoutObjAccessSwitch(obj, on);
        break;
    case 13:
        setScriptSwitch(obj, on);
        break;
    /* Present in the original's case tree, with nothing to do. */
    case 14:
        break;
    }
}
