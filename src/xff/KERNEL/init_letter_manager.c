extern int create_letter_post();
extern void init_letter_type_store();
extern int B_000C2750;
extern void *g_pLetterMem;
extern unsigned char rootPtn[1];

void init_letter_manager(void)
{
    init_letter_type_store();
    g_pLetterMem = &rootPtn;
    B_000C2750 = create_letter_post();
}
