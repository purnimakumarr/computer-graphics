#include<graphics.h>
#include<iostream>
#include<math.h>

using namespace std;

void draw_line(int x0, int y0, int x1, int y1) {
   double dx, dy, d, x, y, a, b;

   dy = abs(y1 - y0);
   dx = abs(x1 - x0);
   d = 2 * dy - dx; // initial d
   a = 2 * dy;
   b = -2 * dx;

   x = x0;
   y = y0;

  while(x <= x1) {
   // E pixel is chosen
   if(d <= 0) {
    putpixel(ceil(x), ceil(y), BLUE);
    d = d + a;
    x++;
   }

   // NE pixel is chosen 
   else if(d > 0) {
      putpixel(ceil(x), ceil(y), BLUE);
      d = d + a + b;
      x++;
      y++;
    }
  }
}

int main() {
   int x0, y0, x1, y1;

   cout<<"Enter the endpoints of line:-\n";
   cout<<"x0: ";
   cin>>x0;
   cout<<"y0: ";
   cin>>y0;
   cout<<"\nx1: ";
   cin>>x1;
   cout<<"y1: ";
   cin>>y1;
   int gd = DETECT, gm;
   char data[] = "C://turboc3//bgi";

   initgraph(&gd, &gm, data);
   draw_line(x0, y0, x1, y1);
   getch();
   closegraph();
  return 1;
}