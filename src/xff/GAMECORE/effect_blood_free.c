extern void iosFree(void *);

void effect_blood_free(void *allocation)
{
    iosFree(allocation);
}
