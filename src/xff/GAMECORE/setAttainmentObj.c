extern void DeleteTwoWayLink(void *);
extern void AddTwoWayLinkNext(void *, void *);
extern char *GetLayoutClass(void *);

void setAttainmentObj(char *w, void *obj)
{
    if (obj == *(void **)(w + 0x94))
        return;
    *(int *)(w + 0x90) = 1;
    if (*(int *)(w + 0xA4) != 0) {
        *(int *)(w + 0xA4) = 0;
        DeleteTwoWayLink(w + 0x98);
    }
    *(void **)(w + 0x94) = obj;
    if (obj != 0) {
        AddTwoWayLinkNext(GetLayoutClass(obj) + 0x118, w + 0x98);
        *(int *)(w + 0xA4) = 1;
    }
    *(int *)(w + 0x410) = 0;
    *(int *)(w + 0xA8) = 0;
    *(int *)(w + 0xAC) = 0;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(w + 0xD0) : "memory");
}
