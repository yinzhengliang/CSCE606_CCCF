/************************************************************************/
/* implementation of feature matching interface                                               */
/************************************************************************/
#include "StdAfx.h"
#include "../demo/mv.h"
#include "FeatMatch.h"
#include "MvFeatMatch.h"
#include "../mvGUI/imageFile.h"
#pragma comment(lib,"../mvGUI/Debug/mvGUI.lib")

/***************************************************************/
//function name£ºAllocFeatParam
//input: feature matching method
//output: external parameters structure pointers
//function: allocate matching parameters, set the default value of them
//Created on 2013.10.11 by Xiang Chen
/***************************************************************/
MvFeatParam * FeatAllocParam(int method)
{
	 MvFeatParam *Featparam=new MvFeatParam;
	  //select method more case element left for future use
     switch(method)                               
	 {
	    case MV_FEATMATCH_EDGE:
		{
			Featparam->method=MV_FEATMATCH_EDGE;
            break;
		}		    
        case MV_DEFAULT:
		{
			Featparam->method=MV_DEFAULT;
            break;
		}
		default: 
		{
            return NULL;
		}
	 }
        //set default parameters
	 Featparam->molNumMode=FALSE;
     Featparam->rindex=0;

     Featparam->anglemode=FALSE;
	 Featparam->startAngle=0;
	 Featparam->negAngle=0;
	 Featparam->posAngle=0;
	 Featparam->angleAccuracy=1;

	 Featparam->acceptance=0.6;
	 Featparam->accuracy=1;
	 Featparam->certainty=0.99;

 	 Featparam->ModelROI=FALSE;
	 Featparam->ModelPointX=0;
	 Featparam->ModelPointY=0;

	 Featparam->TargetROI=FALSE;
	 Featparam->TargetReferenceX=0;
	 Featparam->TargetReferenceY=0;  


	 Featparam->grayfactor=100;
	 Featparam->topsize=16;

	 return Featparam;
}


/***************************************************************/
//function name£ºSetFeatParam
//input: set parameter type, value
//output: NULL
//function:  change the value of parameters based on different requirement
//Created on 2013.10.17 by Xiang Chen
/***************************************************************/
void SetFeatParam(int MvFeatType, double value, MvFeatParam* featparam)
{
	switch(MvFeatType)                           
	{
	    case MV_GRAYFACTOR:
		{
            featparam->grayfactor=(int)value;
			break;
		}
 	    case MV_TOPLEVEL_LENGTH:
		{
			featparam->topsize=(int)value;
			break;
		}
		case MV_MODEL_X:
		{
				if(value==MV_DEFAULT)
				{
                    featparam->ModelROI=FALSE;
				}
				else
				{
					featparam->ModelROI=TRUE;
                   	featparam->ModelPointX=(int)value;
				}
				break;
		}
		case MV_MODEL_Y:
		{
				if(value==MV_DEFAULT)
				{
                    featparam->ModelROI=FALSE;
				}
				else
				{
					featparam->ModelROI=TRUE;
                   	featparam->ModelPointY=(int)value;
				}
				break;
		}
		case MV_MODELROI_X:
		{
				if(value==MV_DEFAULT)
				{
                    featparam->ModelROI=FALSE;
				}
				else
				{
					featparam->ModelROI=TRUE;
                   	featparam->ModelROIX=(int)value;
				}
				break;
		}
		case MV_MODELROI_Y:
		{
				if(value==MV_DEFAULT)
				{
                    featparam->ModelROI=FALSE;
				}
				else
				{
					featparam->ModelROI=TRUE;
                   	featparam->ModelROIY=(int)value;
				}
				break;
		}
		case MV_TARGET_X:
		{
				if(value==MV_DEFAULT)
				{
                    featparam->TargetROI=FALSE;
				}
				else
				{
					featparam->TargetROI=TRUE;
                   	featparam->TargetReferenceX=(int)value;
				}
				break;
		}
		case MV_TARGET_Y:
		{
				if(value==MV_DEFAULT)
				{
					featparam->TargetROI=FALSE;
				}
				else
				{
					featparam->TargetROI=TRUE;
                   	featparam->TargetReferenceY=(int)value;
				}
				break;	
		}
		case MV_TARGETROI_X:
		{
				if(value==MV_DEFAULT)
				{
                    featparam->TargetROI=FALSE;
				}
				else
				{
					featparam->TargetROI=TRUE;
                   	featparam->TargetROIX=(int)value;
				}
				break;
		}
		case MV_TARGETROI_Y:
		{
				if(value==MV_DEFAULT)
				{
					featparam->TargetROI=FALSE;
				}
				else
				{
					featparam->TargetROI=TRUE;
                   	featparam->TargetROIY=(int)value;
				}
				break;		
		}
		case MV_ACCEPTANCE:
		{
			if (value==MV_DEFAULT) 
			{
				featparam->acceptance=0.6;
			}	
			else
			{
				featparam->acceptance=value;
			}
		}
	    default: 
		{
			//error;
		}
	 }
}

