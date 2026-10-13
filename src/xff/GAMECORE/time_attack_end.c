extern int gstatKaisouMode;
extern int gstatTimeAttackMode;

void time_attack_end(void)
{
    gstatTimeAttackMode = 0;
    gstatKaisouMode = 0;
}
