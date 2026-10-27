extern void AddCharacterClassOptionNodeSubGeometry(void *, void *, char *, void *, int);
void AddCharacterClassOptionNodeSubGeometries(void *owner, void *group, char *character, int index)
{
    int i;
    char *node = *(char **)(character + 0x30C);
    for (i = 0; i < *(int *)(character + 0x3FC); i++, node += 0x80) {
        if (*(int *)(node + 0x44) != -2)
            AddCharacterClassOptionNodeSubGeometry(owner, group, character, node + 4, index);
    }
}
