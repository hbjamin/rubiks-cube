/*  


*/



// c++ headers
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void draw_cube(vector<vector<string>> &cube);
void draw_row(vector<string> row, int shift);
void draw_filler_line(vector<string> row, int shift);
void draw_line(int length, int shift);
void draw_text(string text, double shift, double shift2);
void draw_blank(double length);
void draw_buffer(int length);

string get_command();
void play(vector<vector<string>> &cube, string command);
void scramble(vector<vector<string>> &cube);
void reset(vector<vector<string>> &cube);

void rotate(vector<vector<string>> &cube, string command);
void face(vector<vector<string>> &cube, bool clockwise);
void right(vector<vector<string>> &cube, bool clockwise);
void center(vector<vector<string>> &cube, bool clockwise);
void left(vector<vector<string>> &cube, bool clockwise);
void up(vector<vector<string>> &cube, bool clockwise);
void middle(vector<vector<string>> &cube, bool clockwise);
void down(vector<vector<string>> &cube, bool clockwise);
void body_up(vector<vector<string>> &cube, bool clockwise);
void body_right(vector<vector<string>> &cube, bool clockwise);

void swap(vector<vector<string>> &cube, int face1, int square1, int face2, int square2, int face3, int square3, int face4, int square4, bool clockwise);
void curl(vector<vector<string>> &cube, int face, bool clockwise);

int main(int nargs, char** argv) {

  //argument check
  if (nargs>1) {
    cout << "usage: cube [no arguments]" << endl;
    return 0;
  }
  
  //make rubiks cube in solved state
  vector<vector<string>> cube = {{"W","W","W","W","W","W","W","W","W"}, 
				 {"R","R","R","R","R","R","R","R","R"},
				 {"G","G","G","G","G","G","G","G","G"},
				 {"Y","Y","Y","Y","Y","Y","Y","Y","Y"},
				 {"B","B","B","B","B","B","B","B","B"},
				 {"O","O","O","O","O","O","O","O","O"}};

 //draw rubiks cube
 draw_cube(cube);

 //continually rotate cube using input command
 play(cube, get_command()); 
  

  return 0;
}

void draw_cube(vector<vector<string>> &cube) {
  draw_buffer(120);
  //do in four levels
  for (int i=0;i<4;i++) {
    for (int j=0; j<3; j++) {
      if (i==2) {
        vector<string> row = {cube[i][3*j],cube[i][3*j+1],cube[i][3*j+2],cube[i+1][3*j],cube[i+1][3*j+1],cube[i+1][3*j+2],cube[i+2][3*j],cube[i+2][3*j+1],cube[i+2][3*j+2]};
        draw_line(3,3);
        draw_filler_line(row,3);
        draw_row(row,3);
        draw_filler_line(row,3);
        if (j==2) {
	  draw_line(3,3);
        }
      } else {
        if (i==3) {
          vector<string> row = {cube[i+2][3*j],cube[i+2][3*j+1],cube[i+2][3*j+2]};
          draw_filler_line(row,4);
          draw_row(row,4);
          draw_filler_line(row,4);
          draw_line(1,4);
        } else {
          vector<string> row = {cube[i][3*j],cube[i][3*j+1],cube[i][3*j+2]};
          draw_line(1,4);
          draw_filler_line(row,4);
	  draw_row(row,4);
	  draw_filler_line(row,4);
        }
      } 
    }
  }
  draw_buffer(3);
}

void draw_row(vector<string> row, int shift) {
  if (shift>0) {
    draw_blank(shift);
  }
  cout << "*";
  for (int i=0; i<row.size(); i++) {
    if (row[i]=="R") {
      cout << "\033[41m       ";
    } else if (row[i]=="G") {
      cout << "\033[42m       ";    
    } else if (row[i]=="Y") {
      cout << "\033[43m       ";
    } else if (row[i]=="B") {
      cout << "\033[44m       ";
    } else if (row[i]=="O") {
      cout << "\033[45m       ";
    } else if (row[i]=="W") {
      cout << "\033[47m       ";
    }
    cout << "\033[40m*";
  }
  cout << endl;
}

