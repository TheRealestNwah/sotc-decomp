typedef struct { int a; int id; char pad[0x3C]; int state; char pad2[0x38]; } SubAnim;

int SearchSubAnimation(char *c, int id)
{
    int i;
    SubAnim *s = *(SubAnim **)(c + 0x30C);
    for (i = 0; i < *(int *)(c + 0x3FC); i++, s++) {
        if (s->state != -2 && s->id == id)
            return i;
    }
    return -1;
}
