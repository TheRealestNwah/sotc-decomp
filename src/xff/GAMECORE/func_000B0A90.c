#ifdef NONMATCHING
/* ~113 diffs, same length (157 words). Draft from the asm: wander controller for a creature actor: sets o[0x1A0] = 0x29; when the target is outside the (F4<30, |F8|<34) window and FC < 0 it draws two randoms and picks a turn state (6/7 via the thread-held actor's radius at +8 and 2x radius, else 5) into o+0x19C and, for states 6/7, tail-calls func_000B0160(o, o+0xD0, 12, 0.25f); otherwise it picks with fixed 0.2/0.4 thresholds and sets o[0x204] = +-0.25 * o[0x1A4] (state 5 zeroes it), then CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRGoL/R[1]) and SCRCharaTurnDirectInput(th, o[0x204]). Remaining difference: the Original keeps o in s1 and th in s0 (ours swaps them) and builds the first condition with v0 in the branch delay slots instead of a flag; permuter (6 workers, 10 min) only reached 3710. */
extern void *isysGetThisSubThread(void);
extern float iosGetRandom(void);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void SCRCharaTurnDirectInput(void *, float);
extern int *ScriptCtrlDef_SCRGoR;
extern int *ScriptCtrlDef_SCRGoL;
extern void func_000B0160(char *, char *, int, float);

static void func_000B0A90(char *o)
{
    void *th = isysGetThisSubThread();
    int hit;
    float r1, r2;
    int v;

    *(int *)(o + 0x1A0) = 0x29;
    hit = *(float *)(o + 0xF4) < *(float *)(o + 0x30) && *(float *)(o + 0xF8) < *(float *)(o + 0x34) && -*(float *)(o + 0x34) < *(float *)(o + 0xF8);
    if (!hit && *(float *)(o + 0xFC) < 0.0f) {
        float h;
        r1 = iosGetRandom();
        th = *(void **)(o + 0x40);
        h = *(float *)((char *)th + 8);
        r2 = iosGetRandom();
        if (*(float *)(o + 0x12C) < *(float *)(o + 0x130)) {
            if (r2 < h)
                v = 6;
            else if (r2 < h + h)
                v = 7;
            else
                v = 5;
            *(int *)(o + 0x19C) = v;
            *(float *)(o + 0x12C) = r1;
            *(int *)(o + 0x130) = 0;
        }
        v = *(int *)(o + 0x19C);
        if ((unsigned)(v - 6) < 2)
            func_000B0160(o, o + 0xD0, 12, 0.25f);
    } else {
        r1 = iosGetRandom() * 0.5f;
        r2 = iosGetRandom();
        if (*(float *)(o + 0x12C) < *(float *)(o + 0x130)) {
            if (r2 < 0.2f)
                v = 6;
            else if (r2 < 0.4f)
                v = 7;
            else
                v = 5;
            *(int *)(o + 0x19C) = v;
            *(float *)(o + 0x12C) = r1;
            *(int *)(o + 0x130) = 0;
        }
        v = *(int *)(o + 0x19C);
        if (v == 6) {
            *(float *)(o + 0x204) = *(float *)(o + 0x1A4) * -0.25f;
            CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRGoL[1]);
            SCRCharaTurnDirectInput(th, *(float *)(o + 0x204));
        } else if (v == 5) {
            *(int *)(o + 0x204) = 0;
        } else if (v == 7) {
            *(float *)(o + 0x204) = *(float *)(o + 0x1A4) * 0.25f;
            CharaCtrlSetScriptCtrlStatus(th, ScriptCtrlDef_SCRGoR[1]);
            SCRCharaTurnDirectInput(th, *(float *)(o + 0x204));
        }
    }
}
#endif
