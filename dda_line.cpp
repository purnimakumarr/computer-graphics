// AIM: WRITE A PROGRAM TO IMPLEMENT DDA LINE DRAWING ALGORITHM.

#include<graphics.h>
#include<iostream>
#include<math.h>

using namespace std;

void draw_line(int x0, int y0, int x1, int y1) {
   double dx, dy, m, x, y;

   dy = abs(y1 - y0);
   dx = abs(x1 - x0);
   m = dy / dx;

   // for lines having slope less than or equal to 1
   if(m <= 1) {
      y = y0;

      for(int x = x0; x <= x1; x++) {
      putpixel(x, ceil(y), RED);
      y += m;
      }
   }

   // for lines having slope greater than 1 
   else if(m > 1) {
      x = x0;

      for(int y = y0; y <= y1; y++) {
         putpixel(ceil(x), y, GREEN);
         x += 1/m;
      }
   }
}

int  main() {
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