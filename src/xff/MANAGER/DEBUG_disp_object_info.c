/* Parked: ~200 diffs (222 words vs 211). Debug overlay for a layout/character object: prints status lines then the animation names. Registers rotate (obj s5, ctx s4 in the original); the animation-name branch pair shares a tail in the original. */
#ifdef NONMATCHING
extern char *GetLayoutClass(int);
extern char *GetCharacterClass(int);
extern void iosSetKPrintfLocateContext(int, float, float);
extern void kprintfContext(int, const char *, ...);
extern double fptodp(float);
extern int GetCharacterClassCurAnimationTotalFrame(char *);
extern float GetCharacterClassCurAnimationCurFrame(char *);
extern const char *DebugGetAnimObjName(char *);
extern const char *DEBUG_get_cur_using_anb_file_name(int, const char *);
extern char RO_00114F50[];
extern char RO_00114FC0[];
extern char RO_00114FC8[];
extern char RO_00114FE0[];
extern char RO_00114FF0[];
extern char RO_00114FF8[];
extern char RO_00115000[];
extern char RO_00115010[];
extern char RO_00115020[];
extern char RO_00115030[];
extern char RO_00115040[];
extern char RO_00115060[];
extern char RO_00115068[];

float DEBUG_disp_object_info(int obj, int ctx, float x, float y, float dy)
{
    char *layout;
    char *chara;
    int shown;
    int n;
    char *e;
    float *pos;
    char *c2;

    if (obj != 0) {
        layout = GetLayoutClass(obj);
        if (layout != 0) {
            chara = GetCharacterClass(obj);
            iosSetKPrintfLocateContext(ctx, x, y);
            y += dy;
            kprintfContext(ctx, RO_00114FC0, *(int *)(layout + 0x130));
            iosSetKPrintfLocateContext(ctx, x, y);
            y += dy;
            pos = *(float **)(layout + 0x134);
            kprintfContext(ctx, RO_00114FC8, fptodp(pos[0]), fptodp(pos[1]), fptodp(pos[2]));
            if (chara != 0) {
                iosSetKPrintfLocateContext(ctx, x, y);
                c2 = GetCharacterClass(obj);
                kprintfContext(ctx, RO_00114FE0,
                               c2 ? *(char **)(*(char **)(c2 + 0x750) + 8) : RO_00114F50);
                y += dy;
                iosSetKPrintfLocateContext(ctx, x, y);
                c2 = GetCharacterClass(obj);
                if (c2 != 0) {
                    char *p = *(char **)(c2 + 0x578);
                    if (p != 0) {
                        kprintfContext(ctx, RO_00114FF0, *(char **)p);
                        goto after;
                    }
                }
                kprintfContext(ctx, RO_00114FF0, RO_00114F50);
            after:
                y += dy;
                iosSetKPrintfLocateContext(ctx, x, y);
                y += dy;
                kprintfContext(ctx, RO_00114FF8, DEBUG_get_cur_using_anb_file_name(obj, RO_00115000));
                iosSetKPrintfLocateContext(ctx, x, y);
                y += dy;
                kprintfContext(ctx, RO_00115010, *(float *)(chara + 0x720));
                iosSetKPrintfLocateContext(ctx, x, y);
                y += dy;
                kprintfContext(ctx, RO_00115020, GetCharacterClassCurAnimationTotalFrame(chara));
                iosSetKPrintfLocateContext(ctx, x, y);
                y += dy;
                kprintfContext(ctx, RO_00115030, fptodp(GetCharacterClassCurAnimationCurFrame(chara)));
                n = *(int *)(chara + 0x3FC);
                e = *(char **)(chara + 0x30C);
                x -= 100.0f;
                shown = 0;
                if (n > 0) {
                    do {
                        if (*(int *)(e + 0x44) != -2) {
                            if (shown == 0) {
                                iosSetKPrintfLocateContext(ctx, x, y);
                                y += dy;
                                kprintfContext(ctx, RO_00115040);
                            }
                            iosSetKPrintfLocateContext(ctx, x, y);
                            y += dy;
                            shown++;
                            kprintfContext(ctx, RO_00115060, DebugGetAnimObjName(*(char **)(e + 4) + 0x50));
                            n--;
                        } else {
                            n--;
                        }
                        e += 0x80;
                    } while (n != 0);
                }
                if (shown == 0) {
                    iosSetKPrintfLocateContext(ctx, x, y);
                    y += dy;
                    kprintfContext(ctx, RO_00115068);
                }
            }
        }
    }
    return y;
}
#endif
