extern void *GetDamageClass(void *);
extern void ResetDamageClass(void *);
extern void CheckDamageLetter(void *, void *);
extern void CheckLetter(void *, void (*)(void *, void *));

void ExecScriptLayoutObj(void *object)
{
    ResetDamageClass(GetDamageClass(object));
    CheckLetter(object, CheckDamageLetter);
}
