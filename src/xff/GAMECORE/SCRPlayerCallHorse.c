extern void *GetSCRCharaAIWorkPtr();
extern int SCRGetFirstObj(void *);
extern void begin_object_interest_game_camera(int, int);
extern int get_game_camera(int);
extern int get_main_cameraman();
extern unsigned char gcGlobalVar[1];

void SCRPlayerCallHorse(void)
{
    int temp_s0;
    int temp_v0;

    (*(signed char *)((char *)(GetSCRCharaAIWorkPtr()) + 0xD9C)) = 1;
    temp_s0 = get_game_camera(get_main_cameraman());
    temp_v0 = SCRGetFirstObj(&gcGlobalVar + 0x2B4);
    if (temp_v0 != 0) {
        begin_object_interest_game_camera(temp_s0, temp_v0);
    }
}
