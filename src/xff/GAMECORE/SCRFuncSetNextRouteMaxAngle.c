extern void *getSCRDataCtrlWork(void);
extern void setRouteMinAngle(void *, float);

void SCRFuncSetNextRouteMaxAngle(float fparg0) {
    setRouteMinAngle(getSCRDataCtrlWork(), (180.0f - fparg0) * 0.0174532925f);
}
