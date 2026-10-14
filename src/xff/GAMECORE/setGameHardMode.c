extern void SetDamageClassDamageTableType(int);
extern int B_0018479C;

void setGameHardMode(int arg0)
{
    B_0018479C = arg0;
    SetDamageClassDamageTableType(arg0 != 0);
}
