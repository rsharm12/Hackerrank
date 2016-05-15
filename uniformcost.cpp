#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>


using namespace std;

class Node
{
    public:
        Node();
        ~Node();

        int cost;
        int curX, curY;
        char value;
        Node * parent;
};

Node::Node()
{
    cost = 0;
    parent = NULL;  
    curX = 0;
    curY = 0;
    value = 0;
}

Node::~Node()
{
    delete parent;
    
}
struct Node_comp 
{
    bool operator() (const Node* left, const Node* right) const 
    { 
       return left->cost < right->cost;
    }
};



int main(void) 
{
    int foodX, foodY, pacX, pacY, r, c;
    
    cin >> pacX >> pacY;
    cin >> foodX >> foodY;
    cin >> r >> c;
    
    Node * grid[r*c];
    Node * nodePtr;
    // setup memory
    for (int z = 0; z < r*c; z++)
    {
        nodePtr = new Node();
        grid[z] = nodePtr;
    }
    
    // set up nodes
	for (int i = 0; i<r; i++) {
		for (int j = 0; j<c; j++) {
			cin >> grid[i*c + j]->value;
			grid[i*c + j]->curX = i;
			grid[i*c + j]->curY = j;
		}
	}   
    
    int xnext, ynext;
    int xcoord, ycoord;
    list<Node*> explored;
    list<Node*> frontier;
    frontier.push_back(grid[pacX*c+pacY]);
    
    
    while(!frontier.empty())
    {
       frontier.sort(Node_comp());

       Node * currNode = new Node();
       currNode = frontier.front();
       frontier.pop_front();

       xcoord = currNode->curX;
       ycoord = currNode->curY;
        
       if(grid[xcoord*c+ycoord] == grid[foodX*c+foodY]) 
       {
           break;       
       }
        
       explored.push_back(grid[xcoord*c+ycoord]);
        
       for(int l=0; l < 4; l++)
	   {
		  //up
		  if(l==0)
		  {
                ynext=ycoord-1;
		        xnext=xcoord;
          }
          //left		
          if(l==1)
	      {
                ynext=ycoord;
		        xnext=xcoord-1;
		  }
           	//right		
          if(l==2)
		  {
                ynext=ycoord;
               	xnext=xcoord+1;
		  }
          //down
		  if(l==3)
		  {
                ynext=ycoord+1;
                xnext=xcoord;
		  }   
          if( grid[xnext*c+ynext]->value != '%'&& find(explored.begin(), explored.end(), grid[xnext*c+ynext]) == explored.end())
          {    
              grid[xnext*c+ynext]->parent = grid[xcoord*c+ycoord];
              grid[xnext*c+ynext]->cost = grid[xcoord*c+ycoord]->cost + 1;
  
              if(find(frontier.begin(), frontier.end(), grid[xnext*c+ynext]) == frontier.end() )
              {
                  frontier.push_back(grid[xnext*c+ynext]);
              }
              else
              {
                  auto frontIter = std::find(frontier.begin(), frontier.end(), grid[xnext*c+ynext]);
                  if(grid[xnext*c+ynext]->cost < (*frontIter)->cost)
                  {
                      (*frontIter)->cost =  grid[xnext*c+ynext]->cost;
                      (*frontIter)->parent = grid[xnext*c+ynext]->parent;
                  }
              }
          }
       }
    }
  
    std::vector<std::pair<int, int>> coords;
    Node * goal = new Node();
    goal = grid[foodX*c+foodY];
    while(goal->parent != NULL)
    {
        goal = goal->parent;
        coords.push_back( std::pair<int,int>(goal->curX, goal->curY) );
    }    
    
    cout << coords.size() << endl;
    for(int m = coords.size()-1; m >= 0; m--)
    {
        cout << coords[m].first << " " << coords[m].second << endl;

    }
    cout << foodX << " " << foodY << endl;

    
    // clear memory
    for (int q = 0; q < r*c; q++)
    {
        delete grid[q];
        grid[q] = NULL;
    }


    return 0;
}