/***************************************************************/
//function name: MvFeatAllocModel
//input: module image, external parameter structure pointers
//output: module structure pointers
//function: allocate module space based on different methods
//Created on 2013.10.23 by Yang Song
/***************************************************************/
MV_FEATMODEL FeatAllocModel(MvImage* model, MvFeatParam* featparam)
{
     //ROI
     MvImage* modelroi;
	 if(!featparam->ModelROI)
	 {
		 featparam->ModelPointX=0;
		 featparam->ModelPointY=0;
		 featparam->ModelROIX=model->width;
		 featparam->ModelROIY=model->height;
		 modelroi=CloneImage(model);
	 }
	 else
	 {
		 int x=featparam->ModelPointX;
		 int y=featparam->ModelPointY;
		 int dx=featparam->ModelROIX;
		 int dy=featparam->ModelROIY;
		 
		 if(x<0||y<0||(x+dx)>model->width||(y+dy)>model->height)
		 {
			 return NULL;
		 }
		 modelroi=CreateImage(dx,dy,8,1);

 		 uchar * data = (uchar *)model->imageData;
 	     uchar * roidata=(uchar *)modelroi->imageData;
		 
		 for(int i=0;i<dy;i++)
		 {
             for(int j=0;j<dx;j++)
			 {
				 roidata[i*(modelroi->widthStep)+j]=data[(y+i)*model->widthStep+(x+j)];
			 }
		 }
	 }
	 
// 	 CreateWindows("testroi");
// 	 MvShowImage("testroi",modelroi);
	 //choose module based on different methods
	 int featmodelmethod=featparam->method;
	 switch(featmodelmethod)                           
	 {
	    case MV_FEATMATCH_EDGE:
		{
            GHTModel *ghtmodel=new GHTModel; 
			ghtmodel->m_model=CloneImage(modelroi);
			return (MV_FEATMODEL)ghtmodel;
			break;
		}
		//::for alternatives
        case MV_DEFAULT:
		{
            GHTModel *ghtmodel=new GHTModel;
		    ghtmodel->m_model=CloneImage(modelroi);
			return (MV_FEATMODEL)ghtmodel;
			break;
		}
		default: 
		{
			//error;
			return NULL;
		}

		ReleaseImage(modelroi);
	 }
}
/***************************************************************/
//function name: mvFeatPreprocess
//input: module structure pointers, external parameter pointers
//output: NULL
//function: pre-treat module based on different methods
//Created on 2013.10.23 by Yang Song
/***************************************************************/
void FeatPreprocess(MV_FEATMODEL featmodel,MvFeatParam* featparam)
{
	int featmodelmethod=featparam->method;
	switch(featmodelmethod)                           
	{
	    case MV_FEATMATCH_EDGE:
		{
			if(!featparam->anglemode)
			{
               SGHTPreProcessModel((GHTModel*)featmodel,featparam);
			}   
			break;
		}
		//::for alternatives
	    case MV_DEFAULT:
		{
			if(!featparam->anglemode)
			{
			   SGHTPreProcessModel((GHTModel*)featmodel,featparam);
			}
			break;
		}
	    default: 
		{
			//error;
		}
	 }
}

/***************************************************************/
//function name: FeatAllocResult
//input: external parameter structure pointers
//output: matching result pointers
//function: allocate result structure based on different modules
//Created on 2013.10.17 by Xiang Chen
/***************************************************************/
MvFeatResult* FeatAllocResult(MvFeatParam* featparam)
{
	MvFeatResult* featresult=new MvFeatResult;
	if(!featparam->molNumMode)
	{
		featresult->num=1;
		featresult->featresultpoint=new MvFeatResultPoint; 
	}
	else
	{
		featresult->num=0;
/*		featresult->featresultpoint=new MvFeatResultPoint[featparam->];*/
	}
	return featresult;
}

