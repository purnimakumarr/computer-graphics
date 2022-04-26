// AIM: WRITE A PROGRAM TO APPLY VARIOUS 3D TRANSFORMATION ON A 3D OBJECT AND THEN APPLY PARALLEL AND PERSPECTIVE PROJECTION ON IT.

#include<iostream>
#include<graphics.h>
#include<cctype>
#include<math.h>

using namespace std; 

// globally defined array for co-ordinates of sqaure
int cube[8][4];

// globally defined array for transformation matrix
double transform[4][4];

// globally deifned array for transformed co-ordinates of square
int cube_t[8][4];

// globally defined array for resultant matrix we get after performing projection
int result[8][4];

// Matrix multiplication
void multi_matrix() {
  for(int i = 0; i < 8; i++)    
  {    
    for(int j = 0; j < 4; j++)    
    {    
      cube_t[i][j] = 0;    
      for(int k = 0; k < 4; k++)    
      {    
        cube_t[i][j] += cube[i][k] * transform[k][j];    
      }    
    }    
  } 
}

// plot the transformed cube
void display(int max_x, int max_y) {
  int i;
  for(i = 0; i < 3; i++) {
    line(max_x + result[i][0], max_y - result[i][1], max_x + result[i + 1][0], max_y - result[i + 1][1]);
  }
  line(max_x + result[3][0], max_y - result[3][1], max_x + result[0][0], max_y - result[0][1]);
  for(i = 4; i < 7; i++) {
    line(max_x + result[i][0], max_y - result[i][1], max_x + result[i + 1][0], max_y - result[i + 1][1]);
  }
  line(max_x + result[7][0], max_y - result[7][1], max_x + result[4][0], max_y - result[4][1]);
  line(max_x + result[0][0], max_y - result[0][1], max_x + result[4][0], max_y - result[4][1]);
  line(max_x + result[1][0], max_y - result[1][1], max_x + result[5][0], max_y -  result[5][1]);
  line(max_x + result[3][0], max_y - result[3][1], max_x + result[7][0], max_y -  result[7][1]);
  line(max_x + result[2][0], max_y - result[2][1], max_x + result[6][0], max_y - result[6][1]);

}

// Scaling down the co-ordinate system to the middle of the screen
void scale_down(int max_x, int max_y) {
  max_x = getmaxx() / 2;
  max_y = getmaxy() / 2;

  setcolor(WHITE);
  line(0, max_y, max_x * 2, max_y);
  line(max_x, 0, max_x, max_y * 2);
}

// Perform projection; if axis = 1 => Projection about x-axis || if axis = 2 => Projection about y-axis || if axis = 3 => Projection about z-axis
void projection_ortho() {
  int px = 1, py = 1, pz = 0;

  // Projection matrix
  int p_t[4][4];
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if(i == j) {
        if(i == 0) {
          p_t[i][j] = px;
        } else if(i == 1) {
          p_t[i][j] = py;
        } else if(i == 2) {
          p_t[i][j] = pz;
        } else if(i == 3) {
          p_t[i][j] = 1;
        }
      } else {
        p_t[i][j] = 0;
      }
    }
  }

  // matrix multiplication
  for(int i = 0; i < 8; i++)    
  {    
    for(int j = 0; j < 4; j++)    
    {    
      result[i][j] = 0;    
      for(int k = 0; k < 4; k++)    
      {    
        result[i][j] += cube_t[i][k] * p_t[k][j];    
      }    
    }    
  } 

  int gd = DETECT, gm;
  // initwindow(1000, 1000);
  initgraph(&gd, &gm, (char*)"");
  int max_x = getmaxx() / 2, max_y = getmaxy() / 2;
  scale_down(max_x, max_y);
  setcolor(LIGHTBLUE);

  // draw the transformed figure
  display(max_x, max_y);
}

