// AIM : WRITE A PROGRAM TO CLIP A POLYGON USING SUTHERLAND HODGEMAN ALGORITHM.

#include<iostream>
#include<graphics.h>

using namespace std;

const int MAX_POINTS = 20;
int draw_points[20]; // CONTAINS POINTS OF A POLYGON TO BE DRAWN USING drawpoly() FUNCTION

// CREATES A 1D ARRAY OF THE POINTS TO USE drawpoly() FUNCTION

void getPolyPoints(int array[][2], int size, int result[]) {
  int i, k;
  for(i = 0, k = 0; i < size; i++, k += 2) {
    result[k] = array[i][0];
    result[k + 1] = array[i][1];
  }

  result[k] = array[0][0];
  result[k + 1] = array[0][1];
}

// RETURNS X COORDIANTE OF THE POINT OF INTERSECTION OF TWO LINES

int x_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {

  int num = (x1*y2 - y1*x2) * (x3-x4) - (x1-x2) * (x3*y4 - y3*x4);
  int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);

  return num/den;
}

// RETURNS Y COORDINATE OF THE POINT OF INTERSECTION OF TWO LINES

int y_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {

  int num = (x1*y2 - y1*x2) * (y3-y4) - (y1-y2) * (x3*y4 - y3*x4);
  int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);

  return num/den;
}

void clip(int poly_points[][2], int &poly_size, int x1, int y1, int x2, int y2) {
  int new_points[MAX_POINTS][2], new_poly_size = 0;

  for(int i = 0; i < poly_size; i++) {
        int k = (i+1) % poly_size;
        int ix = poly_points[i][0], iy = poly_points[i][1];
        int kx = poly_points[k][0], ky = poly_points[k][1];
  
        int i_pos = (x2-x1) * (iy-y1) - (y2-y1) * (ix-x1);
  
        int k_pos = (x2-x1) * (ky-y1) - (y2-y1) * (kx-x1);
  
        // CASE 1 : WHEN BOTH POINTS ARE INSIDE (INSIDE-INSIDE)
        if (i_pos < 0  && k_pos < 0)
        {
            new_points[new_poly_size][0] = kx;
            new_points[new_poly_size][1] = ky;
            new_poly_size++;
        }
        // CASE 2: WHEN ONLY FIRST POINT IS OUTSIDE (OUTSIDE-INSIDE)
        else if (i_pos >= 0  && k_pos < 0)
        {
            new_points[new_poly_size][0] = x_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
            new_points[new_poly_size][1] = y_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;
  
            new_points[new_poly_size][0] = kx;
            new_points[new_poly_size][1] = ky;
            new_poly_size++;
        }
        // CASE 3: WHEN ONLY SECOND POINTS IS OUTSIDE (INSIDE-OUTSIDE)
        else if (i_pos < 0  && k_pos >= 0)
        {
            new_points[new_poly_size][0] = x_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
            new_points[new_poly_size][1] = y_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;
        }
        // CASE 4: WHEN BOTH POINTS ARE OUTSIDE (OUTSIDE-OUTSIDE)
        else
        {
          //NO POINTS ARE ADDED
        }
  }

  poly_size = new_poly_size;
  for(int i = 0; i < poly_size; i++) {
    poly_points[i][0] = new_points[i][0];
    poly_points[i][1] = new_points[i][1];
  }
}

void suthHodgClip(int poly_points[][2], int poly_size, int clipper_points[][2], int clipper_size) {
  for(int i = 0; i < clipper_size; i++) {
    int k = (i + 1) % clipper_size;

    clip(poly_points, poly_size, clipper_points[i][0], clipper_points[i][1], clipper_points[k][0], clipper_points[k][1]);
  }

  for(int i = 0; i < poly_size; i++) {
    cout<<"("<<poly_points[i][0]<<","<<poly_points[i][1]<<")";
    cout<<endl;
  }

  int gd = DETECT, gm;
  char data[] = "C://turboc3//bgi";

  initgraph(&gd, &gm, data);

  getPolyPoints(clipper_points, clipper_size, draw_points);
  setcolor(RED);
  drawpoly(clipper_size + 1, draw_points);

  getPolyPoints(poly_points, poly_size, draw_points);
  delay(1000);
  setcolor(DARKGRAY);
  drawpoly(poly_size + 1, draw_points);
}

int main() {
  int poly_size;
  int poly_points[20][2];

  int clipper_size;
  int clipper_points[20][2];

  cout<<"\n==============================================================================\n";
  cout<<"\t\tSUTHERLAND HODGEMAN POLYGON CLIPPING ALGORITHM";
  cout<<"\n==============================================================================";

  cout<<"\nEnter the number of vertices clipping window has: ";
  cin>>clipper_size;
  cout<<"Enter the coordinates of the clipping window:-\n";
  for(int i = 0; i < clipper_size; i++) {
    cout<<"x"<<i<<": ";
    cin>>clipper_points[i][0];
    cout<<"y"<<i<<": ";
    cin>>clipper_points[i][1];
    cout<<endl;
  }

  cout<<"\n\nEnter the number of vertices polygon has: ";
  cin>>poly_size;
  cout<<"Enter the coordinates of the clipping window:-\n";
  for(int i = 0; i < poly_size; i++) {
    cout<<"x"<<i<<": ";
    cin>>poly_points[i][0];
    cout<<"y"<<i<<": ";
    cin>>poly_points[i][1];
    cout<<endl;
  }

  cout<<"\nCLIPPING IS BEING PERFORMED...";
  int gd = DETECT, gm;
  char data[] = "C://turboc3//bgi";

  initgraph(&gd, &gm, data);

  getPolyPoints(clipper_points, clipper_size, draw_points);
  setcolor(RED);
  drawpoly(clipper_size + 1, draw_points);

  getPolyPoints(poly_points, poly_size, draw_points);

  delay(1000);
  setcolor(DARKGRAY);
  drawpoly(poly_size + 1, draw_points);

  suthHodgClip(poly_points, poly_size, clipper_points, clipper_size);

  cout<<"\nCLIPPING IS DONE!";

  getch();
  closegraph();
  
  return 1;
}