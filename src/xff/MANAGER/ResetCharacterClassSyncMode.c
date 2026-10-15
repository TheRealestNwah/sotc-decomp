extern void DeleteTwoWayLink(void *);

void ResetCharacterClassSyncMode(char *c)
{
    if (*(int *)(c + 0xD00) != 0) {
        DeleteTwoWayLink(c + 0xD10);
        c[0xD90] = 0;
        *(int *)(c + 0xD00) = 0;
        c[0xD91] = 0;
    }
}
