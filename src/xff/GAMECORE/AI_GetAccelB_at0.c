float AI_GetAccelB_at0(float a, float b, float t)
{
 float step;
 b -= a;
 b += b;
 step = t < 0.0333667f ? 0.0333667f : t;
 return b / step;
}
