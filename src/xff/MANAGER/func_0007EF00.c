#ifdef NONMATCHING
/* 39 diffs (permuter best 520 from a base of 990, plateaued), same length (143 words incl. the func_0007F100 tail). Recovered: for each active entry (stride 0x80, state at +0x44 != -2) whose resource key (ref at entry+4 -> +8) equals the requested key, call the static func_0007E9B8 with the matched entry's data; the share factor is 1/activeCount when w+0x418 is set. Uses the dld reference decode (0x3FFFF offset, DldSysUndefSymbol) like func_00081388. Remaining: saved-register order in the prologue and loop-carried count copies. */

extern void *DldSysUndefSymbol;
inline static char *refModule(unsigned int *reference)
{
  unsigned int offset = (*reference) & 0x3FFFF;
  if (offset)
    return *((char **) (((char *) reference) - offset));
  return 0;
}

inline static char *resourceData(unsigned int *reference)
{
  unsigned int encoded = *reference;
  char *module = refModule(reference);
  if (module && (module != DldSysUndefSymbol))
  {
    int index = (encoded >> 18) & 0xFFF;
    char *definition = *((char **) (module + 8));
    char *data = *((char **) (module + 0x10));
    return data + (index * (*((int *) (definition + 0xC))));
  }
  return 0;
}

extern void func_0007E9B8(int, int, int, void *, void *, void *, void *, void *, int, int, int, float, float, float);
static void func_0007EF00(int arg0, int arg1, int arg2, char *w, char *key, int e1, int e2, float scale)
{
  char *table = *((char **) (w + 0x30C));
  int n = *((int *) (w + 0x3FC));
  int count = 0;
  char **new_var;
  int i;
  char *e;
  float inv;
 do { e = table; for (i = 0; i < n; i++) { if ((*((int *) (e + 0x44))) != (-2)) { count++; } e += 0x80; } if (count == 0) { return; } inv = 1.0f; } while (0);
  if ((*((int *) (w + 0x418))) != 0)
  {
    inv = 1.0f / ((float) count);
  }
  e = table;
  for (i = 0; i < n; i++)
  {
    new_var = (char **) (e + 4);
    if ((*((int *) (e + 0x44))) >= 0)
    {
      char *t0 = *new_var;
      if (resourceData((unsigned int *) (t0 + 8)) == key)
      {
        char *tab2 = *((char **) (w + 0x30C));
        int t5 = *((int *) ((*((char **) (w + 0x304))) + (i * 4)));
        float f14 = *((float *) ((tab2 + (i * 0x80)) + 0x54));
        char *t2 = (tab2 + (i * 0x80)) + 0x60;
        char *t3 = (tab2 + (i * 0x80)) + 0x70;
        char *t1 = resourceData((unsigned int *) (t0 + 0x28));
        if (t0 != ((char *) (-0x50)))
        {
          func_0007E9B8(arg0, arg1, arg2, e + 4, t0, t1, t2, t3, t5, e1, e2, scale, inv, f14);
        }
        n = *((int *) (w + 0x3FC));
      }
    }
    e += 0x80;
  }

}
#endif
