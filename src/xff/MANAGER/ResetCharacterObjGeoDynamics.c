#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
extern s128 ZeroVector;
extern char *GetCharacterClass(void *);

static inline void zero(void *v)
{
    __asm__ __volatile__("sq $0, 0(%0)" : : "r"(v) : "memory");
}

void ResetCharacterObjGeoDynamics(void *object)
{
    char *c = GetCharacterClass(object);

    *(int *)(c + 0xA20) = 0;
    *(char *)(c + 0x10A1) = 0;
    *(char *)(c + 0xC96) = 0;
    zero(c + 0xAB0);
    *(char *)(c + 0xC95) = 0;
    zero(c + 0x9D0);
    zero(c + 0x30);
    *(s128 *)(*(char * volatile *)(c + 0x19C) + 0x0) = *(s128 *)(c + 0x30);
    *(s128 *)(*(char * volatile *)(c + 0x19C) + 0x10) = *(s128 *)(c + 0x30);
    *(unsigned char *)(*(char * volatile *)(c + 0x19C) + 0x8E) = *(unsigned char *)(c + 0x124);
    *(s128 *)(*(char * volatile *)(c + 0x19C) + 0x30) = ZeroVector;
    *(int *)(*(char * volatile *)(c + 0x19C) + 0x88) = 0;
    zero(c + 0x880);
    zero(c + 0x870);
    zero(c + 0x8B0);
    zero(c + 0x8E0);
}
#endif
