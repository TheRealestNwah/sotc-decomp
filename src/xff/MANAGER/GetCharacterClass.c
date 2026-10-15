void *GetCharacterClass(void *character)
{
    char *obj = character;
    unsigned char type = obj[8];

    if (type == 9) {
        return obj + 0x90;
    }
    if (type == 0x16) {
        return obj + 0x90;
    }
    return 0;
}