void draw_filler_line(vector<string> row, int shift) {
  if (shift>0) {
    draw_blank(shift);
  }
  cout << "*";
  for (int i=0; i<row.size(); i++) {
    if (row[i]=="R") {
      cout << "\033[41m       ";
    } else if (row[i]=="G") {
      cout << "\033[42m       ";
    } else if (row[i]=="Y") {
      cout << "\033[43m       ";
    } else if (row[i]=="B") {
      cout << "\033[44m       ";
    } else if (row[i]=="O") {
      cout << "\033[45m       ";
    } else if (row[i]=="W") {
      cout << "\033[47m       ";
    }
    cout << "\033[40m*";
  }
  cout << endl;
}

void draw_line(int length, int shift) {
  if (shift>0) {
    draw_blank(shift);
  }
  cout << "*";
  for (int i=0; i<length*3; i++) {
    cout << " * * * *";
  }
  cout << endl;
}

void draw_text(string text, double shift, double shift2) {
  if (shift>0) {
    draw_blank(shift);
  }
  cout << text;
  if (shift2>0) {
    draw_blank(shift2);
  }
}

void draw_blank(double length) {
  for (int i=0; i<length*24; i++) {
    cout << " ";
  }
}

void draw_buffer(int length) {
  for (int i=0;i<length;i++) {
    cout << endl;
  }
}

string get_command() {
  cout << "Enter Command:" << endl;
  string command;
  cin >> command;
  return command;
}

void play(vector<vector<string>> &cube, string command) {
  if (command != "q") {
     //apply command
     rotate(cube, command);
     //draw updated cube
     draw_cube(cube);
     //ask for new rotation
     play(cube,get_command());
  } 
}

void scramble(vector<vector<string>> &cube) {
  for (int i=0;i<100;i++) {
    int command = rand() % 18;
    if (command==0) {
      face(cube,true);
    } else if (command==1) {
      face(cube,false);
    } else if (command==2) {
      right(cube,true);
    } else if (command==3) {
      right(cube,false);
    } else if (command==4) {
      center(cube,true);
    } else if (command==5) {
      center(cube,false);
    } else if (command==6) {
      left(cube,true);
    } else if (command==7) {
      left(cube,false);
    } else if (command==8) {
      up(cube,true);
    } else if (command==9) {
      up(cube,false);
    } else if (command==10) {
      down(cube,true);
    } else if (command==11) {
      down(cube,false);
    } else if (command==12) {
      middle(cube,true);
    } else if (command==13) {
      middle(cube,false);
    } else if (command==14) {
      body_up(cube,true);
    } else if (command==15) {
      body_right(cube,true);
    } else if (command==16) {
      body_up(cube,false);
    } else if (command==17) {
      body_right(cube,false);
    }
  }
}

void reset(vector<vector<string>> &cube) {
  cube = {{"W","W","W","W","W","W","W","W","W"},
          {"R","R","R","R","R","R","R","R","R"},
          {"G","G","G","G","G","G","G","G","G"},
          {"Y","Y","Y","Y","Y","Y","Y","Y","Y"},
          {"B","B","B","B","B","B","B","B","B"},
          {"O","O","O","O","O","O","O","O","O"}};
}

void rotate(vector<vector<string>> &cube, string command) {
  if (command=="f") {
    face(cube,true);
  } else if (command=="f'") {
    face(cube,false);
  } else if (command=="r") {
    right(cube,true);
  } else if (command=="r'") {
    right(cube,false);
  } else if (command=="c") {
    center(cube,true);
  } else if (command=="c'") {
    center(cube,false); 
  } else if (command=="l") {
    left(cube,true);
  } else if (command=="l'") {
    left(cube,false);
  } else if (command=="u") {
    up(cube,true);
  } else if (command=="u'") {
    up(cube,false);
  } else if (command=="d") {
    down(cube,true);
  } else if (command=="d'") {
    down(cube,false);
  } else if (command=="m") {
    middle(cube,true);
  } else if (command=="m'") {
    middle(cube,false);
  } else if (command=="bu") {
    body_up(cube,true);
  } else if (command=="br") {
    body_right(cube,true);
  } else if (command=="bd") {
    body_up(cube,false);
  } else if (command=="bl") {
    body_right(cube,false);
  } else if (command=="scramble") {
    scramble(cube);
  } else if (command=="reset") {
    reset(cube);
  }
}

