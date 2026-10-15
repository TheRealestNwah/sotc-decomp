typedef struct { int a; int phase; } PhaseState;
extern PhaseState g_TimeAttack;

int GetTimeAttackNextPhase(void)
{
    switch (g_TimeAttack.phase) {
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
