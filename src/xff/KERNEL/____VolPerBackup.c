/* Copies 16 volume words between +0x24C and +0x28C: from +0x24C to +0x28C
   when restore is set, the other way otherwise. */
void ____VolPerBackup(char *st, int restore)
{
    int *src;
    int *dst;
    int i;

    if (restore != 0) {
        src = (int *)(st + 0x24C);
        dst = (int *)(st + 0x28C);
    } else {
        src = (int *)(st + 0x28C);
        dst = (int *)(st + 0x24C);
    }
    for (i = 7; i >= 0; i--) {
        *dst++ = *src++;
        *dst++ = *src++;
    }
}
