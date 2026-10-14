extern int entry_new_letter_type(void *);
extern int D_00139F60;
extern int D_00139F64;
extern unsigned char RO_00141E40[];
extern unsigned char RO_00141E58[];

void InitDamageLetter(void) {
    D_00139F60 = entry_new_letter_type(&RO_00141E40);
    D_00139F64 = entry_new_letter_type(&RO_00141E58);
}
