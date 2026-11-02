typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int data[0x10];
    int target;
    int option;
    char pad48[8];
    int type;
    char pad54[0xC];
} CharacterObjMail;

extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern int _isysRecvSubMsg(void *, void *, int);
extern void ChangeCharacterObjControlTarget(void *, int);
extern void ChangeCharacterObjControlledTarget(void *, int, void *, int);
extern void SetCharacterClassMotionNormalSyncMode(char *, int);
extern void SetCharacterClassMotionAddSyncMode(char *, int);
extern void ForceParentLayoutObj(void *, void *);
extern s128 ZeroPoint;
extern s128 IdentityQuaternion;

void RecvCharacterObjMail(void *obj)
{
    CharacterObjMail mail;
    char *cls = GetCharacterClass(obj);

    while (_isysRecvSubMsg(cls + 0x10D0, &mail, 0x60) != 0) {
        switch (mail.type) {
        case 0:
            break;
        case 1:
            ChangeCharacterObjControlTarget(obj, mail.data[0]);
            break;
        case 2:
            ChangeCharacterObjControlledTarget(obj, mail.target, &mail, mail.option);
            break;
        case 3:
            SetCharacterClassMotionNormalSyncMode(cls, mail.data[0]);
            break;
        case 5:
            SetCharacterClassMotionAddSyncMode(cls, mail.data[0]);
            break;
        case 4: {
            char *layout;
            ForceParentLayoutObj(obj, &mail);
            layout = GetLayoutClass(obj);
            *(s128 *)(layout + 0x70) = ZeroPoint;
            *(s128 *)(layout + 0x60) = IdentityQuaternion;
            break;
        }
        }
    }
}
