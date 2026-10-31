extern char *GetCharacterClass(void *);

typedef struct {
    void *p[2];
} Pair;

static int func_000E1B68(void *a, char *b)
{
    Pair s;
    Pair t;
    int i;

    t.p[0] = a;
    t.p[1] = *(void **)(b + 0x504);
    s = t;
    for (i = 0; i < 2; i++) {
        void *p = s.p[i];
        char *c;

        if (p == 0) {
            continue;
        }
        c = GetCharacterClass(p);
        if (c != 0) {
            char *q = *(char **)(c + 0x578);

            if (q != 0) {
                int v = *(int *)(q + 0x90);

                if (v >= 0x26) { continue; } if (v >= 0x23) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
