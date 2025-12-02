#include <stdio.h>
#include "/home/codeleaded/System/Static/Container/Vector.h"
#include "/home/codeleaded/System/Static/Library/Files.h"
#include "/home/codeleaded/System/Static/Library/CStr.h"

Vector Numbers_Build(){

}


int main(){
    
    char* Data = Files_Read("../data/Data");
    
    Vector Parts = CStr_ChopDown(Data,'\n');
    Vector Numbers = Numbers_Build(&Parts);

    Vector_BubbleSortStep(&Numbers,0,Numbers.size-1,2,Cmp);
    Vector_BubbleSortStep(&Numbers,1,Numbers.size,2,Cmp);

    Number TotalDiff = 0;
    for(int i = 0;i<Numbers.size/2;i++){
        Number n1 = *(Number*)Vector_Get(&Numbers,i*2);
        Number n2 = *(Number*)Vector_Get(&Numbers,i*2+1);

        Number nmin = I64_min(n1,n2);
        Number nmax = I64_max(n1,n2);

        Number Diff = nmax - nmin;
        TotalDiff += Diff;

        printf("%d -> N1: %llu, N2: %llu, Diff: %llu, TotalDiff: %llu |\n",i,n1,n2,Diff,TotalDiff);
    }

    printf("TotalDiff: %llu |\n",TotalDiff);

    Vector_Free(&Numbers);
    Parser_freeParts(&Parts);
    //Vector_Free(&Parts);
    free(Data);
    
    return 0;
}