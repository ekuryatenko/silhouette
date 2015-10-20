#include <iostream>
#include "gbufferedimage.h"
#include "gobjects.h"
using namespace std;

int countMassCenters(auto bwModel, int ySize, int xSize){
    double cm[xSize];
    for(int x=0;x<xSize;x++){
        cm[x]=0;
        for(int y=0; y<(ySize*0.75); y++){
            //sumPoLinii(y,x)
            double tmpSum=0;
            for(int z=0;z<xSize;z++){
                if(bwModel[y][z]=='1'){
                    double zx;
                    if(z==x)
                        zx=1;
                    else
                        zx=1/((z-x));
                    if(zx<0)
                        zx=-zx;
                    tmpSum+=zx;
                }
            }
            cm[x]+=tmpSum;
        }
    }
    // count first derivative
    double dcm[xSize]; int dx=10;
    for(int x=0;x<(xSize-dx);x++){
        double y1=cm[x];
        double y2=cm[x+dx];
        dcm[x]=y2-y1;
    }
    // look for siluets
    double sum=dcm[0], oldSum=sum;
    int counterOfAnotherDirection=0, lastDirection=0;
    int sil=0;
    for(int x=1;x<xSize-dx;x++){
        sum+=dcm[x];
        if(sum>oldSum){
            if(lastDirection==0)
                lastDirection=1;
            else if(lastDirection==-1){
                counterOfAnotherDirection++;
                if(counterOfAnotherDirection==5){
                    counterOfAnotherDirection=0;
                    lastDirection=1;
                }
            }
        } else {
            if(lastDirection==1)
                counterOfAnotherDirection++;
            if(counterOfAnotherDirection==5){
                counterOfAnotherDirection=0;
                lastDirection=-1;
                sil++;
            }
        }
        oldSum=sum;
    }
    return sil;
}

int countObjLegs(auto bwModel, int ySize, int xSize){
    // look for legs at 5%, 10%, 15%, 20%, 25% from bottom of the object
    int maxLegs=0;
    for(int i=1;i<=5;i++){
        int y=ySize*(1-(double)i*5/100);
        int legs=0;
        int x=0;
        while(x<xSize){
            if(bwModel[y][x]=='1'){
                int startX=x;
                while((x<xSize)&&(bwModel[y][x]=='1'))
                    x++;
                int legWide=x-startX;
                if(legWide>5) // to narrow (less 5 px) do not count
                    legs++;
            }
            x++;
        }
        if(maxLegs<legs)
            maxLegs=legs;
    }
    cout << "legs: " << maxLegs << endl;
    
    int mc=countMassCenters(bwModel,ySize,xSize);
    cout << "mass centers: " << mc << endl;
    
    return maxLegs;
}