/***************************************************************/
//function name: FeatFind
//input: object image, module structure pointers, external parameter structure pointers, result structure pointers
//output: NULL
//function: do image match based on different methods
//Created on 2013.10.19 by Xiang Chen
/***************************************************************/
bool FeatFind(MvImage* dstimage,MV_FEATMODEL featmodel,MvFeatParam* featparam,MvFeatResult* featresult)
{
	//ROI
	MvImage* targetroi;
	if(!featparam->TargetROI)
	{
		featparam->TargetReferenceX=0;
		featparam->TargetReferenceY=0;
		featparam->TargetROIX=dstimage->width;
		featparam->TargetROIY=dstimage->height;
		targetroi=CloneImage(dstimage);
	}
	else
	{
		int x=featparam->TargetReferenceX;
		int y=featparam->TargetReferenceY;
		int dx=featparam->TargetROIX;
		int dy=featparam->TargetROIY;
		
		if(x<0||y<0||(x+dx)>dstimage->width||(y+dy)>dstimage->height)
		{
			return NULL;
		}
		targetroi=CreateImage(dx,dy,8,1);
		
		uchar * data = (uchar *)dstimage->imageData;
		uchar * roidata=(uchar *)targetroi->imageData;
		
		for(int i=0;i<dy;i++)
		{
			for(int j=0;j<dx;j++)
			{
				roidata[i*(targetroi->widthStep)+j]=data[(y+i)*dstimage->widthStep+(x+j)];
			}
		}
	 }

	//choose module based on different methods
	int featmodelmethod=featparam->method;
	switch(featmodelmethod)                           
	{
	    case MV_FEATMATCH_EDGE:
		{
            if(!featparam->molNumMode)
			{
				if(!featparam->anglemode)
				{
                   if(!SGHTFindModel(targetroi,(GHTModel*)featmodel,featparam,featresult))
				   {

					   ReleaseImage(targetroi);
						return false;
				   }
				   else//zsh
				   {
					   double ccorr=0;
					   if(Normalize(dstimage,((GHTModel*)featmodel)->m_model,(int)featresult->featresultpoint->rx-(((GHTModel*)featmodel)->m_model->width-1)/2,(int)featresult->featresultpoint->ry-(((GHTModel*)featmodel)->m_model->height-1)/2,0,0,1,&ccorr)==false)
					   {
						   ReleaseImage(targetroi);
						   return false;
					   }
					   featresult->featresultpoint->score=ccorr;
					   if (featresult->featresultpoint->score<featparam->acceptance) 
					   {
						   ReleaseImage(targetroi);
						   return false;
					   }
				   }
				}
				else
				{

				}
			}
			else
			{
				if(!featparam->anglemode)
				{
					//GHT multi-images matching
				}
				else
				{

				}
			}
			break;
		}

		//::for alternatives

	    case MV_DEFAULT:
		{
			if(!featparam->molNumMode)
			{
				if(!featparam->anglemode)
				{
					if(!SSGHTFindModel(targetroi,(GHTModel*)featmodel,featparam,featresult))
					{
						
						ReleaseImage(targetroi);
						return false;
					}
					else//zsh
					{
						double ccorr=0;
						if(Normalize(dstimage,((GHTModel*)featmodel)->m_model,(int)featresult->featresultpoint->rx-(((GHTModel*)featmodel)->m_model->width-1)/2,(int)featresult->featresultpoint->ry-(((GHTModel*)featmodel)->m_model->height-1)/2,0,0,1,&ccorr)==false)
						{
							ReleaseImage(targetroi);
							return false;
						}
						featresult->featresultpoint->score=ccorr;
						if (featresult->featresultpoint->score<featparam->acceptance) 
						{
							ReleaseImage(targetroi);
							return false;
						}
				   }
				}
				else
				{
					
				}
			}
			else
			{
				if(!featparam->anglemode)
				{
					//GHT multi-images matching
				}
				else
				{
					
				}
			}
			break;
		}
	    default: 
		{
			//error;
		}
	}
    
	ReleaseImage(targetroi);
	return TRUE;
}

