extern void *GetCharacterClass(void *);
extern void *GetLayoutClass(void *);

typedef int s128 __attribute__((mode(TI)));
#define NULL ((void *)0)
void GAMEUTIL_get_local_quaternion(s128 *arg0, void *arg1) {
    s128 var_v0;
    void *temp_v0;

    temp_v0 = GetCharacterClass(arg1);
    if (temp_v0 != NULL) {
        var_v0 = (*(s128 *)((char *)(temp_v0) + 0x470));
    } else {
        var_v0 = *(*(s128 **)((char *)(GetLayoutClass(arg1)) + 0x13C));
    }
    *arg0 = var_v0;
}
