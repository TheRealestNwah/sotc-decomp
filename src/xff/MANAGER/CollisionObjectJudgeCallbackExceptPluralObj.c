int CollisionObjectJudgeCallbackExceptPluralObj(int obj, int *list)
{
    int i;
    for (i = 0; i < list[0]; i++) {
        if (obj == list[i + 1]) return 0;
    }
    return 1;
}
