typedef struct { int a; int b; void *buf; int c; } RecordInfo;
extern void GAMEUTIL_destructor_record_info(RecordInfo *);

void CAM_destructor_target(char *target)
{
    GAMEUTIL_destructor_record_info((RecordInfo *)(target + 0x2CC));
}
