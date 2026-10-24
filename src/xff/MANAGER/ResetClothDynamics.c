typedef int s128 __attribute__((mode(TI)));
extern char *GetLayoutClass(unsigned char *);
static inline void zeroVector(s128 *v)
{
    __asm__ __volatile__("sq $0, 0(%0)" : : "r"(v) : "memory");
}
void ResetClothDynamics(unsigned char *object)
{
    char *layout = GetLayoutClass(object);
    if (*(int *)(layout + 0x180)) {
        char *cloth = *(char **)(layout + 0x178);
        int count = *(short *)(cloth + 4);
        char *instance = *(char **)cloth;
        if (count > 0) {
            int remaining = count;
            do {
                char *definition = *(char **)instance;
                char *chain = *(char **)(instance + 0xC);
                int i;
                for (i = 0; i < *(int *)(definition + 4); i++) {
                    s128 *v = *(s128 **)(chain + 8);
                    int j;
                    for (j = 0; j < *(int *)(definition + 8); j++) {
                        zeroVector(v);
                        v++;
                    }
                    chain += 0x18;
                }
                instance += 0x90;
            } while (--remaining);
        }
    }
}