/***************************************************************/
//function name: FeatGetResult
//input:  result structure, type of result, single type of result array
//output:  NULL
//function:  get all the result of single type matching 
//Created on 2013.10.13 by Yang Song
/***************************************************************/
void FeatGetResult(MvFeatResult* FeatResultId,int ResultType,double *UserArrayPtr)
{
	int i=0;
	switch (ResultType)
	{		
	    case MV_RESULT_ANGLE:
		for (;i<FeatResultId->num;i++)
		{
			UserArrayPtr[i]=FeatResultId->featresultpoint[i].delta;
		}
		break;

	    case MV_RESULT_X:
		for (;i<FeatResultId->num;i++)
		{
			UserArrayPtr[i]=FeatResultId->featresultpoint[i].rx;
		}
		break;

 	    case MV_RESULT_Y:
		for (;i<FeatResultId->num;i++)
		{
			UserArrayPtr[i]=FeatResultId->featresultpoint[i].ry;
		}
		break;

	    case MV_RESULT_SCORE:
		for (;i<FeatResultId->num;i++)
		{
			UserArrayPtr[i]=FeatResultId->featresultpoint[i].score;
		}
		break;

		default:
		{
            //error
		}
	}
}

/***************************************************************/
//function name£ºFeatParamFree
//input:  parameter structure pointers
//output:  NULL
//function:  release parameter space memory
//Created on 2013.10.19 by Xiang Chen
/***************************************************************/
void FeatParamFree(MvFeatParam* featparam)
{
     delete featparam;
}

/***************************************************************/
//function name: FeatModelFree
//input:  module pointers
//output:  NULL
//function:  release the memory of module 
//Created on 2013.10.21 by Xiang Chen
/***************************************************************/
void FeatModelFree(MV_FEATMODEL featmodel,MvFeatParam *featparam)
{    
	 int method=featparam->method;
	 switch(method)
	 { 
 	    case MV_FEATMATCH_EDGE:
		{
			for(int d=0;d<((GHTModel *)featmodel)->modellayer-1;d++)
			{
				ReleaseImage(((GHTModel *)featmodel)->m_blmodel_lv[d]);
			}
			delete ((GHTModel *)featmodel)->m_blmodel_lv;
			delete []((GHTModel *)featmodel)->rtable_lv;
			ReleaseImage(((GHTModel *)featmodel)->m_model);	
			ReleaseImage(((GHTModel *)featmodel)->m_blmodel);
			ReleaseImage(((GHTModel *)featmodel)->m_mask);
		}
		break;
		case MV_DEFAULT:
		{
// 			for(int d=0;d<((GHTModel *)featmodel)->modellayer-1;d++)
// 			{
// 				ReleaseImage(((GHTModel *)featmodel)->m_blmodel_lv[d]);
// 			}
		//	delete ((GHTModel *)featmodel)->m_blmodel_lv;
		//	delete []((GHTModel *)featmodel)->rtable_lv;
			ReleaseImage(((GHTModel *)featmodel)->m_model);	
		}
		break;
	 }
     delete featmodel;   
}

/***************************************************************/
//function name£ºFeatResultFree
//input:  result structure pointers
//output:  NULL
//function:  release the result applying memory
//Created on 2013.10.23 by Xiang Chen
/***************************************************************/
void FeatResultFree(MvFeatResult* featresult)
{
     int sum=featresult->num;

	 if(sum>1)
	 {
		 int i=0;
		 for(;i<sum;i++)
		 {
			 delete []featresult->featresultpoint;
		 }
	 }

	 else
	 {
           delete featresult->featresultpoint;
	 }
	 delete featresult;
}

/***************************************************************/
//function name: FeatModelSave
//input: object image, feature matching parameter  
//output: NULL
//function:  store the image module and information
/***************************************************************/
void FeatModelSave(const char* FileName,MvImage* mimage, MvFeatParam* featparam)
{
	FILE* fp;
	if ((fp=fopen(FileName,"wb"))==NULL)
	{
		printf("cannot open this file!");
	}
	FeatWriteModel(fp,mimage,featparam);
	fclose(fp);
}

/***************************************************************/
//function name: FeatWriteModel
//input: object image, feature matching parameter  
//output: NULL
//function:  store the image module and information
/***************************************************************/
void FeatWriteModel(FILE *FileHandle,MvImage* mimage, MvFeatParam* featparam)
{
	fwrite(mimage,sizeof(MvImage),1,FileHandle);
	fwrite(mimage->imageData,(mimage->height)*(mimage->widthStep),1,FileHandle);

	fwrite(featparam,sizeof(MvFeatParam),1,FileHandle);
    fwrite(&(featparam->method),sizeof(int),1,FileHandle);
    fwrite(&(featparam->ModelROI),sizeof(bool),1,FileHandle);
	fwrite(&(featparam->ModelPointX),sizeof(int),1,FileHandle);
	fwrite(&(featparam->ModelPointY),sizeof(int),1,FileHandle);
   	fwrite(&(featparam->ModelROIX),sizeof(int),1,FileHandle);
	fwrite(&(featparam->ModelROIY),sizeof(int),1,FileHandle);
	fwrite(&(featparam->grayfactor),sizeof(int),1,FileHandle);
	fwrite(&(featparam->topsize),sizeof(int),1,FileHandle);
}

