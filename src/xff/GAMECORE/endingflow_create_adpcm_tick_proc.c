extern void func_00012A40();
extern char rootPtn[];
extern char RO_0017CAB8[];
extern void *_gcCreateChildScriptObj(void *, void *, void *, int, int, int, char *, void *);

void *endingflow_create_adpcm_tick_proc(void *parent)
{
    return _gcCreateChildScriptObj(func_00012A40, 0, rootPtn, 0x4000, 0, 4, RO_0017CAB8, parent);
}
