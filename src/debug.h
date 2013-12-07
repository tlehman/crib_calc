/* tlehman's debug tools */

#ifndef _debug_h_
#define _debug_h_
void print_array(int ary[], int num)
{
    int i;
    printf("{");
    for(i = 0; i < num; ++i) {
        printf("%d", ary[i]);
        if(i < num-1) printf(", ");
    }
    printf("}\n");
}

#endif
