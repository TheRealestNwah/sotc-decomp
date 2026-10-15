extern char B_00065008[];
extern void _isysDeleteGroup(void *, void *, int);
extern void isysRequestDeleteObj(void *);

void iosReleaseDC(void *dc)
{
    if (dc != 0) {
        _isysDeleteGroup(dc, B_00065008, 0);
        isysRequestDeleteObj(dc);
    }
}