// Perform scaling on the cube
void scaling(float fx, float fy, float fz) {
  // Update the transformation matrix
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if(i == j) {
        if(i == 0) {
          transform[i][j] = fx;
        } else if(i == 1) {
          transform[i][j] = fy;
        } else if(i == 2) {
          transform[i][j] = fz;
        } else if(i == 3) {
        transform[i][j] = 1;
        } 
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();
}

// Perform overall scaling
void scaling_overall(float f) {
  // Update the transformation matrix
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if(i == j && i == 3) {
        transform[i][j] = f;
      } else if(i == j && i != 3) {
        transform[i][j] = 1;
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();

  // normalizing
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 4; j++) {
      cube_t[i][j] /= f;
    }
  }
}

// Perform rotation about the x-axis; flag = 0 => clockwise || flag = 1 => anti-clockwise
void rotationX(int theta, int flag) {
  if(flag = 0) {
    theta = - theta;
  }

  // Update the transformation matrix
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if(i == j && (i == 0 || i == 3)) {
        transform[i][j] = 1;
      } else if((i == 1 && j == 1) || (i == 2 && j == 2)) {
        transform[i][j] = cos((double)(theta * 0.0174533));
      } else if(i == 2 && j == 1) {
        transform[i][j] = - sin((double)(theta * 0.0174533));
      } else if(i == 1 && j == 2) {
        transform[i][j] = sin((double)(theta * 0.0174533));
      } else {
        transform[i][j] == 0;
      }
    }
  }

  multi_matrix();
}

// Perform rotation about the y-axis; flag = 0 => clockwise || flag = 1 => anti-clockwise
void rotationZ(int alpha, int flag) {
  if(flag = 0) {
    alpha = - alpha;
  }

  // Update the transformation matrix
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
        if(i == j && (i == 2 || i == 3)) {
          transform[i][j] = 1;
        } else if((i == 0 && j == 0) || (i == 1 && j == 1)) {
          transform[i][j] =  cos((double)(alpha * 0.0174533));
        } else if(i == 0 && j == 1) {
          transform[i][j] =  sin((double)(alpha * 0.0174533));
        } else if(i == 1 && j == 0) {
          transform[i][j] =  - sin((double)(alpha * 0.0174533));
        } else {
          transform[i][j] = 0;
        }
    }
  }

  multi_matrix();
}

// Perform rotation about the z-axis; flag = 0 => clockwise || flag = 1 => anti-clockwise
void rotationY(int phi, int flag) {
  if(flag = 0) {
    phi = - phi;
  }

  // Update the transformation matrix
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if(i == j && (i == 1 || i == 3)) {
        transform[i][j] = 1;
      } else if((i == 0 && j == 0) || (i == 2 && j == 2)) {
        transform[i][j] = cos((double)(phi * 0.0174533));
      } else if(i == 2 && j == 0) {
        transform[i][j] = sin((double)(phi * 0.0174533));
      } else if(i == 0 && j == 2) {
        transform[i][j] = -sin((double)(phi * 0.0174533));
      } else {
        transform[i][j] = 0;
      }
    }
  }
}

