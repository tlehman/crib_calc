/* Tobi's debug tools */

#define PRINT_ARRAY(ary, num)            \
        int ai = 0;                      \
        printf("{");                     \
        for(ai=0; ai < num; ++ai) {      \
            printf("%d", ary[ai]);       \
            if(ai < num-1) printf(", "); \
        }                                \
        printf("}\n");

