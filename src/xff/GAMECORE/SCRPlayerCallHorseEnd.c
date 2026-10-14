extern void *GetSCRCharaAIWorkPtr(void *);
extern void end_object_interest_game_camera(int);
extern int get_game_camera(int);
extern int get_main_cameraman();

void SCRPlayerCallHorseEnd(void *actor) {
    void *temp_s0;

    temp_s0 = GetSCRCharaAIWorkPtr(actor);
    end_object_interest_game_camera(get_game_camera(get_main_cameraman()));
    (*(signed char *)((char *)(temp_s0) + 0xD9C)) = 0;
}
