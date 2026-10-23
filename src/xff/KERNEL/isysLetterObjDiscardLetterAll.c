static inline unsigned char *getLetterObj(unsigned char *o)
{
    switch (o[8]) {
    case 6:
    case 9:
    case 11:
    case 13:
    case 22:
        return o;
    case 7:
    case 8:
    case 10:
    case 12:
    case 14 ... 21:
        break;
    }
    return 0;
}

extern void open_letter_post(void *);
extern void discard_all_letter_in_post(void *);
extern void close_letter_post(void *);

void isysLetterObjDiscardLetterAll(unsigned char *object)
{
    unsigned char *letter = getLetterObj(object);
    if (letter != 0) {
        void *post = *(void **)(getLetterObj(object) + 0x1C);
        open_letter_post(post);
        discard_all_letter_in_post(post);
        close_letter_post(post);
    }
}
