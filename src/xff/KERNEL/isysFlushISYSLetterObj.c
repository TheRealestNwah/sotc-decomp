extern void check_free_letter_post(int *);

void isysFlushISYSLetterObj(char *object)
{
    check_free_letter_post((int *)(object + 28));
}
