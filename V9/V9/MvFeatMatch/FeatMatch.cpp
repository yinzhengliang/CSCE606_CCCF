#include "stdafx.h"
#include "FeatMatch.h"
#include "../demo/mv.h"
#include "../mvCore/numericalCal.h"
#define TILE_LENGTH 15
#define GHT_TOP_FACTOR 0.90
#define GHT_LV_FACTOR  0.98
/***************************************************************/
//function name£ºGHTSobelEdge
//input: source image mimg, edge image simg mode£¨0£¬1£©£¬edge extract threshhold
//output: edge vector storage of edge information
//function£ºuse Sobel algorithm to extract edge information and storage
//Created on 2013.10.26 by Xiang Cheng, Yang Song
/***************************************************************/
bool GHTSobelEdge(MvImage * mimg,MvImage * simg, int mode,vector<edgepoint> *edgepoints,int threshold)
{
	double gx=0,gy=0;
	double gradient=0;
	edgepoint ep; 
    double pi=3.1415926;
	
	uchar * mimgdata = (uchar *)mimg->imageData;
	uchar * simgdata=(uchar *)simg->imageData;     

	int ttmin=0;
		
	for(int i=2;i<mimg->height-2;i++)
	{
		for(int j=2;j<mimg->width-2;j++)
		{
			gx =
				-mimgdata[(i-1) * mimg->widthStep + j-1] 
				+mimgdata[(i-1) * mimg->widthStep + j+1] 
				-2*mimgdata[i * mimg->widthStep + j-1] 
				+2*mimgdata[i * mimg->widthStep + j+1] 
				-mimgdata[(i+1) * mimg->widthStep + j-1] 
				+mimgdata[(i+1) * mimg->widthStep + j+1];
			
			gy=
				-mimgdata[(i-1) * mimg->widthStep + j-1] 
				+mimgdata[(i+1) * mimg->widthStep + j-1] 
				-2*mimgdata[(i-1) * mimg->widthStep + j] 
				+2*mimgdata[(i+1) * mimg->widthStep + j] 
				-mimgdata[(i-1) * mimg->widthStep + j+1] 
				+mimgdata[(i+1) * mimg->widthStep + j+1];
			
			if(abs(gx)>=threshold||abs(gy)>=threshold)
			{
				if(mode==1)
				{
					ttmin=(int)mimgdata[(i-1) * mimg->widthStep + j-1]+(int)mimgdata[(i-1) * mimg->widthStep + j]+(int)mimgdata[(i-1) * mimg->widthStep + j+1]
						+(int)mimgdata[i * mimg->widthStep + j-1]+(int)mimgdata[i * mimg->widthStep + j]+(int)mimgdata[i * mimg->widthStep + j+1]
						+(int)mimgdata[(i+1) * mimg->widthStep + j-1]+(int)mimgdata[(i+1) * mimg->widthStep + j]+(int)mimgdata[(i+1) * mimg->widthStep + j+1];
				    ttmin=ttmin/9;
				}
				
				if((mimgdata[i * mimg->widthStep + j]<=ttmin&&mode==1)||mode==0)
				{
					simgdata[i * mimg->widthStep + j]=255;
					
					if(gx>0&&gy>0)
					{
						gradient=atan(gy/gx);
					}
					else if(gx>0&&gy<0)
					{
						gradient=atan(gy/gx)+2*pi;
					}
					else if(gx<0&&gy>0)
					{
						gradient=atan(gy/gx)+pi;
					}
					else if(gx<0&&gy<0)
					{
						gradient=atan(gy/gx)+pi;
					}
					else if(gx==0&&gy>0)
					{
						gradient=pi/2;
					}
					else if(gx==0&&gy<0)
					{
						gradient=3*pi/2;
					}
					else if(gx>=0&&gy==0)
					{
						gradient=0;
					}
					else if(gx<0&&gy==0)
					{
						gradient=pi;
					}
					else 
					{
						gradient=0;
					}						
					ep.gradient=gradient;
					ep.x=j;
					ep.y=i;
					edgepoints->push_back(ep);
				}
			    else
				{
				    simgdata[i * mimg->widthStep + j]=0;
				}
			}           
			else
			{
				simgdata[i * mimg->widthStep + j]=0;
			}
		}
	}
	
	for (i=0; i<mimg->height; i++)
	{
		simgdata[i*mimg->widthStep]=0;
		simgdata[i*mimg->widthStep+mimg->width-1]=0;
	}		
	for (int j=0; j<mimg->widthStep; j++)
	{	 
		simgdata[j]=0;
		simgdata[(mimg->height-1)*mimg->widthStep+j]=0;				
	}
	return TRUE;
}

