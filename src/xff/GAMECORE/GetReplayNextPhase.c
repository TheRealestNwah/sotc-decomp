typedef struct { int a; int phase; } PhaseState;
extern PhaseState g_Replay;

int GetReplayNextPhase(void)
{
    switch (g_Replay.phase) {
    case 8:
        return 1;
    case 9:
        return 2;
    case 11:
        return 3;
    case 13:
        return 4;
    }
    return 0;
}
