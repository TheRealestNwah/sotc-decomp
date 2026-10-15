typedef struct { int *a; char *d; int dc; } Win;
extern void iosReleaseDC(int);

void windowDelete(Win *w)
{
    void (*f)(int, char *);
    if (w == 0)
        return;
    f = *(void (**)(int, char *))(w->d + 0x3F8);
    if (f != 0)
        f(*w->a, w->d);
    iosReleaseDC(w->dc);
}