/***************************************************************/
//Function name£ºGHTSuImgEdgeExtract
//input: source image mimg edge image simg the top of the pyramid priori information mode(0£¬1)
//output: edge vector storage of edge information
//function: use Sobel algorithm to extract edge information and storage from the central portion
//Created on 2013.10.26 by Xiang Cheng, Yang Song
/***************************************************************/
bool GHTSuImgEdgeExtract(MvImage *img, MvImage *emask, PreResult preresult,int threshold,vector<tedgepoint> *sedgepoints, int tilelength,int mode)
{
   double gx=0;
   double gy=0;
   double gradient=0;
   double pi=3.1415926;
   tedgepoint ep; 
   sedgepoints->clear();
   int ttmin=0;

   int i=0;
   int j=0;
   int roih=emask->height;
   int roiw=emask->width;

   int centerx=preresult.x;
   int centery=preresult.y;
  
   uchar * imgdata = (uchar *)img->imageData;
   uchar * emaskdata=(uchar *)emask->imageData;     

   int imgindexx;
   int imgindexy;

   for(i=1;i<roih-1;i++)
   {
	   for(j=1;j<roiw-1;j++)
	   {
           if(emaskdata[i*emask->widthStep+j]>0)
		   {
			   imgindexx=(centerx-roiw/2)+j;
			   imgindexy=(centery-roih/2)+i;

			   if (imgindexx<5||imgindexy<5||imgindexx>img->width-5||imgindexy>img->height-5)
				   break;
               
			   gx =
			    	-imgdata[(imgindexy-1) * img->widthStep + imgindexx-1] 
			    	+imgdata[(imgindexy-1) * img->widthStep + imgindexx+1] 
			    	-2*imgdata[imgindexy * img->widthStep + imgindexx-1] 
			    	+2*imgdata[imgindexy * img->widthStep + imgindexx+1] 
			    	-imgdata[(imgindexy+1) * img->widthStep + imgindexx-1]  
			    	+imgdata[(imgindexy+1) * img->widthStep + imgindexx+1];
			
			   gy=
			    	-imgdata[(imgindexy-1) * img->widthStep + imgindexx-1] 
			    	+imgdata[(imgindexy+1) * img->widthStep + imgindexx-1] 
			    	-2*imgdata[(imgindexy-1) * img->widthStep + imgindexx] 
			    	+2*imgdata[(imgindexy+1) * img->widthStep + imgindexx] 
			    	-imgdata[(imgindexy-1) * img->widthStep + imgindexx+1] 
			    	+imgdata[(imgindexy+1) * img->widthStep + imgindexx+1];

			     if(abs(gx)>=threshold||abs(gy)>=threshold)
				 {
					 if(mode==1)
					 {
						 ttmin=(int)imgdata[(i-1) * img->widthStep + j-1]+(int)imgdata[(i-1) * img->widthStep + j]+(int)imgdata[(i-1) * img->widthStep + j+1]
							 +(int)imgdata[i * img->widthStep + j-1]+(int)imgdata[i * img->widthStep + j]+(int)imgdata[i * img->widthStep + j+1]
							 +(int)imgdata[(i+1) * img->widthStep + j-1]+(int)imgdata[(i+1) * img->widthStep + j]+(int)imgdata[(i+1) * img->widthStep + j+1];
						 ttmin=ttmin/9;
					 }

					 if((imgdata[i * img->widthStep + j]<=ttmin&&mode==1)||mode==0)
					 {
				        if(gx>0&&gy>0)
						{
					        gradient=atan(gy/gx);
						}
				        else if(gx>0&&gy<0)
						{
					         gradient=atan(gy/gx)+2*pi;
						}
				        else if(gx<0&&gy>0)
						{
					         gradient=atan(gy/gx)+pi;
						}
				        else if(gx<0&&gy<0)
						{
					         gradient=atan(gy/gx)+pi;
						}
				        else if(gx==0&&gy>0)
						{ 
					         gradient=pi/2;
						}
				        else if(gx==0&&gy<0)
						{
					         gradient=3*pi/2;
						}
				        else if(gx>=0&&gy==0)
						{
					         gradient=0;
						}
				        else if(gx<0&&gy==0)
						{
					         gradient=pi;
						}
				        else 
						{
					         gradient=0;
						}

				        ep.gradient=gradient;
				        ep.x=imgindexx;
				        ep.y=imgindexy;
				        ep.tindexx=(j)/tilelength;
				        ep.tindexy=(i)/tilelength;
				        sedgepoints->push_back(ep);
				  }
			   }
		   }
	   }
   }
   return TRUE;
}

/***************************************************************/
//Function name£ºGHTDilate
//input: source image simg expansion number n
//output: NULL
//function: use Sobel algorithm to extract edge information and storage from the central portion
//Created on 2013.10.26 by Xiang Cheng
/***************************************************************/
bool GHTDilate(MvImage *simg,int n)
{
	int nn=0;
    int i=0;
	int j=0;
	int k=0;
    int w=simg->width;
	int h=simg->height;
	int ws=simg->widthStep;
    
	MvImage * img;
	img=CreateImage(w,h,8,1);
	mvZero(img);
	
	uchar * sdata = (uchar *)simg->imageData;
	uchar * data  = (uchar *)img->imageData;
	
	for(nn=0;nn<n;nn++)
	{
		for(i=1;i<h-1;i++)
		{
			for(j=1;j<w-1;j++)
			{
				if(sdata[i*ws+j]!=0)
				{
					data[(i-1)*ws+j]=255;
					data[i*ws+j-1]=255;
					data[i*ws+j]=255;
					data[i*ws+j+1]=255;
					data[(i+1)*ws+j]=255;
				}
			}
		}
		for(i=0;i<h;i++)
		{
			for(j=0;j<w;j++)
			{
                k=i*ws+j;
				sdata[k]=data[k];
			}
		}
    }
	return TRUE;
}

/***************************************************************/
//function name: GHTLayerMatch
//input: the length, width, height of object image in current value of resolution and its R-table£¬related with the edge vector
//output: the matching result of current layer 
//function: use the prior value in matching in one of the layer of pyramid
//Created on 2013.10.26 by Xiang Cheng
/***************************************************************/
bool GHTLayerMatch(int row,int column, RTable *rtable_layer,vector<tedgepoint> *sepoints, PreResult& current_result,bool tile)
{
	int   ai=0;
	int   aj=0;
	int   **   pMatrix; 
	pMatrix   =   new   int   *   [row]; 
	for(ai   =   0;   ai   <   row;   ai++) 
	{ 
		pMatrix   [ai]   =   new   int   [column]; 
	} 
	
	//over 
	for(ai   =0;   ai <   row;   ai++) 
	{ 
		for(aj   =   0;   aj   <   column;   aj++) 
		{ 
			pMatrix[ai][aj]   =   0; 
		} 
	} 
	
	//stepII2 vote
	//consider tile restrictions
	int votex=0;
	int votey=0;
	
	for(int slen=0;slen<sepoints->size();slen++)
	{   
		for(int cr=0;cr<rtable_layer->size();cr++)
		{	
			if(   (sepoints->at(slen).gradient<=rtable_layer->at(cr).at(0).gradient+0.0087*3)              //in gradient space
				&& (sepoints->at(slen).gradient>=rtable_layer->at(cr).at(0).gradient-0.0087*3)   )       
			{
				for(int csrt=0;csrt<rtable_layer->at(cr).size();csrt++)
				{
					if(abs(sepoints->at(slen).tindexx-rtable_layer->at(cr).at(csrt).tindexx)<=1 && abs(sepoints->at(slen).tindexy-rtable_layer->at(cr).at(csrt).tindexy)<=1&&tile==TRUE)
					{
						votex=sepoints->at(slen).x+rtable_layer->at(cr).at(csrt).vx;                         //relocate central 
						votey=sepoints->at(slen).y+rtable_layer->at(cr).at(csrt).vy;
						
						if( (votex>=0&&votex<column) && (votey>=0&&votey<row) )
						{
							pMatrix[votey][votex]++;
						}
					}
					
					else if(tile==FALSE)
					{
						votex=sepoints->at(slen).x+rtable_layer->at(cr).at(csrt).vx;                         //relocate central 
						votey=sepoints->at(slen).y+rtable_layer->at(cr).at(csrt).vy;
						
						if( (votex>=0&&votex<column) && (votey>=0&&votey<row) )
						{
							pMatrix[votey][votex]++;
						}
					}
				}
			}			   
		}
		
	}
	
	//stepIII find maximum values order all elements in line
	int max=0;
	votex=0;
    votey=0;
	for(ai   =0;   ai <   row;   ai++) 
	{ 
		for(aj   =   0;   aj   <   column;   aj++) 
		{ 
			if(max<=pMatrix[ai][aj])
			{
				max=pMatrix[ai][aj];
				votex=aj;
				votey=ai;
			} 
		} 
	} 

    SUBPIXMODIFIER3(pMatrix,row,column,votex,votey,&(current_result.x),&(current_result.y));
	current_result.count=max;

	for(ai   =   0;   ai   <   row;   ai++) 
	{ 
		delete pMatrix[ai];
	} 
	delete pMatrix;
			 
    return TRUE;
}


