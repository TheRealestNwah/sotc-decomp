int windowCheckCursorInRect(char *window, float *rect, float *cursor)
{
    float x = rect[0];
    if (window == 0) {
        float cursorY;
        float cursorX;
        return x <= (cursorX = cursor[0]) && rect[1] <= (cursorY = cursor[1])
            && cursorX < x + rect[2] && cursorY < rect[1] + rect[3];
    }
    else {
        float y;
        float shiftedX = x + *(float *)(window + 0x198);
        return shiftedX <= cursor[0] && (y = rect[1] + *(float *)(window + 0x19C)) <= cursor[1]
            && cursor[0] < shiftedX + rect[2] && cursor[1] < y + rect[3];
    }
}
