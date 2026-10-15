extern void ForceUnparentLayoutObj(void *);
extern void DebugSetObjectGeometry(void *, void *, void *);
extern void *get_main_cameraman(void);
extern void *get_game_camera(void *);
extern void reset_game_camera(void *);

void forceMoveObjToPos(void *o, void *pos, void *rot)
{
    ForceUnparentLayoutObj(o);
    DebugSetObjectGeometry(o, pos, rot);
    reset_game_camera(get_game_camera(get_main_cameraman()));
}
