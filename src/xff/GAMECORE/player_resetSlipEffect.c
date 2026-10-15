extern void isysRequestDeleteObj(void *);

void player_resetSlipEffect(void *actor, void **effect)
{
    if (*effect != 0) {
        isysRequestDeleteObj(*effect);
        *effect = 0;
    }
}
