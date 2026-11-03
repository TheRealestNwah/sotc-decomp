typedef struct {
    int start;
    int end;
    int slip;
    int grip;
    int a;
    int b;
} HangDef;

extern HangDef B_0018B748[];
extern int *SkelFocusDef_PLAYER_HAND_L_START, *SkelFocusDef_PLAYER_HAND_L_END;
extern int *SkelFocusDef_PLAYER_HAND_R_START, *SkelFocusDef_PLAYER_HAND_R_END;
extern int *SkelFocusDef_PLAYER_FOOT_L_START, *SkelFocusDef_PLAYER_FOOT_L_END;
extern int *SkelFocusDef_PLAYER_FOOT_R_START, *SkelFocusDef_PLAYER_FOOT_R_END;
extern int *ScriptCtrlDef_SCRPlayerLHandSlip, *ScriptCtrlDef_SCRPlayerLHandGrip;
extern int *ScriptCtrlDef_SCRPlayerRHandSlip, *ScriptCtrlDef_SCRPlayerRHandGrip;
extern int *ScriptCtrlDef_SCRPlayerLFootSlip, *ScriptCtrlDef_SCRPlayerLFootGrip;
extern int *ScriptCtrlDef_SCRPlayerRFootSlip, *ScriptCtrlDef_SCRPlayerRFootGrip;
extern void InitTwoWayLink(void *, void *);

void player_initHangPointWork(char *w)
{
    HangDef defs[4] = {
        { SkelFocusDef_PLAYER_HAND_L_START[2], SkelFocusDef_PLAYER_HAND_L_END[2],
          ScriptCtrlDef_SCRPlayerLHandSlip[1], ScriptCtrlDef_SCRPlayerLHandGrip[1], 1, 1 },
        { SkelFocusDef_PLAYER_HAND_R_START[2], SkelFocusDef_PLAYER_HAND_R_END[2],
          ScriptCtrlDef_SCRPlayerRHandSlip[1], ScriptCtrlDef_SCRPlayerRHandGrip[1], 1, 1 },
        { SkelFocusDef_PLAYER_FOOT_L_START[2], SkelFocusDef_PLAYER_FOOT_L_END[2],
          ScriptCtrlDef_SCRPlayerLFootSlip[1], ScriptCtrlDef_SCRPlayerLFootGrip[1], 0, 0 },
        { SkelFocusDef_PLAYER_FOOT_R_START[2], SkelFocusDef_PLAYER_FOOT_R_END[2],
          ScriptCtrlDef_SCRPlayerRFootSlip[1], ScriptCtrlDef_SCRPlayerRFootGrip[1], 0, 0 },
    };
    int i;

    for (i = 3; i != -1; i--)
        B_0018B748[i] = defs[i];
    *(int *)(w + 0x60) = 0;
    InitTwoWayLink(w + 0x50, w);
    *(int *)w = 0;
}
