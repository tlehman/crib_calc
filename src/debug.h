/* Tobi's debug tools */

#define PRINT_ARRAY(ary, num)           \
        printf("{");                    \
        for(int i=0; i < num; ++i) {    \
            printf("%d", ary[i]);       \
            if(i < num-1) printf(", "); \
        }                               \
        printf("}\n");                  \
