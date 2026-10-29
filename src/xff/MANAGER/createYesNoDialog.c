typedef struct {
    int unknown0, unknown4;
    const char *yes;
    const char *no;
} DialogDefinition;
typedef struct { const char *text; const char *key; int x, y; } DialogItem;
extern char D_001410D8[];
extern char D_001410E0[];
extern unsigned int strlen(const char *);
extern void func_000D3540(DialogItem *, int, DialogDefinition *, void *);

void createYesNoDialog(DialogDefinition *definition, void *context)
{
    DialogItem items[2] = {
        {definition->yes, D_001410D8, -(strlen(definition->yes) * 7 + 7), 24},
        {definition->no, D_001410E0, 7, 24}
    };
    func_000D3540(items, 2, definition, context);
}
