#ifdef NONMATCHING
/* 67 diffs, same length (121 words); permuter best 715 (from 835) after 20 min with 10 workers. Draft from the asm: initialises the AI velocity channels of an AI work block w (offsets 0x2C4/0x2CC/0x2D0/0x2E0/0x2F4/0x2F8/0x2DC/0x318 via AI_UpdateVelocity), seeds the base velocity from the character class motion data, and derives a signed 0.8 factor from the pad block p (p+0x50, p+0x10). Differences: the Original reloads w+0x2D0 after the 128-bit store to w+0x330 and shares the config pointer in $v1 across both branches, and schedules the three zero stores after the 0x330 copy; ours keeps the value in a register and orders the stores differently. */
typedef int s128 __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));
extern void *isysGetThisSubThread(void);
extern char *GetCharacterClass(void *);
extern void AI_UpdateVelocity(float *, float, float);
extern void AI_GetMotionBasicVelocity(Vec4 *, void *, float);
void func_000ABA50(char *w, char *p)
{
  Vec4 vel;
  char *cc = GetCharacterClass(isysGetThisSubThread());
  char *cfg;
  float v;
  float new_var;
  float f;
  *((float *) (w + 0x2C8)) = 1.0f;
  AI_UpdateVelocity((float *) (w + 0x2C4), 1.0f, *((float *) ((*((char **) (w + 0x34))) + 0x4C)));
  AI_GetMotionBasicVelocity(&vel, cc + 0x9E0, *((float *) (w + 0x2C4)));
  if ((*((int *) (w + 0x2C))) != 0)
  {
    cfg = *((char **) (w + 0x34));
    v = ((((*((float *) (cfg + 0x1C))) - (*((float *) (cfg + 0x20)))) * ((*((float *) (cfg + 0x2C))) - (*((float *) (cfg + 0x28))))) / ((*((float *) (cfg + 0x24))) - (*((float *) (cfg + 0x20))))) + (*((float *) (cfg + 0x28)));
  }
  else
  {
    cfg = *((char **) (w + 0x34));
    v = *((float *) (cfg + 0x30));
  }
  *((float *) (w + 0x2D0)) = v;
  *((s128 *) (w + 0x330)) = *((s128 *) (&vel));
  new_var = 0.8f;
  *((int *) (w + 0x27C)) = 0;
  *((int *) (w + 0x28C)) = 0;
  *((float *) (w + 0x340)) = (*((float *) (cfg + 0xC))) * (*((float *) (w + 0x2D0)));
  AI_UpdateVelocity((float *) (w + 0x2E0), *((float *) (cfg + 0x5C)), *((float *) (cfg + 0x58)));
  AI_UpdateVelocity((float *) (w + 0x2F8), *((float *) (w + 0x340)), *((float *) (w + 0x2E0)));
  cfg = *((char **) (w + 0x34));
  *((int *) (w + 0x31C)) = 0;
  *((float *) (w + 0x2CC)) = (*((float *) (w + 0x2F8))) / (*((float *) (cfg + 0xC)));
  *((int *) (w + 0x274)) = 0;
  AI_UpdateVelocity((float *) (w + 0x2DC), 0.5f, 0.5f);
  AI_UpdateVelocity((float *) (w + 0x2F4), -0.1f, *((float *) (w + 0x2DC)));
  *((int *) (w + 0x2F0)) = 0;
  f = ((*((float *) (p + 0x50))) + 1.0f) * 0.5f;
  f = 1.0f - f;
  if ((*((float *) (w + 0x2F0))) < (*((float *) (p + 0x10))))
  {
    f = -f;
  }
  f = f * new_var;
  *((float *) (w + 0x314)) = f;
  AI_UpdateVelocity((float *) (w + 0x318), *((float *) (w + 0x2F0)), 0.1f);
}
#endif
