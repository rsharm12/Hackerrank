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

        int hstic;
        int g_cost;
        int fvalue;
        int curX, curY;
        char value;
        Node * parent;
};

Node::Node()
{
    hstic = 0;
    g_cost = 0;
    fvalue = 0;
    parent = NULL;  
    curX = 0;
    curY = 0;
    value = 0;
}

Node::~Node()
{
    delete parent;
    
}
// functor for sorting nodes
struct Node_comp 
{
    bool operator() (const Node* left, const Node* right) const 
    { 
       return left->fvalue < right->fvalue;
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
    
    list<Node*> openlst, closelst;
 
    // set up nodes
	for (int i = 0; i<r; i++) {
		for (int j = 0; j<c; j++) {
			cin >> grid[i*c + j]->value;
			grid[i*c + j]->curX = i;
			grid[i*c + j]->curY = j;
            		if(grid[i*c + j]->value == '-')
            		{
                		grid[i*c + j]->hstic = fabs(foodX-i)+fabs(foodY-j);
 
            		}
		}
	}   
    
    int xnext, ynext;
    int xcoord, ycoord;
    
    openlst.push_back(grid[pacX*c+pacY]);
    grid[pacX*c+pacY]->fvalue = grid[pacX*c+pacY]->g_cost + grid[pacX*c+pacY]->hstic;
    
    while(!openlst.empty())
    {
        
        //find the node with the least f on the open list
        openlst.sort(Node_comp());
        //pop q off the open list
        Node * currNode = new Node();
        currNode = openlst.front();
        openlst.pop_front();
        closelst.push_back(currNode);
        //generate q's 3 successors and set their parents to q
        xcoord = currNode->curX;
        ycoord = currNode->curY;
        
        if(grid[xcoord*c+ycoord] == grid[foodX*c+foodY]) 
        {
               break;
        }
        
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
           if( grid[xnext*c+ynext]->value != '%' && find(closelst.begin(), closelst.end(), grid[xnext*c+ynext]) == closelst.end())
           {    
               grid[xnext*c+ynext]->parent = grid[xcoord*c+ycoord];
               grid[xnext*c+ynext]->g_cost = grid[xcoord*c+ycoord]->g_cost + 1;
               grid[xnext*c+ynext]->fvalue = grid[xcoord*c+ycoord]->g_cost + grid[xnext*c+ynext]->hstic;
               if((std::find(openlst.begin(), openlst.end(), grid[xnext*c+ynext]) == openlst.end()))
               {
                   openlst.push_back(grid[xnext*c+ynext]);
               }
               else
               {
                   auto openIter = std::find(openlst.begin(), openlst.end(), grid[xnext*c+ynext]);
                   if(grid[xnext*c+ynext]->g_cost < (*openIter)->g_cost)
                   {
                      (*openIter)->g_cost =  grid[xnext*c+ynext]->g_cost;
                      (*openIter)->parent = grid[xnext*c+ynext]->parent;
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
