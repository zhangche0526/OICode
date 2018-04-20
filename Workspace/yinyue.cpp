#include<cstdio>
#include<windows.h>
#define do1 262 
#define re1 294
#define mi1 330
#define fa1 349
#define so1 392
#define la1 440
#define si1 494
#define do2 523
#define re2 578
#define mi2 659
#define fa2 698
#define so2 784
#define la2 880
#define si2 988
#define do3 1046
#define re3 1175
#define mi3 1318
#define fa3 1480
#define so3 1568
#define la3 1760
#define si3 1976
#define sdo1 277
#define sre1 311
#define sfa1 370
#define sso1 415
#define sla1 466
#define sdo2 554
#define sre2 622
#define sfa2 740
#define sso2 831
#define sla2 932
#define sdo3 1046
#define sre3 1245
#define sfa3 1480
#define sso3 1661
#define sla3 1865
#define null 0
const int pai=600;
void beep(int a,double b){
    Beep(a,pai*b);
}
int main(){
    beep(do2,2);
    beep(re2,2);
    beep(mi2,4);
    beep(do2,2);
    beep(re2,2);
    beep(mi2,4);
    beep(mi2,2);
    beep(fa2,2);
    beep(so2,4);
    beep(mi2,2);
    beep(sfa2,2);
    beep(so2,4);
    beep(mi2,0.5);
    beep(fa2,0.5);
    beep(so2,1);
    beep(do3,1);
    beep(si2,1.5);
    beep(so2,0.5);
    beep(la2,3);
    beep(mi2,0.5);
    beep(fa2,0.5);
    beep(so2,1);
    beep(do3,1);
    beep(si2,1.5);
    beep(so2,0.5);
    beep(mi2,3);
    beep(re2,0.5);
    beep(do2,0.5);
    beep(re2,1);
    beep(mi2,1);
    beep(fa2,2);
    beep(so1,2);
    beep(si1,1);
    beep(re2,1);
    beep(do2,3);
    beep(so1,1);
    beep(so1,0.5);
    beep(mi2,0.5);
    beep(so1,0.5);
    beep(mi2,0.5);
    beep(re2,1);
}
