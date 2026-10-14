
extern void *GetCharacterClass(void *);
float SCRGetPlayerTiredParam(void *actor)
{
  char *character = GetCharacterClass(actor);
  float *velocity;
  if ((!character) || (!(*((int *) (character + 0x124)))))
  {
    return 0.0f;
  }
  velocity = (float *) ((*((char **) (character + 0x19C))) + 0x88);
  {
    float value0 = *velocity;
    if ((value0 < 0.0f) ? (value0 < (-10.0f)) : (value0 > 10.0f))
    {
      return 0.1f;
    }
  }
  {
    float value1 = *((float *) ((*((char **) (character + 0x19C))) + 0x88));
    if ((value1 < 0.0f) ? (value1 < (-3.0f)) : (value1 > 3.0f))
    {
      return 0.03f;
    }
  }
  {
    float value2 = *((float *) ((*((char **) (character + 0x19C))) + 0x88));
    if ((value2 < 0.0f) ? (value2 < (-1.0f)) : (1.0f < value2))
    {
      return 0.01f;
    }
  }
  return 0.0f;
}