/***************************************************************/
//function name: FeatModelLoad
//input: object image, feature matching parameter  
//output: NULL
//function:  store the image module and information
/***************************************************************/
void FeatModelLoad(const char* FileName,MvImage** mimage,MvFeatParam** featparam)
{
	const char *p;
	p=FileName;
	p+=strlen(FileName);
	while(--p!=FileName)if(*p=='.')break;
	p++;
	char fileext[20];
	for(int _i=0;_i<=strlen(p);_i++)
		if(p[_i]>='a'&&p[_i]<='z')fileext[_i]=p[_i]+'A'-'a';
		else fileext[_i]=p[_i];
		if (!strcmp(fileext,"FTMO"))
		{
			FILE* fp;
			if ((fp=fopen(FileName,"rb"))==NULL)
			{
				printf("cannot open this file!");
			}
			FeatReadModel(fp,mimage,featparam);
			fclose(fp);
		}
}

/***************************************************************/
//function name: FeatWriteModel
//input: object image, feature matching parameter  
//output: NULL
//function:  store the image module and information
/***************************************************************/
void FeatReadModel(FILE *FileHandle, MvImage** mimage, MvFeatParam** featparam)
{
	MvImage *aimage=new MvImage;
    fread(aimage,sizeof(MvImage),1,FileHandle);
	aimage->imageData=new uchar[(aimage->height)*(aimage->widthStep)];
	fread(aimage->imageData,(aimage->height)*(aimage->widthStep),1,FileHandle);
	*mimage=aimage;

	MvFeatParam *afeatparam=FeatAllocParam(MV_DEFAULT);
	fread(afeatparam,sizeof(MvFeatParam),1,FileHandle);
    fread(&(afeatparam->method),sizeof(int),1,FileHandle);
    fread(&(afeatparam->ModelROI),sizeof(bool),1,FileHandle);
	fread(&(afeatparam->ModelPointX),sizeof(int),1,FileHandle);
	fread(&(afeatparam->ModelPointY),sizeof(int),1,FileHandle);
   	fread(&(afeatparam->ModelROIX),sizeof(int),1,FileHandle);
	fread(&(afeatparam->ModelROIY),sizeof(int),1,FileHandle);
	fread(&(afeatparam->grayfactor),sizeof(int),1,FileHandle);
	fread(&(afeatparam->topsize),sizeof(int),1,FileHandle);
	*featparam=afeatparam;
}

/***************************************************************/
//function name: FeatDrawModel
//input: object image, feature matching parameter  
//output: NULL
//function:  store the image module and information
/***************************************************************/
void FeatDrawModel(MvImage* model, MvFeatParam* featparam,HDC hDCDst, RECT* pDstRect)
{
	MvImage* modelroi;
	if(!featparam->ModelROI)
	{
		featparam->ModelPointX=0;
		featparam->ModelPointY=0;
		featparam->ModelROIX=model->width;
		featparam->ModelROIY=model->height;
		modelroi=CloneImage(model);
	}
	else
	{
		int x=featparam->ModelPointX;
		int y=featparam->ModelPointY;
		int dx=featparam->ModelROIX;
		int dy=featparam->ModelROIY;
		
		if(x<0||y<0||(x+dx)>model->width||(y+dy)>model->height)
		{
			//error
		}
		modelroi=CreateImage(dx,dy,8,1);
		
		uchar * data = (uchar *)model->imageData;
		uchar * roidata=(uchar *)modelroi->imageData;
		
		for(int i=0;i<dy;i++)
		{
			for(int j=0;j<dx;j++)
			{
				roidata[i*(modelroi->widthStep)+j]=data[(y+i)*model->widthStep+(x+j)];
			}
		}
	 }
	DispSelectWindow(modelroi,hDCDst,pDstRect);
	ReleaseImage(modelroi);
}


