typedef struct {
    int unk0;
    void *sheet;
    int index;
    int offset;
    int arg;
} SheetEvent;

typedef void (*SheetFunc)(SheetEvent *, int, int);

typedef struct {
    int offset;
    int pad4;
    SheetFunc func;
} SheetField;

typedef struct {
    char pad0[0xC];
    int stride;
    char pad10[8];
    int fieldCount;
    SheetField *fields;
} SheetLayout;

typedef struct {
    char pad0[8];
    SheetLayout *layout;
    int count;
    char *data;
} Sheet;

extern SheetEvent B_00151808;
extern const char RO_00141AD8[];
extern void iosJumpRecoverPoint(const char *, int);

#ifdef NONMATCHING
/* 65 diffs: original keeps the event address inside the loop and spills count/record to the stack */
void sheetFileUnloadCallBack(char *obj)
{
    Sheet *sheet = *(Sheet **)(obj + 0x38);
    int count = sheet->count;
    SheetLayout *layout = sheet->layout;
    int i;
    int j;

    for (i = 0; i < count; i++) {
        char *rec = sheet->data + layout->stride * i;

        for (j = 0; j < layout->fieldCount; j++) {
            SheetField *f = &layout->fields[j];
            SheetFunc func = f->func;
            int off = f->offset;

            if (func != 0) {
                int *e = (int *)(rec + off);
                int v = e[0];

                if (v != 0) {
                    SheetEvent *ev = &B_00151808;

                    ev->offset = off;
                    ev->arg = e[1];
                    ev->unk0 = 0;
                    ev->sheet = sheet;
                    ev->index = i;
                    if (ev == 0)
                        iosJumpRecoverPoint(RO_00141AD8, v);
                    func(ev, v, e[2]);
                }
            }
        }
    }
}
#endif
