#include <stdio.h>
#include "C:\Wichtig\System\Static\Library\Int_Parser.h"
#include "C:\Wichtig\System\Static\Library\Files.h"
#include "C:\Wichtig\System\Static\Library\Math.h"

#define Number  long long

void* Create(char* cstr){
    Number a = Number_Parse(cstr);
    void* Data = malloc(sizeof(Number));
    memcpy(Data,&a,sizeof(Number));
    return Data;
}
int Cmp(void* e1,void* e2){
    Number a = *(Number*)e1;
    Number b = *(Number*)e2;
    return a<b?1:(a>b?-1:0);
}

int isSafe(Number diff,int Sign){
    return !(I64_abs(diff)>3 || diff==0 || I64_sign(diff)!=Sign);
}
int Safe(Vector* v){
    int Count = 0;
    
    Number Before = *(Number*)Vector_Get(v,0);
    int ShouldCmp = 0;
    for(int i = 1;i<v->size;i++){
        Number n = *(Number*)Vector_Get(v,i);
        Number diff = n - Before;
        if(ShouldCmp==0)                    ShouldCmp = I64_sign(diff);
        
        if(!isSafe(diff,ShouldCmp)) Count++;
        
        if(i<v->size-1){
            Number next = *(Number*)Vector_Get(v,i+1);
            Number diff1 = next - Before;
            Number diff2 = next - n;
        
            if(isSafe(diff,ShouldCmp) || (!isSafe(diff1,ShouldCmp) || isSafe(diff2,ShouldCmp))) Before = n;
        }

        if(Count>1) return 0;
    }
    return 1;
}

int main(){
    
    char* Data = Files_Read("C:/Wichtig/Hecke/C/Cmd_AOC_2024/02_12_2024/Part2/Data");
    Vector Parts = Parser2D_StreamtoParts(Data,'\n');
    Vector Numbers = Parser2D_buildTo(&Parts,sizeof(Number),Create,free);

    
    Number TotalSafe = 0;
    for(int i = 0;i<Numbers.size;i++){
        Vector* nums = (Vector*)Vector_Get(&Numbers,i);
        int s = Safe(nums);
        TotalSafe += s;

        printf("%d -> Safe: %llu, TotalSafe: %llu |\n",i,s,TotalSafe);
    }

    printf("TotalSafe: %llu |\n",TotalSafe);

    Vector2D_Free(&Numbers);
    Parser2D_freeParts(&Parts);
    //Vector_Free(&Parts);
    free(Data);
    
    return 0;
}