extern int fruitsFlagChk(unsigned int, int);

int nico_checkTreeAllFruitsAlreadyTaken(unsigned int t)
{
    int i;
    for (i = 0; i < 32; i++) {
        if (!fruitsFlagChk(t, i))
            return 0;
    }
    return 1;
}

