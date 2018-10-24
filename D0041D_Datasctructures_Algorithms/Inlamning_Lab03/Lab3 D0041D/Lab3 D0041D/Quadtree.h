#pragma once
#include <vector>
#define QUAD_TREE_UPLEFT_NAME nw				//name of upleft node
#define QUAD_TREE_UPRIGHT_NAME ne				//name of upright node
#define QUAD_TREE_DOWNLEFT_NAME sw				//name of downleft node
#define QUAD_TREE_DOWNNRIGHT_NAME se			//name of downright
#define QUAD_TREE_WIDTH_NAME width				//name on the width parameter for type quadtree
#define QUAD_TREE_HEIGHT_NAME height			//name on the height parameter for type quadtree
#define QUAD_TREE_ELEMENTS_NAME points			//name of the vector which contains the elements in the quadtree
#define QUAD_TREE_NUM_ELEMENTS_NAME MaxElements	//maximum number of elements contained in a quadtree 
#define QUAD_TREE_ELEMENT_DATA_NAME data		//name for the variable of the data
#define QUAD_TREE_ELEMENT_X_NAME x				// name of the variable which contains x position for element
#define QUAD_TREE_ELEMENT_Y_NAME y				// name of the variable which contains y position for element
using namespace std;

template <class T>
class QuadTree
{
#ifdef  BUILD_FOR_ASSISTANT
	friend class QuadTreeWindow;
#endif
public:
	QuadTree(void);																//< Default Constructor
	QuadTree(float x, float y);													//< Constructor to set position for a child/leaf
	~QuadTree(void){};															//<Destructor
	void Setup(int width, int height);											//<Set witdth and height for the whole tree
	bool InsertElement(const T& element);										//<Insert element(leaf) in tree
	void FindElement(int x, int y, int width, int height, vector<T>& output);	//<Fins element in the tree
	void Split();																//< Split the tree
	QuadTree<T> *ne;															//<North East child
	QuadTree<T> *se;															//<South East child
	QuadTree<T> *sw;															//<South West child
	QuadTree<T> *nw;															//<North West child
	float x,y;																	//<Position
	vector<T> points;
	float width;
	float height;

	static const int MaxElements = 4;
};

/*!Child nodes*/
template<class T>
struct QuadTreeElement
{
	QuadTreeElement(){};
	QuadTreeElement(float x, float y, T value);
	~QuadTreeElement(){};
	float x,y;
	T data;
};

/*!Constructor to set position and data
*@Param x, x-position
*@Param y, y-position
*@Param value, data to be stored
*/
template<class T>
QuadTreeElement<T>::QuadTreeElement(float x, float y, T value)
{
	this->x=x;
	this->y=y;
	data = value;
}


/*!Default Constructor */
template<class T>
QuadTree<T>::QuadTree()
{
	x=0.0f;
	y=0.0f;
	width = 0.0f;
	height = 0.0f;
	ne=nullptr;				
	se=nullptr;				
	sw=nullptr;				
	nw=nullptr;
}

/*!Set the position of child
*@Param float x, x-position
*@Param float y, y-position
*/
template <class T>
QuadTree<T>::QuadTree(float x, float y)
{
	this->x = x;
	this->y = y;
	this->width=0;
	this->height=0;
	ne=nullptr;				
	se=nullptr;				
	sw=nullptr;				
	nw=nullptr;
}

/*!Method to set witdth and height for the tree*/
template<class T>
void QuadTree<T>::Setup(int width, int height)
{
	this->width = float(width);
	this->height = float(height);

	if(nw != nullptr)			//<In case we delete a node we wanna maintain the structure of the tree
	{
		ne->x= width/2;
		ne->y=y;
		ne->Setup(width/2,height/2);
		se->x = width/2;
		se->y = height/2;
		se->Setup(width/2,height/2);
		sw->x= x;
		sw->y = height/2;
		sw->Setup(width/2,height/2);
		nw->x = x;
		nw->y=y;
		nw->Setup(width/2,height/2);
	}
}

/*!Split the tree to smaller trees*/
template<class T>
void QuadTree<T>::Split()
{
	
	ne = new QuadTree(x+width/2,y);
	ne->Setup(width/2,height/2);
	se = new QuadTree(x+width/2,y+height/2);
	se->Setup(width/2,height/2);
	sw = new QuadTree(x,y+height/2);
	sw->Setup(width/2,height/2);
	nw = new QuadTree(x,y);
	nw->Setup(width/2,height/2);
}

///*!Insert a new element to the tree*/
/*!
@param element, QuadTreeElement to insert in the tree
*/
template<class T>
bool QuadTree<T>::InsertElement(const T &element)
{
	if (element.x< x || element.x>width+x || element.y>height+y || element.y<y) return false; //<Check if the child that we wanna insert is within the tree boundary
	if(points.size() < QuadTree<T>::MaxElements)										//<Check if the tree is full and inserts if its not
	{	
		points.push_back(element);
		return true;
	}

	else if (nw==nullptr )							//<Split tree if original tree is full
	{
		if (height/2 <0.01 || width/2 <0.01) return false;  //<limit on how deep we can go inception style
		this->Split();	
	}

	//We check in which tree the node belongs to and inserts it if it belongs therre and is not full
	if (nw->InsertElement(element)==true) return true;			
	if (se->InsertElement(element)==true) return true;			
	if (sw->InsertElement(element)==true) return true;			
	if (ne->InsertElement(element)==true) return true;			
}	

/*!Find an element in the tree */
template<class T>
void QuadTree<T>::FindElement(int x, int y, int width, int height, std::vector<T>& output)
{
	if (this->points.size() == 0) return;
		
	if ( x > this->x + this->width || y > this->y + this->height || y + height < this->y || x + width < this->x)	return;		//<Checks if the search area overlaps the tree


	if (points.size()!=0)								//<As long as the tree's vector contains data we go forth
	{
		for(int i=0; i<points.size(); i++)
		{
			if (points[i].x <=x+width && points[i].y <= y+height && points[i].x>=x && points[i].y>=y)		//<If the node is withing the search area we insert that node to the output
				output.push_back(points.at(i));
				
		}
		if (points.size() <QuadTree::MaxElements) return;
	}

	if (nw == nullptr) return;	
	//Recursive calls to get all values in the search area
	nw->FindElement(x, y, width, height , output);				
	se->FindElement(x, y, width, height , output);				
	sw->FindElement(x, y, width, height , output);				
	ne->FindElement(x, y, width, height , output);				
}


