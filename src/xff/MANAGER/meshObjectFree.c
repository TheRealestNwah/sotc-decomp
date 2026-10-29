extern void isysRequestDeleteObj(void *);

void meshObjectFree(void *object)
{
    isysRequestDeleteObj(object);
}
