void RequestCharacterClassAdditionMotionChange(char *c, int motion)
{
    int n = *(signed char *)(c + 0xC94);
    if (n < *(int *)(c + 0x3FC)) {
        (*(int **)(c + 0x308))[n] = motion;
        *(signed char *)(c + 0xC94) += 1;
    }
}
