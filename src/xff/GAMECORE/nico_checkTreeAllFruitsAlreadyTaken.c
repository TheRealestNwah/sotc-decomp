extern int fruitsFlagChk(void *, int);

int nico_checkTreeAllFruitsAlreadyTaken(void *t)
{
    int i;
    for (i = 0; i < 32; i++) {
        if (!fruitsFlagChk(t, i))
            return 0;
    }
    return 1;
}
