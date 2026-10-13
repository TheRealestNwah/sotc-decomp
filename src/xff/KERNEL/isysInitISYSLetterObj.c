extern int create_letter_post();

void isysInitISYSLetterObj(void *arg0)
{
    (*(int *)((char *)(arg0) + 0x1C)) = create_letter_post();
}
