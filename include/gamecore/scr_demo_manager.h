#ifndef GAMECORE_SCR_DEMO_MANAGER_H
#define GAMECORE_SCR_DEMO_MANAGER_H

/* GAMECORE script demo manager (src/xff/GAMECORE/scr_demo_manager.c). Its
 * Vec4 view stays local to scr_demo_manager.c, since kite_path's Vec4 has a
 * different shape. */

int SCRConditionAtkChackThreeRaySector(void *obj, float a, float b, float c);
int SCRConditionAtkChackThreeRayParallel(void *obj, float a, float b, float c);
void *createScrDemoManager(void *parent);
void setScrDemoMangerFinishCallback(int arg0, int arg1);
void pauseEventDemoManger(int on);
void eventBgmAllClose(void);
void createScrEventDemoManager(int p0, int p1, int p2, int p3, int p4, int flag, int p6, int p7, float fp, int p8, int p9);
void scrDemoInit(void);

#endif /* GAMECORE_SCR_DEMO_MANAGER_H */
