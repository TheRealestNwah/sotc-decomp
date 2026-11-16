typedef struct { int a[8]; } __attribute__((aligned(8))) B32;
extern char gcGlobalVar[];
extern void *isysGetThisSubThread(void);
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(int, int);
extern char *GetScriptCharacterClass(int);
extern void iosFree(void *);
extern void Kite_SucceedKitePathWork(void *, void *);
extern void func_0009D6C8(char *);
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define BB(p, o) (*(B32 *)((char *)(p) + (o)))

static void func_0009D788(char *w)
{
    int self = (int)isysGetThisSubThread();
    register int had __asm__("$20");
    int found;
    char *k;
    char *s;
    char *c;

    had = I(w, 0x2C);
    found = (int)isysGetThisSubThread();

    if (I(w, 8) != -1) {
        int cur = 0;
        int *it;
        for (it = isysGroupForFirst(gcGlobalVar + 0x2BC, 0); it != 0; it = isysGroupForNext(it, 0)) {
            cur = *it;
            k = P(GetScriptCharacterClass(cur), 0x1200);
            if (k != 0 && I(k, 0) == 4 && I(k, 8) == I(w, 8) && I(k, 4) == I(w, 4) && I(k, 0x34) != 2
                && I(k, 0x19C) < 5) {
                found = cur;
                break;
            }
        }
        if (cur != 0)
            isysGroupForExit(cur, 0);
    }
    I(w, 0x28) = found;
    c = P(GetScriptCharacterClass(found), 0x1200);
    P(w, 0x30) = c;
    if (I(w, 0x19C) < 5) {
        if (I(w, 0x28) == self || I(w, 0x28) == 0 || c == 0) {
            I(w, 0x34) = 0;
            I(w, 0x2C) = 1;
            I(w, 0x494) = 1;
            if (!had)
                func_0009D6C8(w);
            goto tail;
        }
    }
    I(w, 0x2C) = 0;
    I(w, 0x34) = 1;
    if (had && I(w, 0x284) >= 0 && P(w, 0x278) != 0) {
        iosFree(P(w, 0x278));
        P(w, 0x278) = 0;
    }
tail:
    if (I(w, 0x494) == 0 && (s = P(w, 0x30)) != 0) {
        BB(w, 0x570) = BB(s, 0x570);
        BB(w, 0x4F0) = BB(s, 0x4F0);
        BB(w, 0x530) = BB(s, 0x530);
        BB(w, 0x510) = BB(s, 0x510);
        BB(w, 0x550) = BB(s, 0x550);
        I(w, 0x1AC) = I(s, 0x1AC);
        Kite_SucceedKitePathWork(w + 0x280, s + 0x280);
    }
}
