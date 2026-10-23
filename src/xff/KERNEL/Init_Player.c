typedef struct {
    int state;
    void (*play)(void);
    void (*stop)(void);
    void *work;
} Player;

extern void func_00007768(void);
extern void func_00007770(void);
extern void func_000077B8(void);
extern char B_00053F28[];

void Init_Player(Player *player)
{
    void (*play)(void) = func_00007770;
    void (*stop)(void) = func_000077B8;
    void *work = B_00053F28;

    player->state = 0;
    if (play != 0) {
        player->play = play;
    } else {
        player->play = func_00007768;
    }
    player->stop = stop;
    player->work = work;
}
