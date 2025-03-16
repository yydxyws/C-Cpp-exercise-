/*
double xl,xr,yt,yb;//窗口位置

void Cohen_Sutherland(double x0,double y0,double x2,double y2)
{
    int c,c0,c1;
    double x,y;
    c0=makecode(x0,y0);c1=makecode(x2,y2);

    while (c0!=0||c1!=0)
    {
        if (c0&c1!=0) return;
        c=c0;
        if (c==0) c=c1;
        if (c&1==1)
        {
            y=y0+(y2-y0)*(xl-x0)/(x2-x0);
            x=xl;
        }
        else if(c&2==2)
        {
            y=y0+(y2-y0)*(xr-x0)/(x2-x0);
            x=xr;
        }
        else if(c&4==4)
        {
            x=x0+(x2-x0)*(yb-y0)/(y2-y0);
            y=yb;
        }
        else if(c&8==8)
        {
            x=x0+(x2-x0)*(yt-y0)/(y2-y0);
            y=yt;
        }

        if (c==c0)
        {
            x0=x;
            y0=y;
            c0=makecode(x,y);
        }
        else
        {
            x2=x;
            y2=y;
            c1=makecode(x,y);
        }
    }
    showline(x0,y0,x2,y2);
}

int makecode(double x,double y)
{
    int c=0;
    if (x<xl) c=1;
    else if(x>xr) c=2;
    
    if (y<yb) c=c+4;
    else if (y>yt) c=c+8;
    return c; 
}
*/
double x1, y1, x2, y2;

double xl, xr, yt, yb; //窗口的四个位置
void Cohen_Sutherland(double x1, y1, x2, y2)//给定直线的两个端点
{  int c, c1, c2;//两个端点所在的区域编码，和中介编码
  double x, y;//窗口边界截点
  makecode(x1, y1,c1);   
  makecode(x2, y2, c2);//获得端点的区域编码
  while (c1!=0 || c2!=0)//如果二者均为零，在窗口内，不进入循环，直接return
    { if (c1&c2!=0) 
        {
            showline(x1, y1, x2, y2);
            return;
        }//如果二者按位与为0，完全在窗口外，画图，结束。
     c=c1; //令中介编码存放点1区域
     if (c==0) c=c2;//点1若在窗口内，令中介编码存放点2区域（点2不为零）
     if (c&1) {y=y1+(y2-y1)*(xl-x1)/(x2-x1); x=xl;}//点1在左侧列，(x,y)为左边界交点
     else if (c&2) {y=y1+(y2-y1)*(xr-x1)/(x2-x1); x=xr;}//点1在右侧列，(x,y)为右边界交点
     else if (c&4) {x=x1+(x2-x1)*(yb-y1)/(y2-y1); y=yb;}//点1在下侧列，(x,y)为下边界交点
     else if (c&8) {x=x1+(x2-x1)*(yt-y1)/(y2-y1); y=yt;}//点1在上侧列，(x,y)为上边界交点
      if (c==c1)
      {
        showline(x1, y1, x2, y2); //点1到与之最近的边界点绘制
        x1=x; y1=y; makecode(x, y, c1);//变更点1坐标
        }
      else
      {
        showline(x1, y1, x2, y2); //点1到与之最近的边界点绘制
        x2=x; y2=y; makecode(x, y, c2);//变更点2坐标
        }
  }
    return;
  }
  
  int makecode(double x,double y)
{
    int c=0;
    if (x<xl) c=1;//在边界线上的不属于上下左右侧
    else if(x>xr) c=2;
    
    if (y<yb) c=c+4;
    else if (y>yt) c=c+8;
    return c; 
}