// Perform reflection relative to the XY plane
void reflectionXY() {
  // Update the transformation matrix
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) { 
      if(i == j) {
        if(i == 2) {
          transform[i][j] = -1;
        } else {
          transform[i][j] = 1;
        }
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();
}

// Perform reflection relative to the YZ plane
void reflectionYZ() {
  // Update the transformation matrix
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) { 
      if(i == j) {
        if(i == 0) {
          transform[i][j] = -1;
        } else {
          transform[i][j] = 1;
        }
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();
}

// Perform reflection relative to the XZ plane
void reflectionXZ() {
  // Update the transformation matrix
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) { 
      if(i == j) {
        if(i == 1) {
          transform[i][j] = -1;
        } else {
          transform[i][j] = 1;
        }
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();
}

// Perform shearing
void shearing(float fx1, float fx2, float fy1, float fy2, float fz1, float fz2) {
  // Update the transformation matrix
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if(i == j) {
        transform[i][j] = 1;
      } else if(i == 0) {
        if(j == 1) {
          transform[i][j] = fx1;
        } else if(j == 2) {
          transform[i][j] = fx2;
        }
      } else if(i == 1) {
        if(j == 0) {
          transform[i][j] = fy1;
        } else if(j == 2) {
          transform[i][j] = fy2;
        }
      } else if(i == 2) {
        if(j == 0) {
          transform[i][j] = fz1;
        } else if(j == 1) {
          transform[i][j] = fz2;
        }
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();
}

// Perform translation
void translation(float tx, float ty, float tz) {
  // Update the transformation matrix
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if(i == j) {
        transform[i][j] = 1;
      } else if(i == 2) {
        if(j == 0) {
          transform[i][j] =  tx;
        } else if(j == 1) {
          transform[i][j] = ty;
        } else if(j == 2) {
          transform[i][j] = tz;
        }
      } else {
        transform[i][j] = 0;
      }
    }
  }

  multi_matrix();
}

int main(int argc, char const *argv[])
{
  char ch;
  int op, op_pro;

  cout<<"\n\n===========================================";
  cout<<"\nPERFORM 3D TRANSFORMATIONS ON A CUBE";
  cout<<"\n=============================================";

  cout<<"\n\nEnter the co-ordinates of cube:-\n";
  for(int i = 0; i < 8; i++) {
    cout<<"Row "<<i+1<<" : ";
    for(int j = 0; j < 4; j++) {
       cin>>cube[i][j];
    }
  } 
  
  // convert to homogeneous co-ordinate system
  cube[0][3] = 1;
  cube[1][3] = 1;
  cube[2][3] = 1;
  cube[3][3] = 1;
  cube[4][3] = 1;
  cube[5][3] = 1;
  cube[6][3] = 1;
  cube[7][3] = 1;

  do {
    cout<<"\n\n---------------------------";
    cout<<"\n\tMAIN MENU";
    cout<<"\n-----------------------------";
    cout<<"\n1. Local Scaling";
    cout<<"\n2. Overall Scaling";
    cout<<"\n3. Rotation about x-axis (CLOCKWISE)";
    cout<<"\n4. Rotation about y-axis (CLOCKWISE)";
    cout<<"\n5. Rotation about z-axis (CLOCKWISE)";
    cout<<"\n6. Rotation about x-axis (ANTI-CLOCKWISE)";
    cout<<"\n7. Rotation about y-axis (ANTI-CLOCKWISE)";
    cout<<"\n8. Rotation about z-axis (ANTI-CLOCKWISE)";
    cout<<"\n9. Reflection relative to XY plane";
    cout<<"\n10. Reflection relative to YZ plane";
    cout<<"\n11. Reflection relative to XZ plane";
    cout<<"\n12. Shearing";
    cout<<"\n13. Translation";
    cout<<"\nEnter choice: ";
    cin>>op;

    switch(op) {
      case 1: {
        float fx, fy, fz;
        cout<<"\nYOU ARE PERFORMING LOCAL SCALING\n";
        cout<<"Enter the scaling factors:-\n";
        cout<<"fx: ";
        cin>>fx;
        cout<<"fy: ";
        cin>>fy;
        cout<<"fz: ";
        cin>>fz;
        cout<<"\nTO DISPLAY THE TRANSFORMED FIGURE\n";
        cout<<"Select the type of projection you want to perform.";
        cout<<"\n\t1. Orthographic Projection";
        cout<<"\nEnter choice: ";
        cin>>op_pro;
        switch(op_pro) {
          case 1: {
            scaling(fx, fy, fz);
            projection_ortho();
          }
        }
        cout<<"Scaling with factors "<<fx<<", "<<fy<<", "<<fz<<" in the x, y and z component respectively has been done.";
      }
      break;
      case 2: {
        float factor;
        cout<<"\nYOU ARE PERFORMING OVERALL SCALING\n";
        cout<<"Enter overall scaling factor: ";
        cin>>factor;
        cout<<"\nTO DISPLAY THE TRANSFORMED FIGURE\n";
        cout<<"Select the type of projection you want to perform.";
        cout<<"\n\t1. Orthographic Projection";
        cout<<"\nEnter choice: ";
        cin>>op_pro;
        switch(op_pro) {
          case 1: {
            scaling_overall(factor);
            projection_ortho();
          }
        }
        cout<<"Overall scaling with a factor "<<factor<<" has been done.";
      }
      break;
      case 3: {
        int theta;
        cout<<"\nYOU ARE PERFORMING ROTATION ABOUT X-AXIS (CLOCKWISE)\n";
        cout<<"Enter the angle by which you want to rotate the cube: ";
        cin>>theta;
        cout<<"\nTO DISPLAY THE TRANSFORMED FIGURE\n";
        cout<<"Select the type of projection you want to perform.";
        cout<<"\n\t1. Orthographic Projection";
        cout<<"\nEnter choice: ";
        cin>>op_pro;
        switch(op_pro) {
          case 1: {
            rotationX(theta, 0);
            projection_ortho();
          }
        }
        cout<<"Rotation about x-axis in the clockwise direction has been done.";
      }
      break;
      case 4: {
        int phi;
        cout<<"\nYOU ARE PERFORMING ROTATION ABOUT Y-AXIS (CLOCKWISE)\n";
        cout<<"Enter the angle by which you want to rotate the cube: ";
        cin>>phi;
        cout<<"\nTO DISPLAY THE TRANSFORMED FIGURE\n";
        cout<<"Select the type of projection you want to perform.";
        cout<<"\n\t1. Orthographic Projection";
        cout<<"\nEnter choice: ";
        cin>>op_pro;
        switch(op_pro) {
          case 1: {
            rotationY(phi, 0);
            projection_ortho();
          }
        }
        cout<<"Rotation about y-axis in the clockwise direction has been done.";
      }
      break;
      case 5: {
        int alpha;
        cout<<"\nYOU ARE PERFORMING ROTATION ABOUT Z-AXIS (CLOCKWISE)\n";
        cout<<"Enter the angle by which you want to rotate the cube: ";
        cin>>alpha;
        cout<<"\nTO DISPLAY THE TRANSFORMED FIGURE\n";
        cout<<"Select the type of projection you want to perform.";
        cout<<"\n\t1. Orthographic Projection";
        cout<<"\nEnter choice: ";
        cin>>op_pro;
        switch(op_pro) {
          case 1: {
            rotationZ(alpha, 0);
            projection_ortho();
          }
        }
        cout<<"Rotation about z-axis in the clockwise direction has been done.";
      }
      break;
      case 6: {
        int theta;
        cout<<"\nYOU ARE PERFORMING ROTATION ABOUT X-AXIS (ANTI-CLOCKWISE)\n";
        cout<<"Enter the angle by which you want to rotate the cube: ";
        cin>>theta;
        cout<<"\nTO DISPLAY THE TRANSFORMED FIGURE\n";
        cout<<"Select the type of projection you want to perform.";
        cout<<"\n\t1. Orthographic Projection";
        cout<<"\nEnter choice: ";
        cin>>op_pro;
        switch(op_pro) {
          case 1: {
            rotationX(theta, 1);
            projection_ortho();
          }
        }
        cout<<"Rotation about x-axis in the anti-clockwise direction has been done.";
      }
      break;
      case 7: {
        int phi;
        cout<<"\nYOU ARE PERFORMING ROTATION ABOUT Y-AXIS (ANTI-CLOCKWISE)";
        cout<<"\nEnter the angle by which you want to rotate the cube: ";
        cin>>phi;
        cout<<"\nTO DISPLAY THE TRANSFORMED FIGURE\n";
        cout<<"Select the type of projection you want to perform.";
        cout<<"\n\t1. Orthographic Projection";
        cout<<"\nEnter choice: ";
        cin>>op_pro;
        switch(op_pro) {
          case 1: {
            rotationY(phi, 1);
            projection_ortho();
          }
        }
        cout<<"Rotation about y-axis in the anti-clockwise direction has been done.";
      }
      break;
      case 8: {
        int alpha;
        cout<<"\nYOU ARE PERFORMING ROTATION ABOUT Z-AXIS (ANTI-CLOCKWISE)\n";
        cout<<"Enter the angle by which you want to rotate the cube: ";
        cin>>alpha;
        cout<<"\nTO DISPLAY THE TRANSFORMED FIGURE\n";
        cout<<"Select the type of projection you want to perform.";
        cout<<"\n\t1. Orthographic Projection";
        cout<<"\nEnter choice: ";
        cin>>op_pro;
        switch(op_pro) {
          case 1: {
            rotationZ(alpha, 1);
            projection_ortho();
          }
        }
        cout<<"Rotation about z-axis in the anti-clockwise direction has been done.";
      }
      break;
      case 9: {
        cout<<"\nYOU ARE PERFORMING REFLECTION RELATIVE TO XY PLANE\n";
        cout<<"Reflection relative to the XY plane has been done.";
        cout<<"\nTO DISPLAY THE TRANSFORMED FIGURE\n";
        cout<<"Select the type of projection you want to perform.";
        cout<<"\n\t1. Orthographic Projection";
        cout<<"\nEnter choice: ";
        cin>>op_pro;
        switch(op_pro) {
          case 1: {
            reflectionXY();
            projection_ortho();
          }
        }
      }
      break;
      case 10: {
        cout<<"\nYOU ARE PERFORMING REFLECTION RELATIVE TO YZ PLANE\n";
        cout<<"Reflection relative to the YZ plane has been done.";
        cout<<"\nTO DISPLAY THE TRANSFORMED FIGURE\n";
        cout<<"Select the type of projection you want to perform.";
        cout<<"\n\t1. Orthographic Projection";
        cout<<"\nEnter choice: ";
        cin>>op_pro;
        switch(op_pro) {
          case 1: {
            reflectionYZ();
            projection_ortho();
          }
        }
      }
      break;
      case 11: {
        cout<<"\nYOU ARE PERFORMING REFLECTION RELATIVE TO THE XZ PLANE\n";
        cout<<"Reflection relative to the XZ plane has been done.";
        cout<<"\nTO DISPLAY THE TRANSFORMED FIGURE\n";
        cout<<"Select the type of projection you want to perform.";
        cout<<"\n\t1. Orthographic Projection";
        cout<<"\nEnter choice: ";
        cin>>op_pro;
        switch(op_pro) {
          case 1: {
            reflectionXZ();
            projection_ortho();
          }
        }
      }
      break;
      case 12: {
        int fx1, fx2, fy1, fy2, fz1, fz2;
        cout<<"\nYOU ARE PERFORMING SHEARING\n";
        cout<<"Enter the shearing factors:-\n";
        cout<<"fx1: ";
        cin>>fx1;
        cout<<"fx2: ";
        cin>>fx2; 
        cout<<"fy1: ";
        cin>>fy1;
        cout<<"fy2: ";
        cin>>fy2;
        cout<<"fz1: ";
        cin>>fz1;
        cout<<"fz2: ";
        cin>>fz2;
        cout<<"\nTO DISPLAY THE TRANSFORMED FIGURE\n";
        cout<<"Select the type of projection you want to perform.";
        cout<<"\n\t1. Orthographic Projection";
        cout<<"\nEnter choice: ";
        cin>>op_pro;
        switch(op_pro) {
          case 1: {
            shearing(fx1, fx2, fy1, fy2, fz1, fz2);
            projection_ortho();
          }
        }
        cout<<"Shearing with factors "<<fx1<<", "<<fx2<<", "<<fy1<<", "<<fy2<<", "<<fz1<<", "<<fz2<<" has been done.";
      }
      break;
      case 13: {
        float tx, ty, tz;
        cout<<"\nYOU ARE PERFORMING TRANSLATION\n";
        cout<<"Enter the translation factors in the x, y and z-direction respectively:-\n";
        cout<<"tx: ";
        cin>>tx;
        cout<<"ty: ";
        cin>>ty;
        cout<<"tz: ";
        cin>>tz;
        cout<<"\nTO DISPLAY THE TRANSFORMED FIGURE\n";
        cout<<"Select the type of projection you want to perform.";
        cout<<"\n\t1. Orthographic Projection";
        cout<<"\nEnter choice: ";
        cin>>op_pro;
        switch(op_pro) {
          case 1: {
            translation(tx, ty, tz);
            projection_ortho();
          }
        }
        cout<<"Translation with factors "<<tx<<", "<<ty<<", "<<tz<<" has been done in the direction of x, y and z-axis respectively.";
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