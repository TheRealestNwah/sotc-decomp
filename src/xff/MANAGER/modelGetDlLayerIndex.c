extern void *modelGetDlLayer(void *model, void *layer);

void *modelGetDlLayerIndex(char *model, int index)
{
    return modelGetDlLayer(model, *(char **)(model + 0x50) + index * 0x120);
}