/***************************************************************/
//function name£ºSGHTPreProcessModel
//input: matching module pointers in single angle, external parameter structure pointers 
//output£ºNULL
//Function: GHT method extract data from matching module
//Created on 2013.10.09 by Yang Song
/***************************************************************/
bool SGHTPreProcessModel(GHTModel* ghtmodel,MvFeatParam* featparam)
{      
	   //extract data for rtable
	   //pre-process image
       //mvMedian(m_model,m_model);
       
	   //build up 22 pyramid
	   //determine layers automatically
	   double pi=3.1415926;
       int mw=ghtmodel->m_model->width;
	   int mh=ghtmodel->m_model->height;
	   int mwth=ghtmodel->m_model->widthStep;
	   int layer=0;
       int topsize=featparam->topsize;
	   
	   if(mw>8*topsize&&mh>8*topsize)
	   {
           layer=4;
	   }
	   else if(mw>=4*topsize&&mh>=4*topsize)
	   {
           layer=3;
	   }
	   else if(mw>=2*topsize&&mh>=2*topsize)
	   {
		   layer=2;
	   }
	   else if(mw>=topsize&&mh>=topsize)
	   {
		   layer=1;
	   }
	   else
	   {
		   //report error
	   }
	   ghtmodel->modellayer=layer;

	   vector<edgepoint> *modelepoints=new vector<edgepoint>;

	   //extract edge information & create blurred image 
	   ghtmodel->m_blmodel=CreateImage(ghtmodel->m_model->width,ghtmodel->m_model->height,8,1);
	   ghtmodel->m_mask=CreateImage(ghtmodel->m_model->width+TILE_LENGTH*2,ghtmodel->m_model->height+TILE_LENGTH*2,8,1);       //modification pending
	   mvZero(ghtmodel->m_mask);
	   GHTSobelEdge(ghtmodel->m_model,ghtmodel->m_blmodel,1,modelepoints,featparam->grayfactor);

       uchar * edgedata = (uchar *)ghtmodel->m_blmodel->imageData;
	   uchar * maskdata = (uchar *)ghtmodel->m_mask->imageData;
  	   int maskwidth=ghtmodel->m_mask->widthStep;
	   int i;
	   int j;
	   for(i=0;i<mh;i++)
	   {
		   for(j=0;j<mw;j++)
		   { 
               	maskdata[(i+TILE_LENGTH)*maskwidth+(j+TILE_LENGTH)]=edgedata[i*mwth+j];
		   }
	   }
	                                                                                        
	   //build bottom rtable
	   int gradientsum=360;
	   double deltaradient=2*pi/360;
       vector<table> srtable; 
	   table tb;
	   ghtmodel->ct.cx=0.0;
       ghtmodel->ct.cy=0.0;
	   ghtmodel->rtable.clear();

	   for(i=0;i<modelepoints->size();i++)
	   {
		   ghtmodel->ct.cx+=modelepoints->at(i).x;
		   ghtmodel->ct.cy+=modelepoints->at(i).y;
	   }
	   ghtmodel->ct.cx=ghtmodel->ct.cx/(modelepoints->size());
       ghtmodel->ct.cy=ghtmodel->ct.cy/(modelepoints->size());
	   ghtmodel->ct.cx=(int)(ghtmodel->ct.cx+0.5);
	   ghtmodel->ct.cy=(int)(ghtmodel->ct.cy+0.5);
	   ghtmodel->mx=ghtmodel->ct.cx;
	   ghtmodel->my=ghtmodel->ct.cy;
	   
       for(int gradindex=0;gradindex<gradientsum;gradindex++)
	   {
		   for(int en=0;en<modelepoints->size();en++)
		   {
 	             if((modelepoints->at(en).gradient>gradindex*deltaradient-0.0087) && (modelepoints->at(en).gradient<gradindex*deltaradient+0.0087))   //parameters need to be refined here
				 {
					 tb.vx=ghtmodel->ct.cx-modelepoints->at(en).x;
					 tb.vy=ghtmodel->ct.cy-modelepoints->at(en).y;
                     tb.gradient=gradindex*deltaradient;
                     tb.tindexx=modelepoints->at(en).x/TILE_LENGTH+1;                             //for tile structure
					 tb.tindexy=modelepoints->at(en).y/TILE_LENGTH+1;                             //for tile structure
					 srtable.push_back(tb);                                                      //save calculation efforts here
				 }                                                                                //vector targeted sectors use new/delete
		   }                                                                                    //relevant medias defined as temporary parameters
		   
		   if(!srtable.empty())
		   {
			   ghtmodel->rtable.push_back(srtable);                                               
		   }
		   srtable.clear();
		}
       
	   //multiple layers needed
	   if(layer>=2)
	   {
           //Necessary structures:
           MvImage** m_model_lv=new MvImage*[layer-1];
		   ghtmodel->m_blmodel_lv=new MvImage*[layer-1];
           vector<edgepoint> *modelepoints_lv=new vector<edgepoint>[layer-1];
		   ghtmodel->rtable_lv=new RTable[layer-1];
		   
           BuildPyramid(ghtmodel->m_model,m_model_lv,layer-1);
		   
           //extract edge information & create blurred image 
		   GHTDilate(ghtmodel->m_mask,12);
		   for(i=0;i<layer-1;i++)
		   {
               ghtmodel->m_blmodel_lv[i]=CreateImage(m_model_lv[i]->width,m_model_lv[i]->height,m_model_lv[i]->depth,1);
		   }
		   for(i=0;i<layer-1;i++)
		   {
			   GHTSobelEdge(m_model_lv[i],ghtmodel->m_blmodel_lv[i],0,&modelepoints_lv[i],featparam->grayfactor);
		       GHTDilate(ghtmodel->m_blmodel_lv[i],(layer-i-1)*2);
		   }
		   
		   //build higher level R-tables
           for(i=0;i<layer-1;i++)
		   {
			   ghtmodel->ct.cx=0;
			   ghtmodel->ct.cy=0;
			   ghtmodel->rtable_lv[i].clear();
			   for(int j=0;j<modelepoints_lv[i].size();j++)
			   {
				   ghtmodel->ct.cx+=modelepoints_lv[i].at(j).x;
				   ghtmodel->ct.cy+=modelepoints_lv[i].at(j).y;
			   }
			   ghtmodel->ct.cx=ghtmodel->ct.cx/(modelepoints_lv[i].size());
			   ghtmodel->ct.cy=ghtmodel->ct.cy/(modelepoints_lv[i].size());
			   ghtmodel->ct.cx=(int)(ghtmodel->ct.cx+0.5);
			   ghtmodel->ct.cy=(int)(ghtmodel->ct.cy+0.5);
			   for(gradindex=0;gradindex<gradientsum;gradindex++)
			   {
				   for(int en=0;en<modelepoints_lv[i].size();en++)
				   {
					   if((modelepoints_lv[i].at(en).gradient>gradindex*deltaradient-0.0087) && (modelepoints_lv[i].at(en).gradient<gradindex*deltaradient+0.0087))   //parameters need to be refined here
					   {
						   tb.vx=ghtmodel->ct.cx-modelepoints_lv[i].at(en).x;
						   tb.vy=ghtmodel->ct.cy-modelepoints_lv[i].at(en).y;
						   tb.gradient=gradindex*deltaradient;
						   tb.tindexx=modelepoints_lv[i].at(en).x/TILE_LENGTH*(i+2);                             //for tile structure
						   tb.tindexy=modelepoints_lv[i].at(en).y/TILE_LENGTH*(i+2);
						   srtable.push_back(tb);                                                      //save calculation efforts here
					   }                                                                                //vector targeted sectors use new/delete
				   }                                                                                    //relavant medias defined as temporary parameters
				   
				   if(!srtable.empty())
				   {
					   ghtmodel->rtable_lv[i].push_back(srtable);                                               
				   }
				   srtable.clear();
			   }
		   }

           //clear used elements   
		   for(i=0;i<layer-1;i++)
		   {
			   ReleaseImage(m_model_lv[i]);
		   }
		   delete m_model_lv;
		   delete []modelepoints_lv;
	   }
	   delete modelepoints;
	   return TRUE;
}

