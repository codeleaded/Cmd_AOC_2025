#include <stdio.h>
#include "C:\Wichtig\System\Static\Library\Int_Parser.h"
#include "C:\Wichtig\System\Static\Library\Files.h"
#include "C:\Wichtig\System\Static\Library\Math.h"

#define Number  unsigned long long

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

int main(){
    
    char* Data = Files_Read("C:/Wichtig/Hecke/C/Cmd_AOC_2024/01_12_2024/Part2/Data");
    Vector Parts = Parser_StreamtoParts(Data);
    Vector Numbers = Parser_buildTo(&Parts,sizeof(Number),Create,free);

    Number TotalSim = 0;
    for(int i = 0;i<Numbers.size/2;i++){
        Number n = *(Number*)Vector_Get(&Numbers,i*2);
        Number c = Vector_Count(&Numbers,1,Numbers.size,2,&n,Cmp);
        Number Sim = n * c;
        TotalSim += Sim;

        printf("%d -> N1: %llu, Found: %llu,Sim: %llu, TotalSim: %llu |\n",i,n,c,Sim,TotalSim);
    }

    printf("TotalSim: %llu |\n",TotalSim);

    Vector_Free(&Numbers);
    Parser_freeParts(&Parts);
    //Vector_Free(&Parts);
    free(Data);
    
    return 0;
}