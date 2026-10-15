struct CursorPosition {
    float x;
    float y;
};

extern struct CursorPosition B_0014DBB8;

void mouseSetCursorPosition(float x, float y)
{
    B_0014DBB8.x = x;
    B_0014DBB8.y = y;
}
