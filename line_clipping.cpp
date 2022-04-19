// AIM: WRITE A PROGRAM TO CLIP A LINE USING COHEN-SUTHERLAND LINE CLIPPING ALGORITHM.

#include<iostream>
#include<stdio.h>
#include<graphics.h>

using namespace std;

typedef unsigned int outcode;
enum boolean {f, t};
enum {
  top = 0x1,
  bottom = 0x2, 
  _right = 0x4, 
  _left = 0x8
};

outcode compoutcode(double x, double y, double xmin, double xmax, double ymin, double ymax) {
  outcode code = 0;

  if(y > ymax) {
    code |= top;
  } else if(y < ymin) {
    code |= bottom;
  } else if(x > xmax) {
    code |= _right;
  } else if(x < xmin) {
    code |= _left;
  }

  return code;
}

void cohen(double x0, double y0, double x1, double y1, double xmin, double xmax, double ymin, double ymax) {
  outcode outcode0, outcode1, outcodeout;
  boolean accept = f, done = f;
  outcode0 = compoutcode(x0, y0, xmin, xmax, ymin, ymax);
  outcode1 = compoutcode(x1, y1, xmin, xmax, ymin, ymax);

  do {
    if(outcode0 | outcode1) {
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
        y = y0 + (xmax - x0) / m;
        x = xmax;
      } else {
        y = y0 + (xmin - x0) / m;
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
  int x[10], y[10];
  int xmin, xmax, ymin, ymax;
  char* choice;
  
  cout<<"========================================================================";
  cout<<"\n\t\tCOHEN-SUTHERLAND LINE CLIPPING ALGORITHM IMPLEMENTED USING C++";
  cout<<"========================================================================";
  cout<<"\nNote:-";
  cout<<"\n\tYou can only clip upto 5 line against a clipping window.";

  int i = 0;

  do {
    cout<<"Enter the coordinates for the line: ";
    cout<<"x0: ";
    cin>>x[i];
    cout<<"y0: ";
    cin>>y[i];
    cout<<"x1: ";
    cin>>x[i + 1];
    cout<<"y1: ";
    cin>>y[i + 1];

    i += 2;

    cout<<"\n\nDo you want to enter coordinated for another line? ";
    cin>>choice;
  }while((choice == "Y" || choice == "y") && i < 10);

  // cout<<"Enter the coordinates for the line: ";
  // cout<<"x0: ";
  // cin>>x0;
  // cout<<"y0: ";
  // cin>>y0;
  // cout<<"x1: ";
  // cin>>x1;
  // cout<<"y1: ";
  // cin>>y1;
  // cout<<"Enter the coordinated for another line: ";
  // cout<<"x0: ";
  // cin>>x2;
  // cout<<"y0: ";
  // cin>>y2;
  // cout<<"x1: ";
  // cin>>x3;
  // cout<<"y1: ";
  // cin>>y3;

  cout<<"\nEnter the coordinates of the clipping window: ";
  cout<<"xmin: ";
  cin>>xmin;
  cout<<"xmax: ";
  cin>>xmax;
  cout<<"ymin: ";
  cin>>ymin;
  cout<<"ymax: ";
  cin>>ymax;

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  setbkcolor(4);

  cout<<"\nBEFORE CLIPPING THE LINES ARE:-";
  rectangle(xmin, ymin, xmax, ymax);
  for(int j = 0; j < i; j += 2) {
    line(x[j], y[j], x[j + 1], y[j + 1]);
  }

  initgraph(&gd, &gm, (char*)"");
  setbkcolor(6);
  setcolor(1);
  setlinestyle(DOTTED_LINE, 1, 1);
  
  cout<<"AFTER CLIPPING THE LINES ARE";
  rectangle(xmin, ymin, xmax, ymax);
  for(int j = 0; j < i; j += 2) {
    cohen(x[j], y[j], x[j + 1], y[j + 1], xmin, xmax, ymin, ymax);
  }
  return 1;
}