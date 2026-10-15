extern int B_000C2758[];

int entry_new_letter_type(int type)
{
    int i;
    for (i = 0; i < 20; i++) {
        if (B_000C2758[i] == 0) {
            B_000C2758[i] = type;
            return i;
        }
    }
    return -1;
}
