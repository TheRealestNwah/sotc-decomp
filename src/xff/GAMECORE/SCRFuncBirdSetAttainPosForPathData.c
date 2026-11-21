/* Parked: 5 diffs, same size. Bird path attain: looks up the two event points, follows each one's connecting line to its neighbour, takes the dot of the normalized directions (layout->point, point->neighbour) and sets the attainment position to the point with the larger dot. The loop walks pts/dot through a pointer pinned to s4 with the counter pinned to s5 (an int counter otherwise loses the strength-reduced pointer; char adds a sign extension), and the first VU subtraction pins its operands. Remaining: the s4 pointer is set before the d0/d1 addresses instead of after, and the p move into a1 is scheduled after the pts load instead of before. */
#ifdef NONMATCHING

typedef struct 
{
  int unk0;
  int pts;
  int lines;
} PathInfo;
extern int GetSCRCharaAIWorkPtr(void);
extern char *GetLayoutClass(int);
extern PathInfo *getPathInfo(int);
extern int getPointDataFromEvent(int, int, int *);
extern short *getConnectLineArray(int, int);
extern short *getLineData(int, short);
extern float *getPointData(int, short);
extern void setAttainmentPos(int, int);
static inline void normalize3(float *v)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

/* returns no value; a void return type moves the scheduling (3 more diffs) */
static inline short sub4(float *d, float *a, float *b)
{
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline float dot3(float *a, float *b)
{
  float r;
__asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
  return r;
}

void SCRFuncBirdSetAttainPosForPathData(int obj, int ev0, int ev1)
{
  int pts[2];
  int ids[2];
  float dot[2];
  float d0[4];
  float d1[4];
  int work = GetSCRCharaAIWorkPtr() + 0x10;
  char *lay = GetLayoutClass(obj);
  register PathInfo *info __asm__("$19") = getPathInfo(work);
  register int i __asm__("$21");
  register int *pp __asm__("$20");
  pts[0] = getPointDataFromEvent(work, ev0, &ids[0]);
  pts[1] = getPointDataFromEvent(work, ev1, &ids[1]);
  if (pts[0] == 0)
  {
    return;
  }
  if (pts[1] == 0)
  {
    setAttainmentPos(work, pts[0]);
    return;
  }
  for (i = 0, pp = pts; i < 2; i++, pp++)
  {
    short *line = getLineData(info->lines, *getConnectLineArray(info->pts, ids[i]));
    short next;
    float *p;
    if (line == 0)
    {
      return;
    }
    next = line[0];
    if (ids[i] == next)
    {
      next = line[1];
    }
    p = getPointData(info->pts, next);
    {
    register float *pa __asm__("$4") = (float *) *pp;
    register float *lp __asm__("$2") = *((float **) (lay + 0x134));
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsub.xyzw vf7, vf5, vf6
"
                         "sqc2 vf7, 0x0(%0)
"
                         : : "r"(d0), "r"(pa), "r"(lp) : "memory");
    }
    sub4(d1, p, (float *) *pp);
    normalize3(d0);
    normalize3(d1);
    *(float *)(pp + 8) = dot3(d0, d1);
  }

  if (dot[0] > dot[1])
  {
    setAttainmentPos(work, pts[0]);
  }
  else
  {
    setAttainmentPos(work, pts[1]);
  }
}
#endif
