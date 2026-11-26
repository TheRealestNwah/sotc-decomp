/* Parked draft: adds collision finders for every member of a group (stopping when the finder set
   is full), and when the set has a limit deletes the finders a script character class added beyond
   it. 7 diffs, same size: the p.b store lands in the func_000ADFC8 delay slot instead of p.limit,
   and the func_000AE170 address is in v0 (original: v1). v1/v0 pins on the p.limit test fixed
   its reload (10 -> 7); pins on the filter tests have no effect. The `pa` pointer and
   the int return on func_000ADFC8 came from the permuter (37 -> 13); the empty asm on the limit
   load fixed the p.limit store register (13 -> 10). */
#ifdef NONMATCHING

typedef struct 
{
    int count;
    int capacity;
    int limit;
} FinderSet;
typedef struct 
{
    float f;
    int a;
    int b;
    int limit;
} Params;
extern void DeleteCollisionFinder(FinderSet *, int);
extern int GetScriptCharacterClass(int);
extern int func_0009B6C8(FinderSet *, int, float, float, int, int, void *, int, int, int, int);
extern int func_000ADFC8(void *, Params *, int, int);
extern int func_000AE170(int, int);
extern void isysGroupForExit(int, int);
extern int *isysGroupForFirst(int, int);
extern int *isysGroupForNext(int *, int);
void AddCollisionDB(FinderSet *set, int group, int user, int a, int b, float f12)
{
    char tmp[16];
    int *pa;
    Params p;
    int (*filter)(int, int) = func_000AE170;
    p.a = a;
    p.b = b;
    pa = &p.a;
    {
        int l = set->limit;

        __asm__("" : "+r"(l));
        p.f = 0;
        p.limit = l;
    }
    func_000ADFC8(tmp, &p, *pa, p.b);
    if (p.limit < 0)
    {
      int *it;
      int member = 0;
      for (it = isysGroupForFirst(group, 0); it != 0; it = isysGroupForNext(it, 0))
      {
        member = *it;
        if (set->count >= set->capacity)
        {
          break;
        }
        if ((filter == 0) || (filter(member, user) != 0))
        {
          func_0009B6C8(set, member, f12, p.f, p.a, p.b, tmp, 0, 0, 0, user);
        }
      }

      if (member != 0)
      {
        isysGroupForExit(member, 0);
      }
    }
    else
    {
      int *it = isysGroupForFirst(group, 0);
      int member = 0;
      if (it != 0)
      {
        do
        {
          member = *it;
          if ((filter == 0) || (filter(member, user) != 0))
          {
            int before = (set->count < set->capacity) ? (set->count) : (-1);
            int added = func_0009B6C8(set, member, f12, p.f, p.a, p.b, tmp, 0, 0, 0, user);
            if (({
                  register int l __asm__("$3") = p.limit;
                  register int t __asm__("$2") = l < added;
                  t;
                }) && (GetScriptCharacterClass(member) != 0))
            {
              int cur = set->count;
              int i = before;
              int n = 0;
              int end = (set->capacity < cur) ? (set->capacity) : (cur);
              if ((added > 0) && (before < end))
              {
                do
                {
                  DeleteCollisionFinder(set, i);
                  i++;
                  n++;
                }
                while ((n < added) && (i < end));
              }
              set->count = before;
            }
          }
          it = isysGroupForNext(it, 0);
        }
        while (it != 0);
      }
      if (member != 0)
      {
        isysGroupForExit(member, 0);
      }
    }
}
#endif
