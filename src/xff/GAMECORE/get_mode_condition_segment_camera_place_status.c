extern int GAMEUTIL_get_segment_num_and_data(int *, char *);
extern char *GetLayoutClass(void *);
extern int *DldSysUndefSymbol;
extern char SH_SCameraModeConditionParamNORMAL[];

typedef struct {
    int pad0;
    void *obj;
    char pad8[4];
    char *mode;
} CondSrc;

int get_mode_condition_segment_camera_place_status(int *out, int type, CondSrc *s)
{
    int n = 0;
    char **p;
    char *sh;

    *out = 0;
    if (type == 1) {
        n = GAMEUTIL_get_segment_num_and_data(out, *(char **)(s->mode + 0x14) + 0x24);
    } else if (type == 2) {
        p = *(char ***)(GetLayoutClass(s->obj) + 0x1A8);
        if (p != 0) {
            if (*p != 0)
                n = GAMEUTIL_get_segment_num_and_data(out, *p + 0x24);
        }
    } else {
        sh = SH_SCameraModeConditionParamNORMAL;
        if (sh != 0 && (int *)sh != DldSysUndefSymbol) {
            *out = *(int *)(sh + 0xC);
            n = *(int *)(sh + 0x10);
        } else {
            __asm__ __volatile__("break 0");
        }
    }
    return n;
}
