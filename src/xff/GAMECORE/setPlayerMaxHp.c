extern int _gameFWorkSet(int, float);
int setPlayerMaxHp(float hp)
{
 float limit = 570.0f < hp ? 570.0f : hp;
 return _gameFWorkSet(11, limit);
}
