/* Parked: 23 diffs, same length. Remaining: register assignment for id, id >> 5, the sub-index copy and area (the Original keeps id in $a2 and copies sub from $v1 to $s4), and the rootPtn address, which the Original loads in a beqz delay slot. The shift = 5 local and hi = id << 27 come from a permuter run. */
#ifdef NONMATCHING
typedef struct
{
  int pad0[2];
  unsigned int slot[37];
} StageArea;
extern StageArea *D_0017A86C;
extern int *DldSysUndefSymbol;
extern char SH_StageDataDEFAULT[];
extern void sheetMgrLoadSegmentIndex(void *, int, int *);
extern void sheetMgrNopSegmentIndex(int);
extern void initstage(void *, int, int, int, int, int);
extern char rootPtn[];
extern void scrRun(void);
inline static char *dldResolve(unsigned int *h)
{
  unsigned int v = *h;
  int off = v & 0x3FFFF;
  int *t = (off != 0) ? (*((int **) (((char *) h) - off))) : (0);
  return ((t != 0) && (t != DldSysUndefSymbol)) ? (((char *) t[4]) + (((v >> 18) & 0xFFF) * ((int *) t[2])[3])) : (0);
}

static void func_00026AB8(int id)
{
  StageArea *sl = &D_0017A86C[(id >> 5) & 0x3FF];
  char *part = dldResolve(&sl->slot[0]) + (((id << 27) >> 27) * 0x3C);
  int shift;
  int idx;
  int area;
  int sub;
  char *t;
  char *e;
  int hi;
  int status;
  char *root;
  shift = 5;
  idx = (id >> 15) & 0x3FFF;
  area = (id >> shift) & 0x3FF;
  hi = id << 27;
  sub = hi >> 27;
  root = rootPtn;
  *((int *) (part + 4)) &= ~1;
  t = (SH_StageDataDEFAULT != ((char *) DldSysUndefSymbol)) ? (SH_StageDataDEFAULT) : (0);
  e = (t != 0) ? ((*((char **) (t + 0x10))) + (idx * 20)) : (0);
  if ((++(*((unsigned short *) (e + 0x10)))) == 1)
  {
    sheetMgrLoadSegmentIndex(SH_StageDataDEFAULT, idx, &status);
    sheetMgrNopSegmentIndex(0);
    while (((unsigned int) (status - 0xDEAF)) >= 2)
    {
      scrRun();
    }

    if (status != 0xDEB0)
    {
      initstage(root, idx, area, hi >> 27, 1, 0);
    }
  }
  *((int *) (part + 4)) = ((*((int *) (part + 4))) & (~3)) | 5;
}
#endif
