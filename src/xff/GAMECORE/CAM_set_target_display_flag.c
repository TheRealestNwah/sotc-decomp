typedef struct { char pad[0x260]; unsigned long lo : 10; unsigned long hide : 1; unsigned long hi : 53; } Layout;
extern char *GetLayoutClass(int);

void CAM_set_target_display_flag(int *t, int on)
{
    if (*t != 0) {
        Layout *l = *(Layout **)(GetLayoutClass(*t) + 0x144);
        l->hide = on == 0;
    }
}
