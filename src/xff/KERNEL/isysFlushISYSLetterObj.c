extern int check_free_letter_post();

int isysFlushISYSLetterObj(int a, int b, int c, int d)
{
    return check_free_letter_post(a + 28, b, c, d);
}
