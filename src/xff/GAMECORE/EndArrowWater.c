typedef struct { int used; int a; int arg; int c; int d; } Arrow;
extern Arrow B_0018AD70[];

void EndArrowWater(int arg)
{
    int i;
    for (i = 0; i < 25; i++) {
        if (B_0018AD70[i].arg == arg) {
            B_0018AD70[i].used = 0;
            B_0018AD70[i].arg = 0;
            B_0018AD70[i].c = 0;
            B_0018AD70[i].d = 1;
            return;
        }
    }
}
