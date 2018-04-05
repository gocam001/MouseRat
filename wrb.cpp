#include <iostream>
#include <stdlib.h>
#include <stack>

using namespace std;

struct cell{
  int distance;
  bool north, south, east, west;
};

struct current_location{
  int x, y;
  bool north, south, east, west;
};

cell maze[16][16];
current_location here;
stack<current_location> floodfill_stack;

void sense(){
  // depending on where the mouse is facing, update the here.walls accordingly
  //  Gian in charge of this
  // for the first sense() upon turning system on,
  // here.south should be default to false

  // if new walls are detected, add current cell into stack used for floodfill
  if((maze[here.x][here.y].north != here.north) ||
    (maze[here.x][here.y].south != here.south) ||
    (maze[here.x][here.y].east != here.east) ||
    (maze[here.x][here.y].west != here.west)){
      current_location temp0 = here;
      floodfill_stack.push(temp0);
      // ADD ALL CELLS ON THE OTHER SIDE OF NEWFOUND WALLS TO STACK
      // and then correct the maze to reflect the new walls
      if(maze[here.x][here.y].north != here.north){
        current_location temp1 = here;
        temp1.y += 1;
        floodfill_stack.push(temp1);
        maze[here.x][here.y].north = true;
      }
      if(maze[here.x][here.y].south != here.south){
        current_location temp2 = here;
        temp2.y -= 1;
        floodfill_stack.push(temp2);
        maze[here.x][here.y].south = true;
      }
      if(maze[here.x][here.y].east != here.east){
        current_location temp3 = here;
        temp3.x += 1;
        floodfill_stack.push(temp3);
        maze[here.x][here.y].east = true;
      }
      if(maze[here.x][here.y].west != here.west){
        current_location temp4 = here;
        temp4.x -= 1;
        floodfill_stack.push(temp4);
        maze[here.x][here.y].west = true;
      }
    }
    return;
}

void floodfill(){
  // while stack is not empty
    //current cell <- pop top of STACK
    //distance of current cell shoud be min of open neighbors + 1
    //if not, set it to that, and then push all open neighbors to stack



  // finding minimum of open neighbors
  while(!floodfill_stack.empty()){
    current_location temp = floodfill_stack.top();
    int temp_distance = 999;

    // flag to check if all open neighbors should be sent to stack
    bool isnot = false;

    if(!maze[temp.x][temp.y].north){
      if(maze[temp.x][temp.y+1].distance < temp_distance){
        temp_distance = maze[temp.x][temp.y+1].distance;
      }
    }
    if(!maze[temp.x][temp.y].south){
      if(maze[temp.x][temp.y-1].distance < temp_distance){
        temp_distance = maze[temp.x][temp.y-1].distance;
      }
    }
    if(!maze[temp.x][temp.y].east){
      if(maze[temp.x+1][temp.y].distance < temp_distance){
        temp_distance = maze[temp.x+1][temp.y].distance;
      }
    }
    if(!maze[temp.x][temp.y].west){
      if(maze[temp.x-1][temp.y].distance < temp_distance){
        temp_distance = maze[temp.x-1][temp.y].distance;
      }
    }

    // checking if current distance is distance of min(openneighbors) + 1
    // if not, change it to that min + 1 and add all open neighbors
    // to the current cell to stack
    if(!maze[temp.x][temp.y].north){
      if(maze[temp.x][temp.y+1].distance == temp_distance
      && (maze[temp.x][temp.y].distance != (maze[temp.x][temp.y+1].distance + 1))){
        maze[temp.x][temp.y].distance = maze[temp.x][temp.y+1].distance + 1;
        isnot = true;
      }
    }
    if(!maze[temp.x][temp.y].south){
      if(maze[temp.x][temp.y-1].distance == temp_distance
      && (maze[temp.x][temp.y].distance != (maze[temp.x][temp.y-1].distance + 1))){
        maze[temp.x][temp.y].distance = maze[temp.x][temp.y-1].distance + 1;
        isnot = true;
      }
    }
    if(!maze[temp.x][temp.y].east){
      if(maze[temp.x+1][temp.y].distance == temp_distance
      && (maze[temp.x][temp.y].distance != (maze[temp.x+1][temp.y].distance + 1))){
        maze[temp.x][temp.y].distance = maze[temp.x+1][temp.y].distance + 1;
        isnot = true;
      }
    }
    if(!maze[temp.x][temp.y].west){
      if(maze[temp.x-1][temp.y].distance == temp_distance
      && (maze[temp.x][temp.y].distance != (maze[temp.x-1][temp.y].distance + 1))){
        maze[temp.x][temp.y].distance = maze[temp.x-1][temp.y].distance + 1;
        isnot = true;
      }
    }

    if(isnot){ // adding all open neighbors to stack
      if(!maze[temp.x][temp.y].north){
        current_location temp0 = temp;
        temp0.y +=1;
        floodfill_stack.push(temp0);
      }
      if(!maze[temp.x][temp.y].south){
        current_location temp1 = temp;
        temp1.y -=1;
        floodfill_stack.push(temp1);
      }
      if(!maze[temp.x][temp.y].east){
        current_location temp2 = temp;
        temp2.x +=1;
        floodfill_stack.push(temp2);
      }
      if(!maze[temp.x][temp.y].west){
        current_location temp3 = temp;
        temp3.x -=1;
        floodfill_stack.push(temp3);
      }
    }

    floodfill_stack.pop();
  }
  return;
}