/***************************************************************/
//Function name£ºSGHTFindModel
//input: object image, matching module pointers in single angle, external parameter structure pointers, result storage pointers
//output: matching result (success/failure)
//Function£ºGHT application in matching single image in non-rotation environment
//Created on 2011.10.19 by Xiang Chen
/***************************************************************/
bool SGHTFindModel(MvImage* m_image,GHTModel* featmodel,MvFeatParam* featparam,MvFeatResult* featresult)
{
	//preprocess image
	int sobelthresh=featparam->grayfactor;
   	int w=m_image->width;
	int h=m_image->height;
	int layer=featmodel->modellayer;
    MvImage* pimage;
	MvImage ** m_image_lv; 
//	Edgepoint imagepoints;
	Edgepoint imagetoppoints;

	if(featmodel->m_mask->height>=m_image->height||featmodel->m_mask->width>=m_image->width)
	{
		layer=1;
	}
    
	if(layer==1)
	{
		pimage= CreateImage(w,h,8,1);
		mvZero(pimage);
        GHTSobelEdge(m_image,pimage,0,&(imagetoppoints),sobelthresh);
	}
	else if(layer>1)
	{
        m_image_lv=new MvImage*[layer-1];
        BuildPyramid(m_image,m_image_lv,layer-1);
        //test
		pimage= CreateImage(m_image_lv[layer-2]->width,m_image_lv[layer-2]->height,8,1);
		mvZero(pimage);
        GHTSobelEdge(m_image_lv[layer-2],pimage,0,&(imagetoppoints),sobelthresh);
	}
	else
	{
		return FALSE;
	}
	
	//ght match
	//opening up result space	
	if(layer==1)
	{
		int   row=m_image->height; 
		int   column=m_image->width;
		int   ai=0;
		int   aj=0;
		int   **   pMatrix; 
		pMatrix   =   new   int   *   [row]; 
		for(ai   =   0;   ai   <   row;   ai++) 
		{ 
			pMatrix   [ai]   =   new   int   [column]; 
		} 
		
		//over 
		for(ai   =0;   ai <   row;   ai++) 
		{ 
			for(aj   =   0;   aj   <   column;   aj++) 
			{ 
				pMatrix[ai][aj]   =   0; 
			} 
		} 
		//stepII2 vote
		int votex=0;
		int votey=0;
		
		for(int slen=0;slen<imagetoppoints.size();slen++)
		{
			for(int cr=0;cr<featmodel->rtable.size();cr++)
			{
				if(   (imagetoppoints.at(slen).gradient<=featmodel->rtable.at(cr).at(0).gradient+0.0087*2)              //in gradient space
					&& (imagetoppoints.at(slen).gradient>=featmodel->rtable.at(cr).at(0).gradient-0.0087*2)   )       
				{
					for(int csrt=0;csrt<featmodel->rtable.at(cr).size();csrt++)
					{
						votex=imagetoppoints.at(slen).x+featmodel->rtable.at(cr).at(csrt).vx;                         //relocate central 
						votey=imagetoppoints.at(slen).y+featmodel->rtable.at(cr).at(csrt).vy;
						
						if( (votex>=0&&votex<column) && (votey>=0&&votey<row) )
						{
							pMatrix[votey][votex]++;
						}
						
					}
				}
			}
		}		
		//stepIII find maximum value
		int max=0;
		votex=0;
		votey=0;
		for(ai   =0;   ai <   row;   ai++) 
		{ 
			for(aj   =   0;   aj   <   column;   aj++) 
			{ 
				if(max<=pMatrix[ai][aj])
				{
					max=pMatrix[ai][aj];
					votex=aj;
					votey=ai;
				} 
			} 
		} 
		
		double votexx=0;
		double voteyy=0;
        SUBPIXMODIFIER3(pMatrix,row,column,votex,votey,&votexx,&voteyy);

		featresult->featresultpoint->rx=votexx+(double)(featmodel->m_model->width-1)/2-featmodel->mx;  
		featresult->featresultpoint->ry=voteyy+(double)(featmodel->m_model->height-1)/2-featmodel->my;
		featresult->featresultpoint->delta=0;
		
		for(ai   =   0;   ai   <   row;   ai++) 
		{ 
			delete pMatrix[ai];
		} 
		delete pMatrix;
	}

    else if(layer>1)
	{
	         //top level
	         //stepII1 open up parameter spaces ready match prerequisites
		 	 //generating voting space  
		 	 int   row=m_image_lv[layer-2]->height; 
		 	 int   column=m_image_lv[layer-2]->width;
		 	 int   ai=0;
		 	 int   aj=0;
		 	 int   **   pMatrix; 
		 	 pMatrix   =   new   int   *   [row]; 
		 	 for(ai   =   0;   ai   <   row;   ai++) 
		 	 { 
		 		 pMatrix   [ai]   =   new   int   [column]; 
		 	 } 
		 	 
		 	 //over 
		 	 for(ai   =0;   ai <   row;   ai++) 
		 	 { 
		 			 for(aj   =   0;   aj   <   column;   aj++) 
		 			 { 
		 				 pMatrix[ai][aj]   =   0; 
		 			 } 
		 	 } 
		     //stepII2 vote
		     int votex=0;
		 	 int votey=0;
		 
		     for(int slen=0;slen<imagetoppoints.size();slen++)
			 {
		         for(int cr=0;cr<featmodel->rtable_lv[layer-2].size();cr++)
				 {
		 			if(   (imagetoppoints.at(slen).gradient<=featmodel->rtable_lv[layer-2].at(cr).at(0).gradient+0.0087*3)         //Èö¹þ´ï¹þµÂ±ÆÐÔ in gradient space
		 				&& (imagetoppoints.at(slen).gradient>=featmodel->rtable_lv[layer-2].at(cr).at(0).gradient-0.0087*3)   )       
		 			{
		 				for(int csrt=0;csrt<featmodel->rtable_lv[layer-2].at(cr).size();csrt++)
		 				{
		 					votex=imagetoppoints.at(slen).x+featmodel->rtable_lv[layer-2].at(cr).at(csrt).vx;                         //relocate central 
		 					votey=imagetoppoints.at(slen).y+featmodel->rtable_lv[layer-2].at(cr).at(csrt).vy;
		 
		 					if( (votex>=0&&votex<column) && (votey>=0&&votey<row) )
		 					{
		 					    pMatrix[votey][votex]++;
		 					}
		 
		 				}
		 			}
				 }
			 }
		    
		     //stepIII find maximum values on top layer order all elements in line
			 //last stand on stage I
             vector<PreResult> result_of_top;
			 result_of_top.clear();
             
		     int max=0;
			 PreResult toppre;
             toppre.count=0;
			 toppre.x=0;
			 toppre.y=0;

			 votex=0;
		 	 votey=0;
		     for(ai   =0;   ai <   row;   ai++) 
			 { 
		 		for(aj   =   0;   aj   <   column;   aj++) 
		 		{ 
		 			if(max<=pMatrix[ai][aj])
					{
		 				max=pMatrix[ai][aj];
		 				votex=aj;
		 				votey=ai;
		 			} 
		 		} 
			 } 
//f=k0+k1y+k2y2+k3xy+k4x+k5x2
//33
             for(ai=1;ai<row-1;ai++)
			 {
				 for(aj=1;aj<column-1;aj++)
				 {
                      if(pMatrix[ai][aj]>GHT_TOP_FACTOR*max)
					  {
                           if( pMatrix[ai][aj]>=pMatrix[ai-1][aj-1]&&pMatrix[ai][aj]>=pMatrix[ai-1][aj]&&pMatrix[ai][aj]>=pMatrix[ai-1][aj+1]						
							   &&pMatrix[ai][aj]>=pMatrix[ai][aj-1]&&pMatrix[ai][aj]>=pMatrix[ai][aj+1]
							   &&pMatrix[ai][aj]>=pMatrix[ai+1][aj-1]&&pMatrix[ai][aj]>=pMatrix[ai+1][aj]&&pMatrix[ai][aj]>=pMatrix[ai+1][aj+1]
							 )
						   {   
                               toppre.count=pMatrix[ai][aj];
							   SUBPIXMODIFIER3(pMatrix,row,column,votex,votey,&(toppre.x),&(toppre.y));
							   result_of_top.push_back(toppre);
							   pMatrix[ai][aj]++;						   
						   }
					  }
				 }
			 }

//55             
//              for(ai=2;ai<row-2;ai++)
// 			 {
// 				 for(aj=2;aj<column-2;aj++)
// 				 {
//                       if(pMatrix[ai][aj]>GHT_TOP_FACTOR*max)
// 					  {
//                            if( pMatrix[ai][aj]>=pMatrix[ai-2][aj-2]&&pMatrix[ai][aj]>=pMatrix[ai-2][aj-1]&&pMatrix[ai][aj]>=pMatrix[ai-2][aj]&&pMatrix[ai][aj]>=pMatrix[ai-2][aj+1]&&pMatrix[ai][aj]>=pMatrix[ai-2][aj+2]
// 							   &&pMatrix[ai][aj]>=pMatrix[ai-1][aj-2]&&pMatrix[ai][aj]>=pMatrix[ai-1][aj-1]&&pMatrix[ai][aj]>=pMatrix[ai-1][aj]&&pMatrix[ai][aj]>=pMatrix[ai-1][aj+1]&&pMatrix[ai][aj]>=pMatrix[ai-1][aj+2]
// 							   &&pMatrix[ai][aj]>=pMatrix[ai][aj-2]&&pMatrix[ai][aj]>=pMatrix[ai][aj-1]&&pMatrix[ai][aj]>=pMatrix[ai][aj+1]&&pMatrix[ai][aj]>=pMatrix[ai][aj+2]
// 							   &&pMatrix[ai][aj]>=pMatrix[ai+1][aj-2]&&pMatrix[ai][aj]>=pMatrix[ai+1][aj-1]&&pMatrix[ai][aj]>=pMatrix[ai+1][aj]&&pMatrix[ai][aj]>=pMatrix[ai+1][aj+1]&&pMatrix[ai][aj]>=pMatrix[ai+1][aj+2]
// 							   &&pMatrix[ai][aj]>=pMatrix[ai+2][aj-2]&&pMatrix[ai][aj]>=pMatrix[ai+2][aj-1]&&pMatrix[ai][aj]>=pMatrix[ai+2][aj]&&pMatrix[ai][aj]>=pMatrix[ai+2][aj+1]&&pMatrix[ai][aj]>=pMatrix[ai+2][aj+2]
// 							 )
// 						   {
//                                toppre.count=pMatrix[ai][aj];
// 							   toppre.x=aj;
// 							   toppre.y=ai;
// 							   result_of_top.push_back(toppre);
// 							   pMatrix[ai][aj]++;
// 						   }
// 					  }
// 				 }
// 			 }
			 
             for(ai   =   0;   ai   <   row;   ai++) 
			 { 
				 delete pMatrix[ai];
			 } 
			 delete pMatrix;             

			 int top_length=result_of_top.size();
			 int topscale=1;
			 if(layer==1)
			 {
                 topscale=1;
			 }
			 else
			 {
				 for(int n=0;n<layer-1;n++)
				 {
					 topscale=topscale*2;
				 }
			 }
             
             //jump to bottom level 
             if(top_length==1)
			 {
                 PreResult peak_of_top;
				 peak_of_top.count=max;
				 peak_of_top.x=int((result_of_top.at(0).x)*topscale+0.5);
			     peak_of_top.y=int((result_of_top.at(0).y)*topscale+0.5);
                 PreResult bottomresult;
				 vector<tedgepoint> *simageepoints=new vector<tedgepoint>;
				 GHTSuImgEdgeExtract(m_image,featmodel->m_mask,peak_of_top,sobelthresh,simageepoints,TILE_LENGTH,1);
				 GHTLayerMatch(m_image->height,m_image->width, &(featmodel->rtable), simageepoints, bottomresult,TRUE);
				 delete simageepoints;				 
				 featresult->featresultpoint->rx=bottomresult.x+(double)(featmodel->m_model->width-1)/2-featmodel->mx;
				 featresult->featresultpoint->ry=bottomresult.y+(double)(featmodel->m_model->height-1)/2-featmodel->my; 
				 featresult->featresultpoint->delta=0;

				 //test momo 
// 				 CreateWindows("momo");
// 				 MvShowImage("momo",featmodel->m_mask);
			 }
			 
			 //down night
             else if(top_length>1)
			 {
                 PreResult **result_of_lv;
		 	     result_of_lv=new PreResult*[layer-1]; 
                 int layermax;
				 int * lvlength= new int[layer-1];
				 
				 lvlength[layer-2]=top_length;  
				 result_of_lv[layer-2]=new PreResult[lvlength[layer-2]]; 
				 for(int i=0;i<result_of_top.size();i++)
				 {   
					 result_of_lv[layer-2][i].count=result_of_top.at(i).count;
					 result_of_lv[layer-2][i].x=result_of_top.at(i).x;
                     result_of_lv[layer-2][i].y=result_of_top.at(i).y;
				 }
				 PreResult temp;

                 for(int m=layer-2;m>=0;m--)
				 {
                     if(m==0)                        //lowest layer of pyramid if all above layers failed
					 {
						 PreResult *result_of_bottom=new PreResult[lvlength[0]];
						 for(int n=0;n<lvlength[0];n++)
						 {
							 result_of_lv[0][n].x=result_of_lv[0][n].x*2;
							 result_of_lv[0][n].y=result_of_lv[0][n].y*2;
							 
							 vector<tedgepoint> *sbottomimageepoints=new vector<tedgepoint>;
							 GHTSuImgEdgeExtract(m_image, featmodel->m_mask,result_of_lv[0][n],sobelthresh,sbottomimageepoints,TILE_LENGTH,1);
							 GHTLayerMatch(m_image->height,m_image->width, &(featmodel->rtable), sbottomimageepoints, result_of_bottom[n],TRUE);
							 delete sbottomimageepoints;				 
						 }
                         for(int i=0;i<lvlength[0]-1;i++)
						 {
							 for(int j=i+1;j<lvlength[0];j++)
							 {
								 if(result_of_bottom[i].count<result_of_bottom[j].count)
								 {
									 temp.count=result_of_bottom[i].count;
									 temp.x=result_of_bottom[i].x;
									 temp.y=result_of_bottom[i].y;
									 result_of_bottom[i].count=result_of_bottom[j].count;
									 result_of_bottom[i].x=result_of_bottom[j].x;
									 result_of_bottom[i].y=result_of_bottom[j].y;
									 result_of_bottom[j].count=temp.count;
									 result_of_bottom[j].x=temp.x;
									 result_of_bottom[j].y=temp.y;
								 }
							 }
						 }
                         featresult->featresultpoint->rx=result_of_bottom[0].x+(double)(featmodel->m_model->width-1)/2-featmodel->mx;
						 featresult->featresultpoint->ry=result_of_bottom[0].y+(double)(featmodel->m_model->height-1)/2-featmodel->my;
						 featresult->featresultpoint->delta=0;
						 delete []result_of_bottom; 
					 }
					 else 
					 {
						 result_of_lv[m-1]=new PreResult[lvlength[m]];
                         for(int n=0;n<lvlength[m];n++)
						 {
							 result_of_lv[m][n].x=result_of_lv[m][n].x*2;
							 result_of_lv[m][n].y=result_of_lv[m][n].y*2;							 
							 vector<tedgepoint> *sbottomimageepoints=new vector<tedgepoint>;
							 GHTSuImgEdgeExtract(m_image_lv[m-1], featmodel->m_blmodel_lv[m-1],result_of_lv[m][n],sobelthresh,sbottomimageepoints,TILE_LENGTH/m,1);
							 GHTLayerMatch(m_image_lv[m-1]->height,m_image_lv[m-1]->width, &(featmodel->rtable_lv[m-1]), sbottomimageepoints, result_of_lv[m-1][n],TRUE);
							 delete sbottomimageepoints;				 
						 }
                         for(int i=0;i<lvlength[m]-1;i++)
						 {
						  		for(int j=i+1;j<lvlength[m];j++)
						  		{
						  			if(result_of_lv[m-1][i].count<result_of_lv[m-1][j].count)
						  			{
						 				temp.count=result_of_lv[m-1][i].count;
						  				temp.x=result_of_lv[m-1][i].x;
						  				temp.y=result_of_lv[m-1][i].y;
						  				result_of_lv[m-1][i].count=result_of_lv[m-1][j].count;
						  				result_of_lv[m-1][i].x=result_of_lv[m-1][j].x;
						  				result_of_lv[m-1][i].y=result_of_lv[m-1][j].y;
						  				result_of_lv[m-1][j].count=temp.count;
						  				result_of_lv[m-1][j].x=temp.x;
						  				result_of_lv[m-1][j].y=temp.y;
						  			}
						  		}
						  }
                          layermax=result_of_lv[m-1][0].count;
						  lvlength[m-1]=1;
				          for(n=1;n<lvlength[m];n++)
						  {
						  		if(result_of_lv[m-1][n].count>=GHT_LV_FACTOR*layermax)
						   		{
						   			lvlength[m-1]++;
								}
						  }
						  if(lvlength[m-1]==1)
						  {
							   		PreResult peak_of_lv;
									int lvscale=1;
									for(int n=0;n<m;n++)
									{
										lvscale=lvscale*2;
									}
							   		peak_of_lv.x=result_of_lv[m-1][0].x*lvscale;
							  		peak_of_lv.y=result_of_lv[m-1][0].y*lvscale;
							   		peak_of_lv.count=result_of_lv[m-1][0].count;
							   		
							   		PreResult bottomresult;
							   		vector<tedgepoint> *lsimageepoints=new vector<tedgepoint>;
							   		GHTSuImgEdgeExtract(m_image, featmodel->m_mask,peak_of_lv,sobelthresh,lsimageepoints,TILE_LENGTH,1);
							   		GHTLayerMatch(m_image->height,m_image->width, &(featmodel->rtable), lsimageepoints, bottomresult,TRUE);
							   		delete lsimageepoints;				 
							   		featresult->featresultpoint->rx=bottomresult.x+(double)(featmodel->m_model->width-1)/2-featmodel->mx;
 		                            featresult->featresultpoint->ry=bottomresult.y+(double)(featmodel->m_model->height-1)/2-featmodel->my;
									featresult->featresultpoint->delta=0;
									delete result_of_lv[m-1];
							        break;
						  }
					 }
			         delete result_of_lv[m];
				 }

                 delete []lvlength; 
				 delete result_of_lv;
			 }
			 for(int d=0;d<layer-1;d++)
			 {
				 ReleaseImage(m_image_lv[d]);
			 }
			 delete m_image_lv;
			 ReleaseImage(pimage);
    }

// 	double ccorr;
// 	if(Normalize(m_image,featmodel->m_model,(int)featresult->featresultpoint->rx-(featmodel->m_model->width-1)/2,(int)featresult->featresultpoint->ry-(featmodel->m_model->height-1)/2,0,0,1,&ccorr)==false)
// 	{
// 		
// 		return false;
// 	}
// 	featresult->featresultpoint->score=ccorr;
	if(featparam->TargetROI)
	{
         featresult->featresultpoint->rx+=featparam->TargetReferenceX;
		 featresult->featresultpoint->ry+=featparam->TargetReferenceY;

		 ///////////////////////
		 if(featresult->featresultpoint->rx<featparam->TargetReferenceX||
			 featresult->featresultpoint->ry<featparam->TargetReferenceY||
			 featresult->featresultpoint->rx>featparam->TargetReferenceX+featparam->TargetROIX||
			 featresult->featresultpoint->ry>featparam->TargetReferenceY+featparam->TargetROIY)
		 {
			 featresult->featresultpoint->rx=featparam->TargetReferenceX+featparam->TargetROIX/2;
			 featresult->featresultpoint->ry=featparam->TargetReferenceY+featparam->TargetROIY/2;
		 }
		 ///////////////////////
	}
// 	if (featresult->featresultpoint->score<featparam->acceptance) 
// 	{
// 		return false;
// 	}
	
    return TRUE;
}


