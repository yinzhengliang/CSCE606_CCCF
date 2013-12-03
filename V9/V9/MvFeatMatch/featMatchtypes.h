/************************************************************************/
/* feature matching parameter type defination                                    */
/************************************************************************/
// #ifndef FEAT_MATCH_TYPES_XX
// #define FEAT_MATCH_TYPES_XX
/************************************************************************/
/* GHT                                                                  */
/************************************************************************/
#include <vector>
using namespace std;               

typedef struct{
	int x;                //x coordinate
	int y;                //y coordinate
	double gradient;      //gradient value         
}edgepoint;                        //edge point's sturcture

typedef struct{
	int x;                //x coordinate
	int y;                //y coordinate
	double gradient;      // gradient value
	int tindexx;          //partition index x coordinate
	int tindexy;          //partition index y coordinate
}tedgepoint;                       //edge image structure        

typedef struct{
	double gradient;      //gradient value
	int vx;               //x coordinate
	int vy;               //y coordinate
	int tindexx;          //partition index x coordinate
	int tindexy;          //partition index y coordinate
}table;                            //R-table single element structure

typedef vector<table> SRTable;     //R-table single index subset 
typedef vector<SRTable> RTable;    //R-table
typedef vector<edgepoint> Edgepoint;  //edge data structure

typedef struct{
    double cx;            //geometry positioning center x coordinate
	double cy;            //geometry positioning center y coordinate
}center;                           //GHT postitioning center

typedef struct{
	double x;             //x coordinate      
	double y;             //y coordinate
    double delta;         //first matching angle 
	int count;            //voting value
}PreResult;                        //multi-resolutons middle layer result                    

typedef struct{
    MvImage* m_model;     //module image 
	MvImage* m_blmodel;   //module image edge
	MvImage* m_mask;      //blurry area
	RTable rtable;        //R-table
	center ct;
	int my;
	int mx;
	int modellayer;            
	RTable  *rtable_lv;   
	MvImage ** m_blmodel_lv;
}GHTModel;                //module data structure

///////////////////////////////////////////////////////////////////

//General
typedef struct{
	int method;					//feature matching method

 	bool molNumMode;            
	int rindex;                 

	double acceptance;			
	double accuracy;			
 	double certainty;            
     
 	bool anglemode;             
 	double startAngle;          
 	double negAngle;			
 	double posAngle;			
 	double angleAccuracy;       
    
	bool ModelROI;             
 	int ModelPointX;		  
	int ModelPointY;           
 	int ModelROIX;             
 	int ModelROIY;		       
    
	bool TargetROI;          
	int TargetReferenceX;      
	int TargetReferenceY;
	int TargetROIX;
	int TargetROIY;
    
	int grayfactor;         
	int topsize;            
}MvFeatParam;                               

typedef struct{
	double rx;          
	double ry;          
	double delta;       
	double score;        
}MvFeatResultPoint;

typedef struct{
    int num;                               //number of result
	MvFeatResultPoint * featresultpoint;   //result pointers
}MvFeatResult;

