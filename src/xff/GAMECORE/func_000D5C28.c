extern int GAMEUTIL_is_horse_obj(void *obj);
extern int CollisionObjectJudgeCallbackExceptPluralObj(int obj, int *list);

static int func_000D5C28(int obj, int *list)
{
    int horse = GAMEUTIL_is_horse_obj((void *)obj);
    if (horse == 1 && CollisionObjectJudgeCallbackExceptPluralObj(obj, list) == horse) {
        return horse;
    }
    return 0;
}
