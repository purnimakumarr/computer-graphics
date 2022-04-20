// AIM: WRITE A PROGRAM TO CLIP A LINE USING COHEN-SUTHERLAND LINE CLIPPING ALGORITHM.

#include<iostream>
#include<stdio.h>
#include<graphics.h>

using namespace std;

typedef unsigned int outcode;
enum b {f, t};
enum {
  top = 1,
  bottom = 2, 
  _right = 4, 
  _left = 8
};

outcode compoutcode(double x, double y, double xmin, double xmax, double ymin, double ymax) {
  outcode code = 0;

  if(y > ymax) {
    code |= top;
  } else if(y < ymin) {
    code |= bottom;
  }
  if(x > xmax) {
    code |= _right;
  } else if(x < xmin) {
    code |= _left;
  }

  return code;
}

void cohen(double x0, double y0, double x1, double y1, double xmin, double xmax, double ymin, double ymax) {
  outcode outcode0, outcode1, outcodeout;
  b accept = f, done = f;
  outcode0 = compoutcode(x0, y0, xmin, xmax, ymin, ymax);
  outcode1 = compoutcode(x1, y1, xmin, xmax, ymin, ymax);

  do {
    if(outcode0 == 0 && outcode1 == 0) {
      accept = t;
      done = t;
    } else if(outcode0 & outcode1) {
      done = t;
    } else {
      double x, y;
      double m;
      m = (y1 - y0) / (x1 - x0);
      outcodeout = outcode0?outcode0:outcode1;
      
      if(outcodeout & top) {
        x = x0 + (ymax - y0) / m;
        y = ymax;
      } else if(outcodeout & bottom) {
        x = x0 + (ymin - y0) / m;
        y = ymin;
      } else if(outcodeout & _right) {
        y = y0 + (xmax - x0) * m;
        x = xmax;
      } else if(outcodeout & _left) {
        y = y0 + (xmin - x0) * m;
        x = xmin;
      }

      if(outcodeout == outcode0) {
        x0 = x;
        y0 = y;
        outcode0 = compoutcode(x0, y0, xmin, xmax, ymin, ymax);
      } else {
        x1 = x;
        y1 = y;
        outcode1 = compoutcode(x1, y1, xmin, xmax, ymin, ymax);
      }
    }
  }while(done == f);

  if(accept) {
    line(x0, y0, x1, y1);
  }
}

int main() {
  double x[10], y[10];
  double xmin, xmax, ymin, ymax;
  int choice = 'y';

  int c = 0;
  
  cout<<"===============================================================================";
  cout<<"\n\t\tCOHEN-SUTHERLAND LINE CLIPPING ALGORITHM";
  cout<<"\n=============================================================================";
  cout<<"\nNote:-";
  cout<<"\n\tYou can only clip upto 5 line against a clipping window.";

  int i = 0;

  cout<<"\nEnter the coordinates of the clipping window:-\n";
  cout<<"xmin: ";
  cin>>xmin;
  cout<<"xmax: ";
  cin>>xmax;
  cout<<"ymin: ";
  cin>>ymin;
  cout<<"ymax: ";
  cin>>ymax;

  for( ; (choice == 'Y' || choice == 'y') && i < 10; i += 2) {
    cout<<"\nEnter the coordinates for the line:-\n";
    cout<<"x0: ";
    cin>>x[i];
    cout<<"y0: ";
    cin>>y[i];
    cout<<"x1: ";
    cin>>x[i + 1];
    cout<<"y1: ";
    cin>>y[i + 1];

    cout<<"\n\nDo you want to enter coordinates for another line? ";
    cin>>choice;
  }

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"C:\\TURBOC3\\BGI");
  setbkcolor(4);
  rectangle(xmin, ymin, xmax, ymax);
  for(int j = 0; j < i; j += 2) {
    line(x[j], y[j], x[j + 1], y[j + 1]);
  }

  delay(100);

  initgraph(&gd, &gm, (char*)"C:\\TURBOC3\\BGI");
  setbkcolor(6);
  setcolor(RED);
  setlinestyle(DOTTED_LINE, 1, 1);
  
  rectangle(xmin, ymin, xmax, ymax);
  for(int j = 0; j < i; j += 2) {
    cohen(x[j], y[j], x[j + 1], y[j + 1], xmin, xmax, ymin, ymax);
    c++;
  }

  getch();
  closegraph();
  return 1;
}