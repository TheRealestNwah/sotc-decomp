typedef struct {
    char pad0[0x98];
} PathInfo;

typedef struct {
    char pad0[0x3C50];
    int path;
} PathOwner;

extern PathInfo B_001A57E8[];

PathInfo *getPathInfo(PathOwner *owner)
{
    return &B_001A57E8[owner->path];
}
