// AIM: WRITE A PROGRAM TO APPLY VARIOUS 2D TRANSFORMATION ON A 2D OBJECT (USE HOMOGENOUS COORDINATES).

#include<iostream>
#include<graphics.h>
#include<cctype>
#include<math.h>

using namespace std;

// globally defined array for coordinates of sqaure
int square[4][3];

// globally defined array for transformation matrix
double transform[3][3];

// globally defined array for transformed coordinates of square
int square_t[4][3];

// Matrix multiplication
void multi_matrix() {
  for(int i = 0; i < 4; i++)    
  {    
    for(int j = 0; j < 3; j++)    
    {    
      square_t[i][j] = 0;    
      for(int k = 0; k < 3; k++)    
      {    
        square_t[i][j] += square[i][k] * transform[k][j];    
      }    
    }    
  } 
}

// Scaling down the coordinate system to the middle of the screen
void scale_down(int max_x, int max_y) {
  max_x = getmaxx() / 2;
  max_y = getmaxy() / 2;

  setcolor(WHITE);
  line(0, max_y, max_x * 2, max_y);
  line(max_x, 0, max_x, max_y * 2);
}

// Display the original square
void display_original(int max_x, int max_y) {
  line(max_x + square[0][0], max_y - square[0][1], max_x + square[1][0], max_y - square[1][1]);
  line(max_x + square[1][0], max_y - square[1][1], max_x + square[2][0], max_y - square[2][1]);
  line(max_x + square[2][0], max_y - square[2][1], max_x + square[3][0], max_y - square[3][1]);
  line(max_x + square[0][0], max_y - square[0][1], max_x + square[3][0], max_y - square[3][1]);
}

// Display the transformed square
void display_transformed(int max_x, int max_y) {
  line(max_x + square_t[0][0], max_y - square_t[0][1], max_x + square_t[1][0], max_y - square_t[1][1]);
  line(max_x + square_t[1][0], max_y - square_t[1][1], max_x + square_t[2][0], max_y - square_t[2][1]);
  line(max_x + square_t[2][0], max_y - square_t[2][1], max_x + square_t[3][0], max_y - square_t[3][1]);
  line(max_x + square_t[0][0], max_y - square_t[0][1], max_x + square_t[3][0], max_y - square_t[3][1]);
}

