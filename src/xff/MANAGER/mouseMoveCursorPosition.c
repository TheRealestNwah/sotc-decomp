typedef struct {
    float x;
    float y;
} MouseCursor;

extern MouseCursor B_0014DBB8;

void mouseMoveCursorPosition(float dx, float dy)
{
    MouseCursor *cursor = &B_0014DBB8;

    cursor->x += dx;
    cursor->y += dy;
}
