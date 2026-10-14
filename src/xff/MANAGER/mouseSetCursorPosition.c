struct CursorPosition {
    volatile float x;
    volatile float y;
};

extern struct CursorPosition B_0014DBB8;

void mouseSetCursorPosition(float x, float y)
{
    B_0014DBB8.y = y;
    B_0014DBB8.x = x;
}
