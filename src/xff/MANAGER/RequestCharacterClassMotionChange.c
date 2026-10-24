/* The do/while (0) scope (likely an original macro shared with
   RequestCharacterClassMotionChangeWithParam) is needed for the counter
   address to be computed before the first store. */
void RequestCharacterClassMotionChange(char *p, int motion, int frame)
{
    signed char *count = (signed char *)(p + 0xC40);

    do {
        *(int *)(p + 0xC44) = motion;
        *(int *)(p + 0xC48) = frame;
        if (*count <= 0) {
            (*count)++;
        }
    } while (0);
    *(char *)(p + 0xC4C) = 0;
    *(int *)(p + 0xC50) = 0;
}
