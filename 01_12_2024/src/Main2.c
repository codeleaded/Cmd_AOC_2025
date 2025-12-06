#include <stdio.h>
#include "/home/codeleaded/System/Static/Container/Vector.h"
#include "/home/codeleaded/System/Static/Library/Files.h"
#include "/home/codeleaded/System/Static/Library/CStr.h"

#define DIRECTION_L     0
#define DIRECTION_R     1

typedef struct Rotation {
    int dir : 1;
    int value : 31;
} Rotation;


// Vector<CStr> Parts
Vector Numbers_Build(Vector* Parts){
    Vector ret = Vector_New(sizeof(Rotation));
    for(int i = 0;i<Parts->size;i++){
        CStr cstr = *(CStr*)Vector_Get(Parts,i);
        CStr real = CStr_ChopEndTo(cstr,'\r');

        const char dir = cstr[0];
        const int value = (int)Number_Parse(real + 1);

        printf("S: %s -> %d,%d\n",real,dir,value);

        Vector_Push(&ret,(Rotation[]){{
           .dir = dir=='L' ? DIRECTION_L : DIRECTION_R,
           .value = value
        }});

        CStr_Free(&real);
    }
    return ret;
}


int main(){
    
    char* Data = Files_Read("./data/Data");
    printf("Data:\n%s\n",Data);

    Vector Parts = CStr_ChopDown(Data,'\n');
    Vector Numbers = Numbers_Build(&Parts);

    int overs = 0;
    int zeros = 0;
    int angle = 50;
    for(int i = 0;i<Numbers.size;i++){
        Rotation* r = (Rotation*)Vector_Get(&Numbers,i);
        const int rotation = r->value * (r->dir==DIRECTION_L ? -1 : 1);
        const int preangle = angle;
        angle += rotation;

        const int overrot = I64_Abs(rotation) / 100;
        overs += overrot > 0 ? overrot : (angle <= 0 || angle >= 100 ? 1 : 0);
        angle = angle % 100;

        if(angle < 0) angle += 100;

        //if(angle == 0) zeros++;

        printf("Angle: %d + %d = %d |    \t%d,%d\n",preangle,rotation,angle,zeros,overs);
    }

    printf("Zeros: %d, Overs: %d -> %d\n",zeros,overs,zeros + overs);

    Vector_Free(&Numbers);

    for(int i = 0;i<Parts.size;i++){
        CStr* cstr = (CStr*)Vector_Get(&Parts,i);
        CStr_Free(cstr);
    }
    Vector_Free(&Parts);
    free(Data);
    
    return 0;
}