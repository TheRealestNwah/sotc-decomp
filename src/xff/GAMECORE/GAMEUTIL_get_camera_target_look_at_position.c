typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 q;
} Vec4;

typedef struct {
    char pad0[0x134];
    Vec4 *pos;
} LayoutClass;

extern void GAMEUTIL_get_node_posi_by_id(Vec4 *, int, int);
extern LayoutClass *GetLayoutClass(int);
extern char *GetScriptCharacterClass(int);

void GAMEUTIL_get_camera_target_look_at_position(Vec4 *pos, int id)
{
    char *chara = GetScriptCharacterClass(id);

    if (chara != 0) {
        GAMEUTIL_get_node_posi_by_id(pos, id, *(int *)(chara + 0x11F0));
        return;
    }
    *pos = *GetLayoutClass(id)->pos;
}
