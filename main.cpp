/**
Brenda Escoto
escot105@mail.chapman.edu
April 22, 2019
**/
#include <iostream>
#include <ctime>

using namespace std;

void print(int b[50][50], int size)
{
  for(int i=0;i<size;i++)
  {
    for(int j=0;j<size;j++)
    {

      cout << b[i][j] << "\t";

    }
    cout << "\n\n";
  }
}

bool isFree(int x, int y, int b[50][50], int size)
{
  if(x>-1&&y>-1)//index can be zero
  {
    if(x<size&&y<size)//ex: size is 8; is x<8? index can go to size-1
    {
      if(b[x][y]<0)//in bounds
      {
          return true;
      }
    }
  }
  return false;

}

int traverseW(int x, int y, int delX[8], int delY[8], int b[50][50], int bSize, int moves)//warnsdorff traversal
{
  int xjump,yjump;
  int xx,yy;
  int xf,yf;
  int jumps=0;
  int least=20;

  if(moves==bSize*bSize)//solution found
  {
    print(b,bSize);

  }
  for(int i=0;i<8;i++)
  {
    xjump=x+delX[i];
    yjump=y+delY[i];

    if(isFree(xjump,yjump,b,bSize))
    {
      jumps=0;
      for(int j=0;j<8;j++)
      {
        xx=xjump+delX[j];
        yy=yjump+delY[j];
        if(isFree(xx,yy,b,bSize))
        {
          jumps++;
        }
      }

      if(jumps<least)
      {

        least=jumps;
        xf=xjump;
        yf=yjump;
      }
    }

  }
  if(isFree(xf,yf,b,bSize))
  {

    b[xf][yf]=moves;
    traverseW(xf,yf,delX,delY,b,bSize,moves+1);
  }
  return moves;

}

bool traverse(int x, int y, int delX[8], int delY[8], int b[50][50], int bSize, int moves)//brute force solution
{
  int xjump,yjump;
  if(moves==bSize*bSize)//solution found
  {
    print(b,bSize);
    return true;
  }
  for(int i=0;i<8;i++)
  {
    xjump=x+delX[i];
    yjump=y+delY[i];
    if(isFree(xjump,yjump,b,bSize))
    {
      b[xjump][yjump]=moves;
      if(traverse(xjump,yjump,delX,delY,b,bSize,moves+1))
      {
        return true;
      }
      else
      {
        b[xjump][yjump]=-5;//path did not work
      }
    }
  }

  return false;
}



bool solution(int xStart, int yStart, int boardSize, bool h)//called first
{

  int board[50][50];
  bool finished=false;

  int deltax[8]={2,1,-1,-2,-2,-1,1,2};//the moves that x can make
  int deltay[8]={1,2,2,1,-1,-2,-2,-1};//the moves that y can make

  int movesMade=0;


  for(int i=0;i<50;i++)
  {
    for(int j=0;j<50;j++)
      {
        board[i][j]=-1;
      }
  }

  clock_t stop = clock();
  clock_t start=clock();
  board[xStart][yStart]=0;//initial position


  if(h)//warnsdorff
  {
    traverseW(xStart, yStart, deltax, deltay, board, boardSize,1);
  }
  else//brute force
  {
    finished=traverse(xStart, yStart, deltax, deltay, board, boardSize,1);
    if(finished==false)
    {
      cout << "path not possible" << endl;
    }
  }

  stop = clock();

  double time = double(stop - start) / CLOCKS_PER_SEC;
  cout << "\ntime taken: " <<time<< " seconds" <<endl;
}



int main()
{
  int x,y,size;
  string h="";

  cout << "X Coordinate to start on: ";
  cin >> x;
  cout << "Y Coordinate to start on: ";
  cin >> y;
  cout << "Size of board: ";
  cin >> size;
  cout << "Heuristic? If yes, type '--h': ";
  cin >> h;

  if(x<size&&y<size)
  {
    if(h=="--h")
    {
      solution(x,y,size,true);
    }
    else
    {
      solution(x,y,size,false);
    }
  }
  else
  {
    cout << "Coordinates provided out of bounds." << endl;
  }

}
