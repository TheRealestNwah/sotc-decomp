extern int GAMEUTIL_is_player_obj(void *);
extern char *GetSCRCharaAIWorkPtr(void *);
extern int is_doing_nico_sight_on(void *);
extern void get_hope_camera_direction_nico_sight_on(void *, void *);
extern void SCRGetLocalDirZ(void *, void *);

void nico_playerSightOnDirection(void *out, void *obj)
{
    int p = GAMEUTIL_is_player_obj(obj);
    char *w;

    if (p == 1) {
        w = GetSCRCharaAIWorkPtr(obj) + 0x190;
        if (is_doing_nico_sight_on(w) == 1) {
            get_hope_camera_direction_nico_sight_on(out, w);
            return;
        }
        SCRGetLocalDirZ(out, obj);
        return;
    }
    SCRGetLocalDirZ(out, obj);
}
