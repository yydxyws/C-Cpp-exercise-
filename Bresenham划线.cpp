#include <stdlib.h> 
#include<GLUT/glut.h> 
#include <math.h>


void BresenhamLine(int x1,int y1,int x2,int y2)
{
    int dx,dy,p,x,y;
    x=x1;
    y=y1;    
    dx=x2-x1;
    dy=y2-y1;
    p=2*dy-dx;  //��ʼ�б���p1
    for(;x<=x2;x++)
    {
        getPixel(x,y);
        if(p>=0)
        {
            y++;
            p+=2*(dy-dx);  //pi>=0,y_{i+1}=y_i+1
        }
        else
        {
            p+=2*dy; //p_i<0,y_{i+1}=y_i
        }
    }//for
}
