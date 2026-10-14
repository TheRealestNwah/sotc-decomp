extern int getDrawScreenHeight();

int SpriteMenuGetProgressiveOffset(void **arg0)
{
    int var_a0;

    var_a0 = 0;
    if (getDrawScreenHeight() < 0x1C0) {
        var_a0 = (*(int *)((char *)(*arg0) + 8));
    }
    return var_a0;
}
