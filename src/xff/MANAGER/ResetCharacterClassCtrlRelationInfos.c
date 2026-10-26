extern int isysDeleteGroupAllObj(void *group);

int ResetCharacterClassCtrlRelationInfos(char *character)
{
    return isysDeleteGroupAllObj(character + 0x10E4);
}
