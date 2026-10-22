extern void *B_000C2750;
extern void open_letter_post(void *);
extern void *get_next_letter_in_post(void *);
extern int get_reference_letter_type(void *);
extern int get_letter_receiver_obj_group(void *);
extern unsigned char *isysGetLetterObj(unsigned char *);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void discard_all_letter_in_post(void *);
extern void close_letter_post(char *);
extern int func_0001BE30(unsigned char *, void *, int *);

void doit_letter_manager(void)
{
    void *letter;
    int *type;
    void **link;
    unsigned char *object;
    unsigned char *receiver;
    int result;

    open_letter_post(B_000C2750);
    while ((letter = get_next_letter_in_post(B_000C2750)) != 0) {
        type = (int *)get_reference_letter_type(letter);
        if (*type == 0) {
            receiver = isysGetLetterObj((unsigned char *)get_letter_receiver_obj_group(letter));
            if (receiver != 0) {
                func_0001BE30(receiver, letter, type);
            } else {
                __asm__("break 0");
            }
        } else {
            object = 0;
            for (link = isysGroupForFirst((void *)get_letter_receiver_obj_group(letter), 0);
                 link != 0; link = isysGroupForNext(link, 0)) {
                object = *link;
                receiver = isysGetLetterObj(object);
                if (receiver != 0) {
                    result = func_0001BE30(receiver, letter, type);
                    if (result == 1 && *type == result) {
                        break;
                    }
                    continue;
                }
                __asm__("break 0");
            }
            if (object != 0) {
                isysGroupForExit(object, 0);
            }
        }
    }
    discard_all_letter_in_post(B_000C2750);
    close_letter_post(B_000C2750);
}
