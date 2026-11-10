#ifdef NONMATCHING
/* 51 diffs, same length (144 words); permuter best 1370 (from 2440) after 20 min. Draft from the asm (MANAGER): looks up the sprite-set entry table behind obj+0x60 (dld ref: count at target+0xC, data at target+0x10), finds entries whose id (+8) equals obj+0xC, and for each loads the sprite, positions/scales it, sets the UV rectangle and draws it with the draw-params block dp (alpha scaled by 0.6 when the flag at dp+8 bit 20 is clear and dp+0x38 & 0x1FF is set; y gets the screen-height offset when the screen is shorter than 0x1C0). Differences are in the dld ref helpers: the Original loads *ref twice (once for the count, once for the data) and builds each target test as beql / daddu forms with the count test fused into the loop guard; ours CSEs the load and emits the plain bne form. A volatile read of *ref made it worse (56). */
extern int *DldSysUndefSymbol;
extern int getDrawScreenHeight(void);
extern void spriteSetPosition(void *, float, float);
extern void spriteSetScale(void *, float, float);
extern void spriteSetTextureCoordinateUV(void *, float, float, float, float);
extern void spriteDrawSprite(void *, int, float, float, float, float, float, float, int, int);
inline static int dldCount(unsigned int *h)
{
  unsigned int v = *h;
  int off = v & 0x3FFFF;
  int *t = (off != 0) ? (*((int **) (((char *) h) - off))) : (0);
  return ((t != 0) && (t != DldSysUndefSymbol)) ? (t[3]) : (0);
}

inline static char *dldData(unsigned int *h)
{
  unsigned int v = *h;
  int off = v & 0x3FFFF;
  int *t = (off != 0) ? (*((int **) (((char *) h) - off))) : (0);
  return ((t != 0) && (t != DldSysUndefSymbol)) ? ((char *) t[4]) : (0);
}

void func_00095218(int *out, char *dp, char *obj, float alpha)
{
  unsigned int *ref = (unsigned int *) (obj + 0x60);
  int n = dldCount(ref);
  char *e = dldData(ref);
  float new_var2;
  char *new_var;
  if (e == 0)
  {
    return;
  }
  if (n <= 0)
  {
    return;
  }
  for (; n != 0; n--, e += 0x80)
  {
    int h;
    float a;
    unsigned int fl;
    if ((*((int *) (e + 8))) != (*((int *) (obj + 0xC))))
    {
      continue;
    }
    out[0] = ((int *) dldData((unsigned int *) e))[3];
    new_var = e;
    spriteSetPosition(out, (*((float *) (obj + 0x1C))) + (*((float *) (new_var + 0x1C))), (*((float *) (obj + 0x20))) + (*((float *) (e + 0x20))));
    spriteSetScale(out, *((float *) (e + 0x24)), *((float *) (e + 0x28)));
    spriteSetTextureCoordinateUV(out, *((float *) (e + 0x2C)), *((float *) (e + 0x30)), *((float *) (e + 0x34)), *((float *) (e + 0x38)));
    h = (getDrawScreenHeight() < 0x1C0) ? (*((int *) ((*((char **) dp)) + 8))) : (0);
    new_var2 = (*((float *) (dp + 0x20))) + ((float) h);
    a = alpha;
    fl = *((unsigned int *) (dp + 8));
    if ((((fl >> 20) & 1) == 0) && (((*((unsigned int *) (dp + 0x38))) & 0x1FF) != 0))
    {
      a = a * 0.6f;
    }
    spriteDrawSprite(out, *((int *) (dp + 0x24)), *((float *) (dp + 0x1C)), new_var2, *((float *) (dp + 0x28)), *((float *) (dp + 0x2C)), *((float *) (dp + 0x30)), a, (fl >> 14) & 0xF, *((int *) (obj + 0x70)));
  }

}
#endif
