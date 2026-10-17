extern char *GetDamageClass(char *);
int SCRConditionDamagedWeaponType(char *object, int type)
{
    char *damage = GetDamageClass(object);
    if (damage != 0 && *(int *)damage == 3) {
        if (type == 1) {
            int result = 0;
            int weapon = *(int *)(damage + 0x60);
            if (weapon == 1 || weapon == 3)
                result = 1;
            return result;
        }
        if (type == 0) {
            int result = 0;
            int weapon = *(int *)(damage + 0x60);
            if (weapon == 5 || weapon == 0 || weapon == 2 || weapon == 4)
                result = 1;
            return result;
        }
        return type == *(int *)(damage + 0x60);
    }
    return 0;
}
