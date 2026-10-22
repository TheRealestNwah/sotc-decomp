extern char *GetLayoutClass(unsigned char *);
extern void *GetCharacterClass(void *);
extern float *GetGeometryPointerSurfacePlane(char *);
float *GAMEUTIL_get_parent_plane(unsigned char *object, int characterPlane)
{
    char *layout = GetLayoutClass(object);
    if (layout && *(int *)(layout + 0x124)) {
        if (characterPlane) {
            char *character = GetCharacterClass(object);
            if (character) return (float *)(character + 0x6A0);
        }
        return GetGeometryPointerSurfacePlane(layout + 0xC0);
    }
    return 0;
}
