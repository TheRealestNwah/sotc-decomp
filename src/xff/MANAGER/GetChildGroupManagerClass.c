extern int GetScrLwsOriClass();
extern int GetScriptAnimationClass();

int GetChildGroupManagerClass(void *arg0)
{
    unsigned char temp_v1;

    temp_v1 = (*(unsigned char *)((char *)(arg0) + 8));
    switch (temp_v1) {                              /* irregular */
    case 13:
        return GetScriptAnimationClass() + 0x320;
    case 22:
        return GetScrLwsOriClass() + 0x11F0;
    default:
        return 0;
    }
}
