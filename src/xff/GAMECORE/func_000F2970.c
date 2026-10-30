typedef struct {
    float score;
    int a;
    int b;
    char pad[0x65C - 0xC];
} Candidate;

typedef struct {
    int count;
    Candidate *items;
} CandidateList;

static void func_000F2970(int *outA, int *outB, CandidateList *list)
{
    int i;
    int a = 0;
    int b = 0;
    float best = -1.0f;
    Candidate *c;

    i = list->count;
    if (i > 0) {
        c = list->items;
        do {
            if (best < c->score) {
                a = c->a;
                best = c->score;
                b = c->b;
            }
            c++;
        } while (--i != 0);
    }
    *outA = a;
    *outB = b;
}
