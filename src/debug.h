/* tlehman's debug tools */

#define PRINT_ARRAY(ary, num)           \
    do {                                \
        int i;                          \
        printf("{");                    \
        for(i = 0; i < num; ++i) {      \
            printf("%d", ary[i]);       \
            if(i < num-1) printf(", "); \
        }                               \
        printf("}\n");                  \
    } while(0);

