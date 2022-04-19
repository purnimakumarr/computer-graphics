// AIM: WRITE A PROGRAM TO IMPLEMENT MID-POINT CIRCLE DRAWING ALGORITHM.

#include<graphics.h>
#include<iostream>
#include<math.h>

using namespace std;

void draw_circle(int r, int x0, int y0) {
  double xp = 0, yp = r, d;

  d = 5/4 - r;

  while(xp <= yp) {
  putpixel(x0 + xp, y0 + yp, 7);
	putpixel(x0 + yp, y0 + xp, 7);
	putpixel(x0 - yp, y0 + xp, 7);
	putpixel(x0 - xp, y0 + yp, 7);
	putpixel(x0 - xp, y0 - yp, 7);
	putpixel(x0 - yp, y0 - xp, 7);
	putpixel(x0 + yp, y0 - xp, 7);
	putpixel(x0 + xp, y0 - yp, 7);
  
   // E pixel is chosen
   if(d < 0) {
    d = d + 2 * xp + 3;
    xp++;
   }

   // SE pixel is chosen 
   else if(d >= 0) {
      d = d + 2 * xp - 2 * yp + 5;
      xp++;
      yp--;
    }
  }
}

int main() {
   int radius, x0, y0;

   cout<<"Enter the radius for the circle: ";
   cin>>radius;
   cout<<"Enter the coordinates of center:-\n";
   cout<<"x0: ";
   cin>>x0;
   cout<<"y0: ";
   cin>>y0;

   int gd = DETECT, gm;
   char data[] = "C://turboc3//bgi";

   initgraph(&gd, &gm, data);
   draw_circle(radius, x0, y0);
   getch();
   closegraph();
  return 1;
}