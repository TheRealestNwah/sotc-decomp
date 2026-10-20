/* The owner word is part of the same DC aggregate as its flag bits. */
typedef struct {
    char pad[0x170];
    unsigned long first : 1;
    unsigned long second : 1;
    unsigned long rest : 62;
    char pad178[0xC];
    int owner;
    char pad188[8];
} DC;
extern void *_isysCreateObj(void *, int, int, int, int, int);
static void func_00012AD0(void);
static void func_00012AD8(void);
extern void isysSetObjImmediateDeleteFunc(void *, int);
extern void *iosMallocAlign(void *, int, int);
extern int isysAddGroupWithLinkParam(void *, void *, int, int);
extern char B_00065008[];
int *iosCreateDC(void *heap, int count)
{
    int bytes = count * 400;
    int *obj = _isysCreateObj(heap, 31, 0x24, bytes + 0x33, (int)func_00012AD0, 16);
    DC *dc;
    isysSetObjImmediateDeleteFunc(obj, (int)func_00012AD8);
    obj[8] = count;
    dc = iosMallocAlign((void *)obj[0], bytes, 16);
    obj[7] = (int)dc;
    dc->owner = (int)obj;
    ((DC *)obj[7])->first = 0;
    ((DC *)obj[7])->second = 0;
    isysAddGroupWithLinkParam(obj, B_00065008, 0, 0);
    return obj;
}