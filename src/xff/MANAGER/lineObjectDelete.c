extern void isysRequestDeleteObj(void *);

void lineObjectDelete(void *object)
{
    isysRequestDeleteObj(object);
}
