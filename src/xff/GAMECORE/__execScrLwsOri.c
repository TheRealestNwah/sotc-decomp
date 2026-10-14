extern void ExecScriptLwsOrientClass(void *, void *, void *, float, float);
extern float ViewIntervalClip(void *, void *, float);
extern void *get_main_cameraman_camera_obj(void);
struct OrientationGlobalsView {
 char pad00[0x188];
  float interval;
 char pad18C[0x1E4];
 char context[0];
};
extern struct OrientationGlobalsView gcGlobalVar;

void __execScrLwsOri(void *actor)
{
    float interval;

    interval = ViewIntervalClip(actor, get_main_cameraman_camera_obj(),
                                gcGlobalVar.interval);
    ExecScriptLwsOrientClass(actor, get_main_cameraman_camera_obj(),
                            gcGlobalVar.context, interval, 1.0f / interval);
}