/***************************************************************/
//function name£ºGHTMODIFIER3
//input: GHT voting matrix, prior value coordinate x£¬y
//output: matching value of sub pixel 
//function: change the parameter of sub pixel 
//Created on 2013.10.25 by Yang Song
/***************************************************************/
bool SUBPIXMODIFIER3(int **pMatrix,int ai,int aj,int votex,int votey,double *x,double *y)
{
    if(votex>1&&votey>1&&votex<aj-1&&votey<ai-1)
	{
       	MvMat* factor_k6=CreateMat(6,1,MV_64F);
		MvPoint2D64f *src=new MvPoint2D64f[9];
		MvPoint2D64f *dst=new MvPoint2D64f[9];
		double* k=new double[6];
		
		dst[0].x=votex-1; 
		dst[1].x=votex;
		dst[2].x=votex+1;
		dst[3].x=votex-1; 
		dst[4].x=votex;
		dst[5].x=votex+1;
		dst[6].x=votex-1; 
		dst[7].x=votex;
		dst[8].x=votex+1;
		
		dst[0].y=votey-1; 
		dst[1].y=votey-1;
		dst[2].y=votey-1;
		dst[3].y=votey; 
		dst[4].y=votey;
		dst[5].y=votey;
		dst[6].y=votey+1; 
		dst[7].y=votey+1;
		dst[8].y=votey+1;
		
		src[0].x=pMatrix[votey-1][votex-1]; 
		src[1].x=pMatrix[votey-1][votex];
		src[2].x=pMatrix[votey-1][votex+1];
		src[3].x=pMatrix[votey][votex-1]; 
		src[4].x=pMatrix[votey][votex];
		src[5].x=pMatrix[votey][votex+1];
		src[6].x=pMatrix[votey+1][votex-1]; 
		src[7].x=pMatrix[votey+1][votex];
		src[8].x=pMatrix[votey+1][votex+1];
		
		src[0].y=pMatrix[votey-1][votex-1]; 
		src[1].y=pMatrix[votey-1][votex];
		src[2].y=pMatrix[votey-1][votex+1];
		src[3].y=pMatrix[votey][votex-1]; 
		src[4].y=pMatrix[votey][votex];
		src[5].y=pMatrix[votey][votex+1];
		src[6].y=pMatrix[votey+1][votex-1]; 
		src[7].y=pMatrix[votey+1][votex];
		src[8].y=pMatrix[votey+1][votex+1];
		
		LeastSquaresFitting_1_2(factor_k6,factor_k6,src,dst,9);
		
		for(int i=0;i<6;i++)
		{
			k[i]=*(factor_k6->data.db+i);        //identifying k1-k6;
		}
		
		//maximum;
		*y=(2*k[1]*k[5]-k[3]*k[4])/(k[4]*k[4]-4*k[2]*k[5]);
	    *x=(k[3]+k[4]*(*y))/(2*k[5])*(-1);
		ReleaseMat(factor_k6);                      
		delete []src;
		delete []dst;
	    delete []k;
	}

	else
	{
		*x=votex;
		*y=votey;
	}

	//	current_result.count=max; 
	
	return TRUE;
}

