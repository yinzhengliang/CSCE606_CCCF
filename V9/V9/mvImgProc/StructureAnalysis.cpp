/************************************************************************/
/* Structural analysis related operations                                                                    */
/************************************************************************/
#include "stdafx.h"
#include "StructureAnalysis.h"

//normalize image gray scale value
bool Normalize(MvImage* dstImage,MvImage* tmpImage,int offX,int offY,int width,int height,int filter,double* ccorr)
{
	int dstWidth=dstImage->width;
	int dstHeight=dstImage->height;
	int dstStep=dstImage->widthStep;
	int tmpWidth=tmpImage->width;
	int tmpHeight=tmpImage->height;
	int tmpStep=tmpImage->widthStep;
	if ((offX+width+tmpWidth)>dstWidth||(offY+height+tmpHeight)>dstHeight||(offX+tmpWidth)<0||(offY+tmpHeight)<0)  
	{
		return false;
	}
	int i=0,j=0,s=0,k=0;
	double SI=0,SM=0,SIM=0,SII=0,SMM=0;
	int oYjdstStep=0;
	int jtmpStep=0;
	int num=0;
	height++;
	width++;
	int size=height*width;
	int sizeCount=0;
	for (k=0;k<height;k++) 
	{
		for (s=0;s<width;s++) 
		{
			num=0;
			SI=0;
			SII=0;
			SIM=0;
			SM=0;
			SMM=0;
			for (j=0;j<tmpHeight;j+=filter) 
			{
				oYjdstStep=(offY+j)*dstStep;
				jtmpStep=j*tmpStep;
				for (i=0;i<tmpWidth;i+=filter) 
				{
					SI+=(double)dstImage->imageData[oYjdstStep+(offX+i)]/255;
					SII+=(double)dstImage->imageData[oYjdstStep+(offX+i)]*dstImage->imageData[oYjdstStep+(offX+i)]/65025;
					SM+=(double)tmpImage->imageData[jtmpStep+i]/255;
					SMM+=(double)tmpImage->imageData[jtmpStep+i]*tmpImage->imageData[jtmpStep+i]/65025;
					SIM+=(double)dstImage->imageData[oYjdstStep+(offX+i)]*tmpImage->imageData[jtmpStep+i]/65025;
					num++;
				}
			}
			ccorr[sizeCount]=(num*SIM-SI*SM)/(sqrt(fabs((num*SII-SI*SI)*(num*SMM-SM*SM))));
			sizeCount++;
		}
	}
	return true;
}