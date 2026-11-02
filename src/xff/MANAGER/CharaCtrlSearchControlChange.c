extern void *DldSysUndefSymbol;

typedef struct {
    int pad00[2];
    unsigned int from;
    unsigned int to;
} ControlChange;

typedef struct {
    int pad00[3];
    int count;
    ControlChange *changes;
} ControlChangeTable;

static inline void *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

void *CharaCtrlSearchControlChange(void *control, ControlChangeTable *table)
{
    if (table) {
        int n = table->count;
        ControlChange *c = table->changes;
        int i;
        for (i = 0; i < n; i++, c++) {
            if (resourceData(&c->from) == control)
                return resourceData(&c->to);
        }
    }
    return 0;
}
