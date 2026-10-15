typedef struct { int key; int a; int *sym; } Ent;
extern char B_00054398[];
extern Ent *SearchStrHashKey(void *, int);

int isysSearchSymbol(int *out, int name)
{
    Ent *e;
    if (name == 0) {
        *out = 0;
        return 1;
    }
    e = SearchStrHashKey(B_00054398, name);
    if (e != 0)
        *out = e->sym[1];
    return e != 0;
}
