#include <iostream>
using namespace std;

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
    return maxLegs;
}
