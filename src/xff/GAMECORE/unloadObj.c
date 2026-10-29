extern void isysRequestDeleteObj(void *);

void unloadObj(void *object)
{
    isysRequestDeleteObj(object);
}
