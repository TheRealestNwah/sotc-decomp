extern int B_000C2758[];
void init_letter_type_store(void)
{
    int i;
    for (i = 19; i >= 0; i--)
        B_000C2758[i] = 0;
}