// Scaling in the x component
void scaleX(float factor) {
  // update transformation matrix
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(i == j && i == 0) {
        transform[i][j] = factor;
      }
      else if(i == j && (i == 1 || i == 2)) {
        transform[i][j] = 1; 
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(DARKGRAY);

  // plot the original square
  display_original(max_x, max_y);
  setcolor(RED);
  // plot the transformed square
  display_transformed(max_x, max_y);
}

// Scaling in the y component
void scaleY(float factor) {
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(i == j && i == 1) {
        transform[i][j] = factor;
      }
      else if(i == j && (i == 0 || i == 2)) {
        transform[i][j] = 1; 
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(DARKGRAY);

  // plot the original square
  display_original(max_x, max_y);
  setcolor(GREEN);
  // plot the transformed square
  display_transformed(max_x, max_y);

}

// Scaling in both x and y component
void scaleXY(float factorX, float factorY) {
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(i == j && i == 0) {
        transform[i][j] = factorX;
      }
      else if(i == j && i == 1) {
        transform[i][j] = factorY; 
      } else if(i == j && i == 2) {
        transform[i][j] = 1;
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(DARKGRAY);

  // plot the original square
  display_original(max_x, max_y);
  setcolor(BLUE);
  // plot the transformed square
  display_transformed(max_x, max_y);

}


// Overall Scaling
void scale_overall(float factor) {
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(i == j && (i == 0 || i == 1)) {
        transform[i][j] = 1;
      }
      else if(i == j && i == 2) {
        transform[i][j] = factor;
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

  // Normalizing..
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
      square_t[i][j] = square_t[i][j] / factor;
    }
  }

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(DARKGRAY);

  // plot the original square
  display_original(max_x, max_y);
  setcolor(MAGENTA);
  // plot the transformed square
  display_transformed(max_x, max_y);

}

// Reflection about x-axis
void reflectionX() {
  // Update transformation matrix
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(i == j && i == 1) {
        transform[i][j] = -1;
      } else if(i == j && (i == 0 || i == 2)) {
        transform[i][j] = 1;
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(DARKGRAY);

  // plot the original square
  display_original(max_x, max_y);
  setcolor(CYAN);
  // plot the transformed square
  display_transformed(max_x, max_y); 
}

// Reflection about y-axis
void reflectionY() {
  // Update transformation matrix
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(i == j && i == 0) {
        transform[i][j] = -1;
      } else if(i == j && (i == 1 || i == 2)) {
        transform[i][j] = 1;
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(DARKGRAY);

  // plot the original square
  display_original(max_x, max_y);
  setcolor(RED);
  // plot the transformed square
  display_transformed(max_x, max_y);
}

// Reflection about the line y = x
void reflection_about_line1() {
  // Update transformation matrix
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(i == j && i == 2) {
        transform[i][j] = 1;
      } else if((i == 0 && j == 1) || (i == 1 && j == 0)) {
        transform[i][j] = 1;
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(DARKGRAY);

  // plot the original square
  display_original(max_x, max_y);
  setcolor(YELLOW);
  // plot the transformed square
  display_transformed(max_x, max_y);
}

// Reflection anout the line y = -x
void reflection_about_line2() {
  // Update transformation matrix
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(i == j && i == 2) {
        transform[i][j] = 1;
      } else if((i == 0 && j == 1) || (i == 1 && j == 0)) {
        transform[i][j] = -1;
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(DARKGRAY);

  // plot the original square
  display_original(max_x, max_y);
  setcolor(LIGHTBLUE);
  // plot the transformed square
  display_transformed(max_x, max_y);
}

// Rotation in anti-clockwise direction
void rotation_anti(int theta) {
  // Update the transformation matrix
  for(int i = 0;  i < 3; i++) {
    for(int j = 0;  j < 3; j++) {
      if(i == j && i == 0) {
        transform[i][j] = cos((double)(theta * 0.0174533));
      } else if(i == 0 && j == 1) {
        transform[i][j] = sin((double)(theta * 0.0174533));
      } else if(i == 1 && j == 0) {
        transform[i][j] = -sin((double)(theta * 0.0174533));
      } else if(i == j && i == 1) {
        transform[i][j] = cos((double)(theta * 0.0174533));
      } else if(i == j && i == 2) {
        transform[i][j] = 1;
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(DARKGRAY);

  // plot the original square
  display_original(max_x, max_y);
  setcolor(BLUE);
  // plot the transformed square
  display_transformed(max_x, max_y);

}

// Rotation in clockwise direction
void rotation(int theta) {
  // Update the transformation matrix
  for(int i = 0;  i < 3; i++) {
    for(int j = 0;  j < 3; j++) {
      if(i == j && i == 0) {
        transform[i][j] = cos((double)(-theta) * 0.0174533);
      } else if(i == 0 && j == 1) {
        transform[i][j] = sin((double)(-theta) * 0.0174533);
      } else if(i == 1 && j == 0) {
        transform[i][j] = -sin((double)(-theta) * 0.0174533);
      } else if(i == j && i == 1) {
        transform[i][j] = cos((double)(-theta) * 0.0174533);
      } else if(i == j && i == 2) {
        transform[i][j] = 1;
      } else { 
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(DARKGRAY);

  // plot the original square
  display_original(max_x, max_y);
  setcolor(MAGENTA);
  // plot the transformed square
  display_transformed(max_x, max_y);
}

// Shearing in x component
void shearingX(int sh_x) {
  // Update the transformation matrix
  for(int i = 0;  i < 3; i++) {
    for(int j = 0;  j < 3; j++) {
      if(i == j) {
        transform[i][j] = 1;
      } else if(i == 1 && j == 0) {
        transform[i][j] = sh_x;
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(DARKGRAY);

  // plot the original square
  display_original(max_x, max_y);
  setcolor(MAGENTA);
  // plot the transformed square
  display_transformed(max_x, max_y);
}

// Shearing in y component
void shearingY(int sh_y) {
  // Update the transformation matrix
  for(int i = 0;  i < 3; i++) {
    for(int j = 0;  j < 3; j++) {
      if(i == j) {
        transform[i][j] = 1;
      } else if(i == 0 && j == 1) {
        transform[i][j] = sh_y;
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(DARKGRAY);

  // plot the original square
  display_original(max_x, max_y);
  setcolor(BROWN);
  // plot the transformed square
  display_transformed(max_x, max_y);
}

// Shearing in both x and y component
void shearingXY(int sh_x, int sh_y) {
  // Update the transformation matrix
  for(int i = 0;  i < 3; i++) {
    for(int j = 0;  j < 3; j++) {
      if(i == j) {
        transform[i][j] = 1;
      } else if(i == 1 && j == 0) {
        transform[i][j] = sh_x;
      } else if(i == 0 && j == 1) {
        transform[i][j] = sh_y;
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

  int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(DARKGRAY);

  // plot the original square
  display_original(max_x, max_y);
  setcolor(MAGENTA);
  // plot the transformed square
  display_transformed(max_x, max_y);
}

// Translation
void translation(int m, int n) {
  // Update the transformation matrix
  for(int i = 0;  i < 3; i++) {
    for(int j = 0;  j < 3; j++) {
      if(i == j) {
        transform[i][j] = 1;
      } else if(i == 2 && j == 0) {
        transform[i][j] = m;
      } else if(i == 2 && j == 1) {
        transform[i][j] = n;
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

 int gd = DETECT, gm;
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(DARKGRAY);

  // plot the original square
  display_original(max_x, max_y);
  setcolor(YELLOW);
  // plot the transformed square
  display_transformed(max_x, max_y);

}
 
int main(int argc, char const *argv[])
{
  char ch;
  int op;

  cout<<"\n\n===========================================";
  cout<<"\nPERFORM 2D TRANSFORMATIONS ON A SQUARE";
  cout<<"\n=============================================";

  cout<<"\n\nEnter the co-ordinates of square:-\n";
  for(int i = 0; i < 4; i++) {
    cout<<"Row "<<i+1<<" : ";
    for(int j = 0; j < 2; j++) {
       cin>>square[i][j];
    }
  } 

  // convert to homogeneous co-ordinate system
  square[0][2] = 1;
  square[1][2] = 1;
  square[2][2] = 1;
  square[3][2] = 1;

  do {
    cout<<"\n\n---------------------------";
    cout<<"\n\tMAIN MENU";
    cout<<"\n-----------------------------";
    cout<<"\n1. Scaling in x component";
    cout<<"\n2. Scaling in y component";
    cout<<"\n3. Scaling in both x and y component";
    cout<<"\n4. Overall Scaling";
    cout<<"\n5. Reflection about x-axis";
    cout<<"\n6. Reflection about y-axis";
    cout<<"\n7. Reflection about the line y = x";
    cout<<"\n8. Reflection about the line y = -x";
    cout<<"\n9. Rotation (Clockwise)";
    cout<<"\n10. Rotation (Anti-clockwise)";
    cout<<"\n11. Shearing in x component";
    cout<<"\n12. Shearing in y component";
    cout<<"\n13. Shearing in both x and y component";
    cout<<"\n14. Translation";
    cout<<"\nEnter choice: ";
    cin>>op;

    switch(op) {
      case 1: {
        float f;
        cout<<"\n\nYOU ARE PERFORMING SCALING IN X COMPONENT";
        cout<<"\nEnter the scaling factor: ";
        cin>>f;
        scaleX(f);
        cout<<"Object scaled by a factor of "<<f<<" in x-direction.";
      }
      break;
      case 2: {
        float f;
        cout<<"\nYOU ARE PERFORMING SCALING IN Y COMPONENT";
        cout<<"\nEnter the scaling factor: ";
        cin>>f;
        scaleY(f);
        cout<<"\nObject scaled by a factor of "<<f<<" in y-direction.";
      }
      break;
      case 3: {
        float fx, fy;
        cout<<"\n\nYOU ARE PERFORMING SCALING IN BOTH X AND Y COMPONENT";
        cout<<"\nEnter the scaling factor (x xomponent): ";
        cin>>fx;
        cout<<"Enter the scaling factor (y component): ";
        cin>>fy;
        scaleXY(fx, fy);
        cout<<"\nObject scaled by a factor of "<<fx<<" in x-direction && a factor of "<<fy<<" in y-direction.";
      }
      break;
      case 4: {
        float f;
        cout<<"\n\nYOU ARE PERFORMING OVERALL SCALING";
        cout<<"\nEnter the scaling factor: ";
        cin>>f;
        scale_overall(f);
        cout<<"Overall scaling with a factor "<<f<<" has been done.";
      }
      break;
      case 5: {
        cout<<"\nYOU ARE PERFORMING REFLECTION ABOUT x-axis";
        reflectionX();
        cout<<"\nReflection about x-axis has been done.";
      }
      break;
      case 6: {
        cout<<"\nYOU ARE PERFORMING REFLECTION ABOUT y-axis";
        reflectionY();
        cout<<"\nReflection about y-axis has been done.";
      }
      break;
      case 7: {
        cout<<"\nYOU ARE PERFORMING REFLECTION ABOUT LINE y = x";
        reflection_about_line1();
        cout<<"\nReflection about line y = x has been done.";
      }
      break;
      case 8: {
        float f;
        cout<<"\nYOU ARE PERFORMING REFLECTION ABOUT LINE y = -x";
        reflection_about_line2();
        cout<<"\nReflection about the line y = -x has been done.";
      }
      break;
      case 9: {
        int theta;
        cout<<"\n\nYOU ARE PERFORMING ROTATION (CLOCKWISE)";
        cout<<"\nEnter the angle about which you want to perform the rotation(in degrees): ";
        cin>>theta;
        rotation(theta);
        cout<<"Rotation about an angle "<<theta<<" has been done.";
      }
      break;
      case 10: {
        int theta;
        cout<<"\n\nYOU ARE PERFORMING ROTATION (ANTI-CLOCKWISE)";
        cout<<"\nEnter the angle about which you want to perform the rotation(in degrees): ";
        cin>>theta;
        rotation_anti(theta);
        cout<<"Rotation about an angle "<<theta<<" has been done.";
      }
      break;
      case 11: {
        float sh_x;
        cout<<"\n\nYOU ARE PERFORMING SHEARING IN X COMPONENT";
        cout<<"\nEnter shearing factor: ";
        cin>>sh_x;
        shearingX(sh_x);
        cout<<"Shearing with a factor of "<<sh_x<<" in x component has been done.";
      }
      break;
      case 12: {
        float sh_y;
        cout<<"\n\nYOU ARE PERFORMING SHEARING IN Y COMPONENT";
        cout<<"\nEnter shearing factor: ";
        cin>>sh_y;
        shearingY(sh_y);
        cout<<"Shearing with a factor of "<<sh_y<<" in x component has been done.";
      }
      break;
      case 13: {
        float sh_x, sh_y;
        cout<<"\n\nYOU ARE PERFORMING SHEARING IN X and Y COMPONENT";
        cout<<"\nEnter shearing factor:-\n";
        cout<<"x: ";
        cin>>sh_x;
        cout<<"y: ";
        cin>>sh_y;
        shearingXY(sh_x, sh_y);
        cout<<"Shearing with a factor of "<<sh_x<<","<<sh_y<<" in x and y component respectively has been done.";
      }
      break;
      case 14: {
        int m, n;
        cout<<"\n\nYOU ARE PERFORMING TRANSLATION";
        cout<<"\nEnter the translating factors:-\n";
        cout<<"m: ";
        cin>>m;
        cout<<"n: ";
        cin>>n;
        translation(m, n);
        cout<<"Translation about factors "<<m<<", "<<n<<" has been done.";
      }
      break;
      default: cout<<"\nPlease enter a valid option.";
    };

    cout<<"\nWant to return back to menu? (y/Y - \"Yes\", any other key - \"No\") : ";
    cin>>ch; 
  }while(toupper(ch) == 'Y');

  closegraph();
  return 0;
}
