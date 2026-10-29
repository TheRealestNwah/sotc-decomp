extern char *D_00136C00;
extern void *_isysCreateObj(void *, int, int, int, void *, int);
extern void deleteGlobalLightObj(void);
extern void deleteGameLightObj(void);
extern void *GetGlobalLightClass(void *);
extern void *GetGameLightClass(void *);
extern void *memset(void *, int, unsigned int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
void CreateLightColMan(void *heap)
{
    char *manager = D_00136C00;
    int i;
    for (i = 0; i < 128; i++) {
        void *object = _isysCreateObj(heap, 0x19, 0x170, 0x170, deleteGlobalLightObj, 16);
        if (object != 0) {
            void *light = GetGlobalLightClass(object);
            if (light != 0)
                memset(light, 0, 0x150);
            isysAddGroupWithLinkParam(object, manager + 0x514, 0, 0);
        }
    }
    for (i = 0; i < 256; i++) {
        void *object = _isysCreateObj(heap, 0x1A, 0x80, 0x80, deleteGameLightObj, 16);
        if (object != 0) {
            void *light = GetGameLightClass(object);
            if (light != 0)
                memset(light, 0, 0x60);
            isysAddGroupWithLinkParam(object, manager + 0x524, 0, 0);
        }
    }
}