/***************************************************************/
//function names£ºSSGHTFindModel
//input: object image, matching module pointers in single angle, external parameter structure pointers, result storage pointers
//output: matching result (success/failure)
//Function£ºGHT application in matching single image in non-rotation environment
//Created on 2011.10.19 by Xiang Chen
/***************************************************************/
bool SSGHTFindModel(MvImage* m_image,GHTModel* featmodel,MvFeatParam* featparam,MvFeatResult* featresult)
{
	//preprocess image
	int sobelthresh=featparam->grayfactor;
   	int w=m_image->width;
	int h=m_image->height;
	Edgepoint imagepoints;

    MvImage* pimage;
	pimage= CreateImage(w,h,8,1);
	mvZero(pimage);
    GHTSobelEdge(m_image,pimage,0,&(imagepoints),sobelthresh);
	
	//ght match
	//opening up result space	
		int   row=m_image->height; 
		int   column=m_image->width;
		int   ai=0;
		int   aj=0;
		int   **   pMatrix; 
		pMatrix   =   new   int   *   [row]; 
		for(ai   =   0;   ai   <   row;   ai++) 
		{ 
			pMatrix   [ai]   =   new   int   [column]; 
		} 
		
		//over 
		for(ai   =0;   ai <   row;   ai++) 
		{ 
			for(aj   =   0;   aj   <   column;   aj++) 
			{ 
				pMatrix[ai][aj]   =   0; 
			} 
		} 
		//stepII2 vote
		int votex=0;
		int votey=0;
		
		for(int slen=0;slen<imagepoints.size();slen++)
		{
			for(int cr=0;cr<featmodel->rtable.size();cr++)
			{
				if(   (imagepoints.at(slen).gradient<=featmodel->rtable.at(cr).at(0).gradient+0.0087*2)              //in gradient space
					&& (imagepoints.at(slen).gradient>=featmodel->rtable.at(cr).at(0).gradient-0.0087*2)   )       
				{
					for(int csrt=0;csrt<featmodel->rtable.at(cr).size();csrt++)
					{
						votex=imagepoints.at(slen).x+featmodel->rtable.at(cr).at(csrt).vx;                         //relocate central 
						votey=imagepoints.at(slen).y+featmodel->rtable.at(cr).at(csrt).vy;
						
						if( (votex>=0&&votex<column) && (votey>=0&&votey<row) )
						{
							pMatrix[votey][votex]++;
						}
						
					}
				}
			}
		}		
		//stepIII find maximum value
		int max=0;
		votex=0;
		votey=0;
		for(ai   =0;   ai <   row;   ai++) 
		{ 
			for(aj   =   0;   aj   <   column;   aj++) 
			{ 
				if(max<=pMatrix[ai][aj])
				{
					max=pMatrix[ai][aj];
					votex=aj;
					votey=ai;
				} 
			} 
		} 
		double votexx=0;
		double voteyy=0;
        SUBPIXMODIFIER3(pMatrix,row,column,votex,votey,&votexx,&voteyy);

		featresult->featresultpoint->rx=votexx+(double)(featmodel->m_model->width-1)/2-featmodel->mx;  
		featresult->featresultpoint->ry=voteyy+(double)(featmodel->m_model->height-1)/2-featmodel->my;
		featresult->featresultpoint->delta=0;
		
		for(ai   =   0;   ai   <   row;   ai++) 
		{ 
			delete pMatrix[ai];
		} 
		delete pMatrix;
		ReleaseImage(pimage);

		if(featparam->TargetROI)
		{
			featresult->featresultpoint->rx+=featparam->TargetReferenceX;
			featresult->featresultpoint->ry+=featparam->TargetReferenceY;
			if(featresult->featresultpoint->rx<featparam->TargetReferenceX||
			   featresult->featresultpoint->ry<featparam->TargetReferenceY||
			   featresult->featresultpoint->rx>featparam->TargetReferenceX+featparam->TargetROIX||
			   featresult->featresultpoint->ry>featparam->TargetReferenceY+featparam->TargetROIY)
			{
               featresult->featresultpoint->rx=featparam->TargetReferenceX+featparam->TargetROIX/2;
			   featresult->featresultpoint->ry=featparam->TargetReferenceY+featparam->TargetROIY/2;
			}
		}

		
		return TRUE;
}

