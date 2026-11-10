#ifdef NONMATCHING
/* ~120 diffs, same length (162 words). Draft from the asm: state machine on o+0x258 (7 cases via a jump table), writing the next state to o+0x264. 0 -> 1 when o[0x280] > o[0x270]; 1 -> 2; 2/3/4 first run the minotaur-death check (o+0x30 set and GetCharacterClass(o[0x24])+0x750 == ControlMode_MINOTOUR_DEATH adds gcGlobalVar+0x190 to o+0x290 and goes to 5), then compare (q[0x48] - P[0]) against -P[1] / +P[1] with P = o[0x34], q = o[0x220]: below -P[1] -> 2, above P[1] -> 4 (case 4 only tests the first, case 3 sends the fall-through tail to 2, case 2 to 3); 5 -> 6 once q[0x44] < 10.0; default -> 2. Difference: the Original loads P into v0 and q into v1 in cases 2/3 (swapped in case 4) and reloads q[0x48], P[0], P[1] for the second compare (no CSE), while ours loads P/q the other way round and reuses the loaded floats, so the whole body after the first compare shifts. */
extern void *isysGetThisSubThread(void);
extern char *GetCharacterClass(void *);
extern int ControlMode_MINOTOUR_DEATH;
extern char gcGlobalVar[];

static inline int checkDeath(char *o)
{
    if (*(int *)(o + 0x30) != 0) {
        if (*(int *)(GetCharacterClass(*(void **)(o + 0x24)) + 0x750) == ControlMode_MINOTOUR_DEATH) {
            *(float *)(o + 0x290) += *(float *)(gcGlobalVar + 0x190);
            return 1;
        }
    }
    return 0;
}

static void func_000AAF70(char *o)
{
    float *P;
    char *q;
    int a;
    int next;

    isysGetThisSubThread();
    switch (*(int *)(o + 0x258)) {
    case 0:
        if (*(float *)(o + 0x280) > *(float *)(o + 0x270)) {
            next = 1;
            break;
        }
        return;
    case 1:
        next = 2;
        break;
    case 2:
        if (checkDeath(o)) {
            next = 5;
            break;
        }
        P = *(float **)(o + 0x34);
        q = *(char **)(o + 0x220);
        a = *(float *)(q + 0x48) - P[0] < -P[1] ? 1 : 0;
        if (a) {
            next = 2;
            break;
        }
        a = P[1] < *(float *)(q + 0x48) - P[0] ? 1 : 0;
        if (a) {
            next = 4;
            break;
        }
        if (*(float *)(o + 0x280) > *(float *)(o + 0x270)) {
            next = 3;
            break;
        }
        return;
    case 3:
        if (checkDeath(o)) {
            next = 5;
            break;
        }
        P = *(float **)(o + 0x34);
        q = *(char **)(o + 0x220);
        a = *(float *)(q + 0x48) - P[0] < -P[1] ? 1 : 0;
        if (a) {
            next = 2;
            break;
        }
        a = P[1] < *(float *)(q + 0x48) - P[0] ? 1 : 0;
        if (a) {
            next = 4;
            break;
        }
    tail:
        if (*(float *)(o + 0x280) > *(float *)(o + 0x270)) {
            next = 2;
            break;
        }
        return;
    case 4:
        if (checkDeath(o)) {
            next = 5;
            break;
        }
        P = *(float **)(o + 0x34);
        q = *(char **)(o + 0x220);
        a = *(float *)(q + 0x48) - P[0] < -P[1] ? 1 : 0;
        if (!a)
            goto tail;
        next = 2;
        break;
    case 5:
        q = *(char **)(o + 0x220);
        if (*(float *)(q + 0x44) < 10.0f) {
            next = 6;
            break;
        }
        return;
    case 6:
        return;
    default:
        next = 2;
        break;
    }
    *(int *)(o + 0x264) = next;
}
#endif
