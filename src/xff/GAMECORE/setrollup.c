
extern float B_0019CD3C;
extern float D_0017B018[];
extern float D_0017AFF0;
extern char gcGlobalVar[];
typedef struct 
{
  int flag;
  float a;
  float b;
  float pad;
  float c;
} RollupState;
extern RollupState B_0019CD10;
extern void func_000BC988(int);
/* The empty asm clobbering $31 at the start of the inner block tells reorg that $ra is dead there, so the branch over it stays a plain bc1f with the epilogue ld $ra in its delay slot, as in the Original. */
void setrollup(float v)
{
  float prev;
  float lim;
  if ((!(B_0019CD3C > 0.0f)) && (v != D_0017B018[0]))
  {
    D_0017B018[0] = v;
    lim = D_0017AFF0 - 0.001f;
    prev = D_0017B018[2];
    D_0017B018[2] = v;
    D_0017B018[1] = prev;
    if ((prev < lim) && (lim <= v))
    {
      float c1 = 0.6f;
      float c2 = 0.5f;
      __asm__("" ::: "$31");
      func_000BC988(4);
 do { B_0019CD10.flag = 1; B_0019CD10.c = *((float *) (gcGlobalVar + 0x178)); B_0019CD10.a = c1; } while (0);
      B_0019CD10.b = c2;
    }
  }
}
