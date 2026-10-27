typedef struct {
    char pad0[0xC8];
} CameraLwsAnimation;

typedef struct {
    char pad0[0xC];
    int count;
    CameraLwsAnimation *animations;
} CameraLwsSegment;

extern int end_camera_lws_animation_by_paramID(int param_id);
void free_camera_lws_animation_segment(CameraLwsSegment *seg)
{
    if (seg != 0) {
        int n = seg->count;
        CameraLwsAnimation *anim = seg->animations;

        if (n > 0) {
            CameraLwsAnimation *p = anim;
            int i = n;

            do {
                (void)end_camera_lws_animation_by_paramID((int)p);
                p++;
            } while (--i);
        }
    }
}
