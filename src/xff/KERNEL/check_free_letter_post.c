extern void discard_all_letter_in_post(int);
extern void iosFree(int);

void check_free_letter_post(int *arg0)
{
    int temp_v0;

    temp_v0 = *arg0;
    if (temp_v0 != 0) {
        discard_all_letter_in_post(temp_v0);
        iosFree(*arg0);
        *arg0 = 0;
    }
}
