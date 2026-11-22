/* Collects collision finders for every member of a group (stopping when the finder set is full), and when a limit is set deletes the finders a script character class added beyond it. */
typedef struct {
    int count;
    int capacity;
    int limit;
} FinderSet;

typedef struct {
    float f;
    int a;
    int b;
} Params;

extern void FlushCollisionFinder(FinderSet *);
extern void DeleteCollisionFinder(FinderSet *, int);
extern int GetScriptCharacterClass(int);
extern int func_0009B6C8(FinderSet *, int, float, float, int, int, void *, int, int, int, int);
extern void func_000ADFC8(void *, Params *, int, int);
extern int func_000AE170(int, int);
extern void isysGroupForExit(int, int);
extern int *isysGroupForFirst(int, int);
extern int *isysGroupForNext(int *, int);

void GetCollisionDB(FinderSet *set, int group, float f12, int unused, int a, int b)
{
    char tmp[16];
    Params p;
    int limit;
    int (*filter)(int, int) = func_000AE170;

    p.a = a;
    p.b = b;
    FlushCollisionFinder(set);
    p.f = 0;
    limit = set->limit;
    func_000ADFC8(tmp, &p, p.a, p.b);
    if (limit < 0) {
        int *it;
        int member = 0;
        for (it = isysGroupForFirst(group, 0); it != 0; it = isysGroupForNext(it, 0)) {
            member = *it;
            if (set->count >= set->capacity)
                break;
            if (filter == 0 || filter(member, 0) != 0)
                func_0009B6C8(set, member, f12, p.f, p.a, p.b, tmp, 0, 0, 0, 0);
        }
        if (member != 0)
            isysGroupForExit(member, 0);
    } else {
        int *it = isysGroupForFirst(group, 0);
        int member = 0;
        if (it != 0) {
            do {
                member = *it;
                if (filter == 0 || filter(member, 0) != 0) {
                    int before = set->count < set->capacity ? set->count : -1;
                    int added = func_0009B6C8(set, member, f12, p.f, p.a, p.b, tmp, 0, 0, 0, 0);
                    if (limit < added && GetScriptCharacterClass(member) != 0) {
                        int cur = set->count;
                        int i = before;
                        int n = 0;
                        int end = set->capacity < cur ? set->capacity : cur;
                        if (added > 0 && before < end) {
                            do {
                                DeleteCollisionFinder(set, i);
                                i++;
                                n++;
                            } while (n < added && i < end);
                        }
                        set->count = before;
                    }
                }
                it = isysGroupForNext(it, 0);
            } while (it != 0);
        }
        if (member != 0)
            isysGroupForExit(member, 0);
    }
}
