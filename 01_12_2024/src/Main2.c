#include <stdio.h>
#include "/home/codeleaded/System/Static/Container/Vector.h"
#include "/home/codeleaded/System/Static/Library/Files.h"
#include "/home/codeleaded/System/Static/Library/CStr.h"

#define DIRECTION_L     0
#define DIRECTION_R     1

typedef struct Rotation {
    int dir;
    int value;
} Rotation;

// Vector<CStr> Parts
Vector Numbers_Build(Vector* Parts){
    Vector ret = Vector_New(sizeof(Rotation));
    for(int i = 0;i<Parts->size;i++){
        CStr cstr = *(CStr*)Vector_Get(Parts,i);
        CStr real = CStr_ChopEndTo(cstr,'\r');

        const char dir = cstr[0];
        const int value = (int)Number_Parse(real + 1);

        printf("S: %s -> (%c)%d\n",real,dir,value);

        Vector_Push(&ret,(Rotation[]){{
           .dir = dir=='L' ? DIRECTION_L : DIRECTION_R,
           .value = value
        }});

        CStr_Free(&real);
    }
    return ret;
}

int clicking_L(int angle,int rotation,int* clicks){
    angle -= rotation;
    
    while(angle < 0){
        angle += 100;
        (*clicks)++;
    }
    if(angle == 0){
        (*clicks)++;
    }
    return angle;
}
int clicking_R(int angle,int rotation,int* clicks){
    angle += rotation;

    while(angle > 100){
        angle -= 100;
        (*clicks)++;
    }
    if(angle == 0){
        (*clicks)++;
    }
    return angle;
}

int main(){
    
    char* Data = Files_Read("./data/Data");
    printf("Data:\n%s\n",Data);

    Vector Parts = CStr_ChopDown(Data,'\n');
    Vector Numbers = Numbers_Build(&Parts);

    int clicks = 0;
    int angle = 50;
    
    for(int i = 0;i<Numbers.size;i++){
        Rotation* r = (Rotation*)Vector_Get(&Numbers,i);
        const int preangle = angle;
        
        if(r->dir == DIRECTION_L)       angle = clicking_L(angle,r->value,&clicks);
        else if(r->dir == DIRECTION_R)  angle = clicking_R(angle,r->value,&clicks);
        else                            printf("Unknown direction: %d\n",r->dir);
        
        printf("Angle: %d + (%c)%d = %d (%d)\n",preangle,r->dir == DIRECTION_L ? 'L' : 'R',r->value,angle,clicks);
    }

    printf("Clicks: %d\n",clicks);

    Vector_Free(&Numbers);

    for(int i = 0;i<Parts.size;i++){
        CStr* cstr = (CStr*)Vector_Get(&Parts,i);
        CStr_Free(cstr);
    }
    Vector_Free(&Parts);
    free(Data);
    
    return 0;
}