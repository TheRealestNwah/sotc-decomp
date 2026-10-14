extern void *GetLayoutClass(void *);

typedef int s128 __attribute__((mode(TI)));
#define NULL ((void *)0)
extern s128 All1Vector;

void GAMEUTIL_get_object_scale(s128 *arg0, void *arg1) {
    void *temp_v0;

    if (arg1 != NULL) {
        temp_v0 = GetLayoutClass(arg1);
        if (temp_v0 != NULL) {
            *arg0 = (*(s128 *)((char *)(temp_v0) + 0x90));
            return;
        }
    }
    *arg0 = All1Vector;
}
