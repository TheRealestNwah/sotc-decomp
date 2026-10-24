typedef struct {
    char button[0x28];
} ControlButton;

typedef struct {
    char pad0[0x10];
    ControlButton *button;
} ControlOwner;

extern char gcGlobalVar[];

void setDefaultPlayerControlButton(ControlOwner *owner)
{
    *(ControlButton *)(gcGlobalVar + 0x314) = *owner->button;
}
