extern int B_000C2758[];

int get_letter_type(unsigned int i)
{
    if (i < 20) {
        return B_000C2758[i];
    }
    return 0;
}
