extern char B_001884D0[];
extern void gameFlagCheckPointSave(int, int, int, int, int, void *);

void gStatOmakeSave(void)
{
    gameFlagCheckPointSave(0, 0, 0, 0, 0, B_001884D0);
}
