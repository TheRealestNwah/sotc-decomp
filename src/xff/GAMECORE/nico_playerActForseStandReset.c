extern void CancelSwordEffect();
extern int GAMEUTIL_is_player_obj();
extern void SCRRequestMotionDirect(int, int);
extern int ScriptCtrlDef_SCRPlayerForceStand;

int nico_playerActForseStandReset(int arg0)
{
    if (GAMEUTIL_is_player_obj() == 1) {
        SCRRequestMotionDirect(arg0, ScriptCtrlDef_SCRPlayerForceStand);
        CancelSwordEffect();
        return 1;
    }
    return 0;
}
