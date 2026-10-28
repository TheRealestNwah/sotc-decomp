extern int Sg2RemoteGetSlotReleaseLv(int);
extern int sprintf(char *, const char *, ...);
extern char *strcpy(char *, const char *);
extern char *strcat(char *, const char *);

void Sg2SlotEnvTbl(char *output)
{
    char text[16];
    int slot;
    strcpy(output, "");
    for (slot = 0; slot < 48; slot++) {
        sprintf(text, "%04x ", Sg2RemoteGetSlotReleaseLv(slot));
        if ((slot + 1) % 12 == 0)
            strcat(text, "\n");
        strcat(output, text);
    }
}
