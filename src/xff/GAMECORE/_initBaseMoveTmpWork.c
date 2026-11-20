#ifdef NONMATCHING /* 2 words: only the order of the two hoisted lui (gcGlobalVar first in the original) differs; the w->in store goes through a union so the float loads aren't moved above it */

typedef struct 
{
  char pad0[0x74];
  int deg;
} BmSub;
typedef struct 
{
  BmSub *sub;
  char pad4[0x1C - 4];
  float f1C;
} BmInner;
typedef struct 
{
  char pad0[0x1C0];
  BmInner in;
  char pad1DC[0x374 - 0x1DC];
  float f374;
  char pad378[0x524 - 0x378];
  float f524;
  char pad528[0x570 - 0x528];
  float f570;
  float f574;
  char pad578[0x72C - 0x578];
  float f72C;
} BmChr;
typedef struct 
{
  int *state;
  int path;
  int obj;
  int w0;
  int w1;
  BmChr *chr;
  int layout;
  BmInner *in;
  char pad20[0xA0 - 0x20];
  float dt;
  float a4;
  float a8;
  float aC;
  float b0;
  float b4;
  float b8;
} BmWork;
typedef union { BmInner *p; BmSub *s; float f; int i; } InOrAny;
typedef struct { char pad[0x190]; float dt; } GcG;
extern GcG gcGlobalVar;
extern float chkTime2Int;
extern int getPassageWork(int, int);
extern BmChr *GetCharacterClass(int);
extern int GetLayoutClass(int);
void _initBaseMoveTmpWork(int obj, BmWork *w, int *state, int path)
{
  float g;
  float ct;
  w->obj = obj;
  w->state = state;
  w->path = path;
  w->w0 = getPassageWork(path, 0);
  w->w1 = getPassageWork(path, 1);
  w->chr = GetCharacterClass(obj);
  w->layout = GetLayoutClass(obj);
  {
  register char *chr __asm__("$5") = (char *)w->chr;
  register BmInner *in __asm__("$3") = (BmInner *)(chr + 0x1C0);
  ((InOrAny *)&w->in)->p = in;
  ct = chkTime2Int;
  w->a4 = ((float) in->sub->deg) * 0.0174532924f;
  w->a8 = (*((float *) (chr + 0x72C))) * 0.0174532924f;
  w->aC = in->f1C;
  w->b0 = 1.0f / (((*((float *) (chr + 0x374))) * in->f1C) * (*((float *) (chr + 0x524))));
  w->b4 = *((float *) (chr + 0x574));
  w->b8 = *((float *) (chr + 0x570));
  g = gcGlobalVar.dt;
  w->dt = g;
  if (ct < g)
  {
    w->dt = ct;
  }
  }
  *state = 0;
}
#endif
