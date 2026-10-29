extern void _gameFWorkSet(int, float);
void setPlayerMaxHp(float hp)
{
 float limit = 570.0f < hp ? 570.0f : hp;
 _gameFWorkSet(11, limit);
}
