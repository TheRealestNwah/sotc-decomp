extern int D_00040FB0;
extern int Sg2SlotSetOutputMode();

int setSoundMode(int m)
{
    int v = m ? 1 : 2;

    D_00040FB0 = v;
    return Sg2SlotSetOutputMode(v);
}