int main(){

  /////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < 16; i++) { // generate maze with no walls
    for (int j = 0; j < 16; j++) {

      maze[i][j].distance = 0; // center is goal = 0

      if(j < 8){
        if(i < 8){
          maze[i][j].distance = abs(7 - j) + abs(7 - i); // first quadrant
        }else{
          maze[i][j].distance = abs(7 - j) + abs(7 - i); // third quadrant
        }
      }else{
        if(i >= 8){
          maze[i][j].distance = abs(8 - j) + abs(8 - i); // fourth quadrant
        }else{
          maze[i][j].distance = abs(7 - j) + abs(7 - i); // second quadrant
        }
      }

      //cout << maze[i][j].distance << " ";

      if(i == 0){ // left wall
        maze[i][j].west = true;
        maze[i][j].east = false;
        if(j == 0){maze[i][j].south = true;} // bottom left corner
        else if(j == 15){maze[i][j].north = true;} // top left corner
        else{
          maze[i][j].south = false;
          maze[i][j].north = false;
        }
      }// left wall

      if(i == 15){ // right wall
        maze[i][j].east = true;
        maze[i][j].west = false;
        if(j == 0){maze[i][j].south = true;} // bottom right corner
        else if(j == 15){maze[i][j].north = true;} // top right corner
        else{
          maze[i][j].south = false;
          maze[i][j].north = false;
        }
      }// right wall

      if(j == 0){ // bottom wall
        maze[i][j].south = true;
        maze[i][j].north = false;
        if(i == 0){maze[i][j].east = true;} // bottom left corner
        else if(i == 15){maze[i][j].west = true;} // bottom right corner
        else{
          maze[i][j].east = false;
          maze[i][j].west = false;
        }
      }// bottom wall

      if(j == 0){ // top wall
        maze[i][j].north = true;
        maze[i][j].south = false;
        if(i == 0){maze[i][j].east = true;} // top left corner
        else if(i == 15){maze[i][j].west = true;} // top right corner
        else{
          maze[i][j].east = false;
          maze[i][j].west = false;
        }
      }// top wall

    }
    //cout << endl;
  } // generate maze with no walls
  /////////////////////////////////////////////////////////////////////////////

  // initialize current location
  here.x = 0;
  here.y = 0;
  here.north = false;
  here.south = true;
  here.west = true;
  here.east = true;

  return 0;

}
