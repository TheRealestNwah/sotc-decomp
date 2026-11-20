
static int D_000409B8[3] = {1, 2, 0};
inline static float sqrtf(float x)
{
  float r;
__asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
  return r;
}

static void func_0000DD30(float *q, float m[4][4])
{
  float tr;
  float s;
  float r;
  int i;
  int j;
  int k;
  tr = (m[0][0] + m[1][1]) + m[2][2];
  if (tr > 0.0f)
  {
    s = sqrtf(tr + 1.0f);
    q[3] = s * 0.5f;
    r = 0.5f / s;
    q[0] = (m[1][2] - m[2][1]) * r;
    q[1] = (m[2][0] - m[0][2]) * r;
    q[2] = (m[0][1] - m[1][0]) * r;
  }
  else
  {
    i = 0;
    if (m[0][0] < m[1][1])
    {
      i = 1;
    }
    if (m[i][i] < m[2][2])
    {
      i = 2;
    }
    j = D_000409B8[i];
    k = D_000409B8[j];
    s = sqrtf((m[i][i] - (m[j][j] + m[k][k])) + 1.0f);
    q[i] = s * 0.5f;
    r = (s != 0.0f) ? 0.5f / s : 0.0f;
    q[3] = (m[j][k] - m[k][j]) * r;
    q[j] = (m[i][j] + m[j][i]) * r;
    q[k] = (m[i][k] + m[k][i]) * r;
  }
}

