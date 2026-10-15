typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroVector;

typedef struct {
    s128 pos;
    int a;
    int b;
} AnimalLayout;

void AI_InitAnimalLayout(AnimalLayout *layout)
{
    layout->pos = ZeroVector;
    layout->a = 0;
    layout->b = 0;
}