void face(vector<vector<string>> &cube, bool clockwise) {
  swap(cube,1,6,2,8,5,2,4,0,clockwise);
  swap(cube,1,7,2,5,5,1,4,3,clockwise);
  swap(cube,1,8,2,2,5,0,4,6,clockwise);
  curl(cube,3,clockwise);
}

void right(vector<vector<string>> &cube, bool clockwise) {
  swap(cube,0,2,1,2,3,2,5,2,clockwise);
  swap(cube,0,5,1,5,3,5,5,5,clockwise);
  swap(cube,0,8,1,8,3,8,5,8,clockwise);
  curl(cube,4,clockwise);
}

void center(vector<vector<string>> &cube, bool clockwise) {
  swap(cube,0,1,1,1,3,1,5,1,clockwise);
  swap(cube,0,4,1,4,3,4,5,4,clockwise);
  swap(cube,0,7,1,7,3,7,5,7,clockwise);
}

void left(vector<vector<string>> &cube, bool clockwise) {
  swap(cube,0,0,5,0,3,0,1,0,clockwise);
  swap(cube,0,3,5,3,3,3,1,3,clockwise);
  swap(cube,0,6,5,6,3,6,1,6,clockwise);
  curl(cube,2,clockwise);
}

void up(vector<vector<string>> &cube, bool clockwise) {
  swap(cube,2,0,3,0,4,0,0,8,clockwise);
  swap(cube,2,1,3,1,4,1,0,7,clockwise);
  swap(cube,2,2,3,2,4,2,0,6,clockwise);
  curl(cube,1,clockwise);
}

void middle(vector<vector<string>> &cube, bool clockwise) {
  swap(cube,2,3,3,3,4,3,0,5,clockwise);
  swap(cube,2,4,3,4,4,4,0,4,clockwise);
  swap(cube,2,5,3,5,4,5,0,3,clockwise);
}

void down(vector<vector<string>> &cube, bool clockwise) {
  swap(cube,4,6,3,6,2,6,0,2,clockwise);
  swap(cube,4,7,3,7,2,7,0,1,clockwise);
  swap(cube,4,8,3,8,2,8,0,0,clockwise);
  curl(cube,5,clockwise);
}

void body_up(vector<vector<string>> &cube, bool clockwise) {
  for (int i=0;i<9;i++) {
    swap(cube,0,i,1,i,3,i,5,i,clockwise);
  }
  curl(cube,4,clockwise);
  if (clockwise) {
    curl(cube,2,false);
  } else {
    curl(cube,2,true);
  }
}

void body_right(vector<vector<string>> &cube, bool clockwise) {
  for (int i=0;i<9;i++) {
    swap(cube,2,i,0,8-i,4,i,3,i,clockwise);
  }
  curl(cube,5,clockwise);
  if (clockwise) {
    curl(cube,1,false);
  } else {
    curl(cube,1,true);
  }
}

void swap(vector<vector<string>> &cube, int face1, int square1, int face2, int square2, int face3, int square3, int face4, int square4, bool clockwise) {
  if (clockwise) {
    string temp = cube[face1][square1];
    cube[face1][square1] = cube[face2][square2];
    cube[face2][square2] = cube[face3][square3];
    cube[face3][square3] = cube[face4][square4];
    cube[face4][square4] = temp;
  } else {
    string temp = cube[face1][square1];
    cube[face1][square1] = cube[face4][square4];
    cube[face4][square4] = cube[face3][square3];
    cube[face3][square3] = cube[face2][square2];
    cube[face2][square2] = temp;
  }
}

void curl(vector<vector<string>> &cube, int face, bool clockwise) {
  swap(cube,face,6,face,8,face,2,face,0,clockwise);
  swap(cube,face,7,face,5,face,1,face,3,clockwise);
}
