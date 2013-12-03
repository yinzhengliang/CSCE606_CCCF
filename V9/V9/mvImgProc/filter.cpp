/************************************************************************/
/* filter.cpp implementation of functions concerning filtering                                                                   */
/************************************************************************/
#include "filter.h"

/***************************************************************/
//function name£ºPyrDown
//input£ºsrcImage->pointer to the input image,dstImage->pointer to the output image
//output£º
//function£ºbuild the pyramid downward for the input image
//
/***************************************************************/
void PyrDown(MvImage* srcImage,MvImage*& dstImage)
{
	//median pyramid
	int dstImageWidth=srcImage->width/2;
	int dstImageHeight=srcImage->height/2;
	dstImage=CreateImage(dstImageWidth,dstImageHeight,srcImage->depth,srcImage->nChannels);
	int srcImageStep=srcImage->widthStep;
	int dstImageStep=dstImage->widthStep;
	uchar* dstImageValue=dstImage->imageData;
	uchar* srcImageValue=srcImage->imageData;
	for (int j=0;j<dstImageHeight;j++)
	{
		for (int i=0;i<dstImageWidth;i++)
		{
			dstImageValue[j*dstImageStep+i]\
				=(srcImageValue[j*2*srcImageStep+i*2]\
				+srcImageValue[j*2*srcImageStep+i*2+1]\
				+srcImageValue[(j*2+1)*srcImageStep+i*2]\
				+srcImageValue[(j*2+1)*srcImageStep+(i*2+1)])/4;
		}
	}
}


/***************************************************************/
//funciton name£ºbuildPyramid
//input£ºsrcImage->pointer to the input image,dstImage-> array of pointers to the output image£¬maxlevel-> how many layers of the pyramid
//output£º
//function£ºbuild the pyramid of maxlevel layers for the input image
//
/***************************************************************/
void BuildPyramid(MvImage* srcImage, MvImage** dstImage, int maxlevel)
{
	int i=0;
	if (maxlevel>0)
	{
		PyrDown(srcImage,dstImage[0]);
		for (i=1;i<maxlevel;i++)
		{
			PyrDown(dstImage[i-1],dstImage[i]);
		}
	}
	//	else  //errors happen
}

/***************************************************************/
//function name£ºSobelEdge
//input£ºmimg-> original image,threshhold->edge extraction threshold value,mode->edge extraction mode(Thick£ºMV_THICK£¬Thin: MV_THIN)
//output£ºedge image
//function£ºuse Sobel operator to extract the edge
//
/***************************************************************/
void SobelEdge(MvImage * img, int threshold,int mode)
{
	int gx=0,gy=0;
	double gradient=0;
    double pi=3.1415926;
    int w=img->width;
    int h=img->height;
	int ws=img->widthStep;

    MvImage * simg;
	simg=CreateImage(w,h,8,1);
	mvZero(simg);

	uchar * mimgdata = (uchar *)img->imageData;
	uchar * simgdata=(uchar *)simg->imageData;     
    
	int ttmin=0;
	int k=0;
		
	for(int i=1;i<h-1;i++)
	{
		for(int j=1;j<w-1;j++)
		{
			gx =
				-mimgdata[(i-1) * img->widthStep + j-1] 
				+mimgdata[(i-1) * img->widthStep + j+1] 
				-2*mimgdata[i * img->widthStep + j-1] 
				+2*mimgdata[i * img->widthStep + j+1] 
				-mimgdata[(i+1) * img->widthStep + j-1] 
				+mimgdata[(i+1) * img->widthStep + j+1];
			
			gy=
				-mimgdata[(i-1) * img->widthStep + j-1] 
				+mimgdata[(i+1) * img->widthStep + j-1] 
				-2*mimgdata[(i-1) * img->widthStep + j] 
				+2*mimgdata[(i+1) * img->widthStep + j] 
				-mimgdata[(i-1) * img->widthStep + j+1] 
				+mimgdata[(i+1) * img->widthStep + j+1];
			
			if(abs(gx)>=threshold||abs(gy)>=threshold)
			{
				if(mode==MV_THIN)
				{
					ttmin=(int)mimgdata[(i-1) * img->widthStep + j-1]+(int)mimgdata[(i-1) * img->widthStep + j]+(int)mimgdata[(i-1) * img->widthStep + j+1]
						+(int)mimgdata[i * img->widthStep + j-1]+(int)mimgdata[i * img->widthStep + j]+(int)mimgdata[i * img->widthStep + j+1]
						+(int)mimgdata[(i+1) * img->widthStep + j-1]+(int)mimgdata[(i+1) * img->widthStep + j]+(int)mimgdata[(i+1) * img->widthStep + j+1];
				    ttmin=ttmin/9;
				}
				
				if(mimgdata[i * img->widthStep + j]>=ttmin||mode==MV_THICK)
				{
					simgdata[i * img->widthStep + j]=255;
					
					if(gx>0&&gy>0)
					{
						gradient=atan(gy/gx);
					}
					else if(gx>0&&gy<0)
					{
						gradient=atan(gy/gx)+3*pi/2;
					}
					else if(gx<0&&gy>0)
					{
						gradient=atan(gy/gx)+pi/2;
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
				}
			    else
				{
				    simgdata[i * img->widthStep + j]=0;
				}
			}           
			else
			{
				simgdata[i * img->widthStep + j]=0;
			}
		}
	}
	
	for (i=0; i<h; i++)
	{
		simgdata[i*img->widthStep]=0;
		simgdata[i*img->widthStep+img->width-1]=0;
	}		
	for (int j=0; j<img->widthStep; j++)
	{	 
		simgdata[j]=0;
		simgdata[(img->height-1)*img->widthStep+j]=0;				
	}

   	for(i=0;i<h;i++)
	{
			for(j=0;j<w;j++)
			{
                k=i*ws+j;
				mimgdata[k]=simgdata[k];
			}
	}
	ReleaseImage(simg);
}

/************************************************************************/
/* Binary corrosion
input img
output img
legend£º3*3 structure elment£¬the background is white£¬the target is black
                                                                    */
/************************************************************************/
bool Erosion(MvImage * img)
{
	if(img==NULL) return false;
	if (img->width<3||img->height<3) return false;
	MvImage* org=CloneImage(img);//original image
	if (org==NULL) return false;
	uchar* pSrc=org->imageData;
	uchar* pDst=img->imageData;
	int wStep=org->widthStep;
	int w=org->width;
	int h=org->height;
	uchar pixel;
	uchar* p=NULL;
	uchar* q=NULL;
	int i,j,m,n;
	for (i=0;i<w-2;i++)//process the first row
	{

		p=pSrc+i;
		if (*p != 255&&*p != 0) 
		{
			ReleaseImage(org);
			return false;

		}
		if(*p==255) continue;//don't process the background pixel					
		q=pDst+i;
	
		//If there is a pixel that is not black in the structure element of the original image,
		//assign the pixel to white in the target image.
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p + m*wStep + n);
				if (pixel == 255 )
				{	
					*q = (unsigned char)255;
					break;
				}
			}
		}
	}
	for (i=0;i<w-2;i++)//process the last row
	{
		p=pSrc+wStep*(h-1)+i;
		if (*p != 255&&*p != 0)
		{
			ReleaseImage(org);
			return false;
		}
		if(*p==255) continue;//don't process the background pixel						
		q=pDst+wStep*(h-1)+i;
		//If there is a pixel that is not black in the structure element of the original image,
		//assign the pixel to white in the target image.
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p - m*wStep + n);
				if (pixel == 255 )
				{	
					*q = (unsigned char)255;
					break;
				}
			}
		}
	}
	for (j=1;j<h-2;j++)//process the first row
	{
		p=pSrc+j*wStep;
		if (*p != 255&&*p != 0)
		{
			ReleaseImage(org);
			return false;
		}
		if(*p==255) continue;//don't process the background pixel					
		q=pDst+j*wStep;
		//If there is a pixel that is not black in the structure element of the original image,
		//assign the pixel to white in the target image.
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p + m*wStep + n);
				if (pixel == 255 )
				{	
					*q = (unsigned char)255;
					break;
				}
			}
		}
	}
	for (j=0;j<h-2;j++)//process the last row
	{
		p=pSrc+j*wStep+w-1;
		if (*p != 255&&*p != 0) 
		{
			ReleaseImage(org);
			return false;
		}
		if(*p==255) continue;//don't process the background pixel						
		q=pDst+j*wStep+w-1;
		//If there is a pixel that is not black in the structure element of the original image,
		//assign the pixel to white in the target image.
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p + m*wStep -n);
				if (pixel == 255 )
				{	
					*q = (unsigned char)255;
					break;
				}
			}
		}
	}
	p=pSrc+w-2;//the penultimate pixel of the first row
	if (*p != 255&&*p != 0)
	{
		ReleaseImage(org);
		return false;
	}
	if(*p==0) //not background pixel
	{
		q=pDst+w-2;
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p + m*wStep+n-1);
				if (pixel == 255 )
				{	
					*q = (unsigned char)255;
					break;
				}
			}
		}
	}
	p=pSrc+w-1+wStep*(h-2);//the penultimate pixel of the last row
	if (*p != 255&&*p != 0)
	{
		ReleaseImage(org);
		return false;
	}
	if(*p==0) //not background pixel
	{
		q=pDst+w-1+wStep*(h-2);
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p + (m-1)*wStep-n);
				if (pixel == 255 )
				{	
					*q = (unsigned char)255;
					break;
				}
			}
		}
	}
	p=pSrc+w-1+wStep*(h-1);//the pixel in the lower right corner
	if (*p != 255&&*p != 0)
	{
		ReleaseImage(org);
		return false;
	}
	if(*p==0) //not background pixel
	{
		q=pDst+w-1+wStep*(h-1);
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p - m*wStep-n);
				if (pixel == 255 )
				{	
					*q = (unsigned char)255;
					break;
				}
			}
		}
	}
	p=pSrc+w-2+wStep*(h-1);//the penultimate pixel of the last row
	if (*p != 255&&*p != 0)
	{
		ReleaseImage(org);
		return false;
	}
	if(*p==0) //not background pixel
	{
		q=pDst+w-2+wStep*(h-1);
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p -m*wStep+(n-1));
				if (pixel == 255 )
				{	
					*q = (unsigned char)255;
					break;
				}
			}
		}
	}
	p=pSrc+wStep*(h-2);//the penultimate pixel of the first row
	if (*p != 255&&*p != 0)
	{
		ReleaseImage(org);
		return false;
	}
	if(*p==0) //not background pixel
	{
		q=pDst+wStep*(h-2);
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p + (m-1)*wStep+n);
				if (pixel == 255 )
				{	
					*q = (unsigned char)255;
					break;
				}
			}
		}
	}
	//middle elements
	for (j=1;j<h-1;j++)
	{
		for (i=1;i<w-1;i++)
		{
			p=pSrc+j*wStep+i;
			if (*p != 255&&*p != 0)
			{
				ReleaseImage(org);
				return false;
			}
			if(*p==255) continue;//don't process the background pixel						
			q=pDst+j*wStep+i;
			//If there is a pixel that is not black in the structure element of the original image,
		//assign the pixel to white in the target image.
			for (m = 0;m < 3;m++ )//rows of structure element
			{
				for (n = 0;n < 3;n++)//columns of structure element
				{
					pixel = *(p + (m-1)*wStep +n-1);
					if (pixel == 255 )
					{	
						*q = (unsigned char)255;
						break;
					}
				}
			}
		}
	}
	ReleaseImage(org);//release the backup of the original image
	return true;
}
/************************************************************************/
/*  binary expansion                                                                    */
/************************************************************************/
bool Dilation(MvImage * img)
{
	if(img==NULL) return false;
	if (img->width<3||img->height<3) return false;
	MvImage* org=CloneImage(img);//original image
	if (org==NULL) return false;
	uchar* pSrc=org->imageData;
	uchar* pDst=img->imageData;
	int wStep=org->widthStep;
	int w=org->width;
	int h=org->height;
	uchar pixel;
	uchar* p=NULL;
	uchar* q=NULL;
	int i,j,m,n;

	
	//process the first row
	for (i=0;i<w-2;i++)
	{

		p=pSrc+i;
		if (*p != 255&&*p != 0) 
		{
			ReleaseImage(org);
			return false;

		}
		if(*p==0) continue;//don't process the black pixel						
		q=pDst+i;
		//If there is a pixel that is not black in the structure element of the original image,
		//assign the pixel to black in the target image.
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p + m*wStep + n);
				if (0 == pixel)
				{	
					*q = (unsigned char)0;
					break;
				}
			}
		}
	}


	//process the last row
	for (i=0;i<w-2;i++)
	{
		p=pSrc+wStep*(h-1)+i;
		if (*p != 255&&*p != 0)
		{
			ReleaseImage(org);
			return false;
		}
		if(*p==0) continue;//don't process the black pixel						
		q=pDst+wStep*(h-1)+i;
		//If there is a pixel that is not black in the structure element of the original image,
		//assign the pixel to black in the target image.
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p - m*wStep + n);
				if (pixel == 0 )
				{	
					*q = (unsigned char)0;
					break;
				}
			}
		}
	}


	//process the first row
	for (j=1;j<h-2;j++)
	{
		p=pSrc+j*wStep;
		if (*p != 255&&*p != 0)
		{
			ReleaseImage(org);
			return false;
		}
		if(*p==0) continue;//don't process the black pixel							
		q=pDst+j*wStep;
		//If there is a pixel that is not black in the structure element of the original image,
		//assign the pixel to black in the target image.
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p + m*wStep + n);
				if (pixel == 0 )
				{	
					*q = (unsigned char)0;
					break;
				}
			}
		}
	}


    //process the last row
	for (j=0;j<h-2;j++)
	{
		p=pSrc+j*wStep+w-1;
		if (*p != 255&&*p != 0) 
		{
			ReleaseImage(org);
			return false;
		}
		if(*p==0) continue;//don't process the black pixel						
		q=pDst+j*wStep+w-1;
		//If there is a pixel that is not black in the structure element of the original image,
		//assign the pixel to black in the target image.
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p + m*wStep -n);
				if (pixel == 0 )
				{	
					*q = (unsigned char)0;
					break;
				}
			}
		}
	}


    //the penultimate pixel of the first row
	p=pSrc+w-2;
	if (*p != 255&&*p != 0)
	{
		ReleaseImage(org);
		return false;
	}
	if(*p==255) //if the pixel == background color(white)
	{
		q=pDst+w-2;
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p + m*wStep+n-1);
				if (pixel == 0 )
				{	
					*q = (unsigned char)0;
					break;
				}
			}
		}
	}


    //the penultimate pixel of the last row
	p=pSrc+w-1+wStep*(h-2);
	if (*p != 255&&*p != 0)
	{
		ReleaseImage(org);
		return false;
	}
	if(*p==255) //if the pixel == background color(white)
	{
		q=pDst+w-1+wStep*(h-2);
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p + (m-1)*wStep-n);
				if (pixel == 0 )
				{	
					*q = (unsigned char)0;
					break;
				}
			}
		}
	}


    //the pixel int the lower right corner
	p=pSrc+w-1+wStep*(h-1);
	if (*p != 255&&*p != 0)
	{
		ReleaseImage(org);
		return false;
	}
	if(*p==255) //if the pixel == background color(white)
	{
		q=pDst+w-1+wStep*(h-1);
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p - m*wStep-n);
				if (pixel == 0 )
				{	
					*q = (unsigned char)0;
					break;
				}
			}
		}
	}


	//the penultimate pixel of the last row
	p=pSrc+w-2+wStep*(h-1);
	if (*p != 255&&*p != 0)
	{
		ReleaseImage(org);
		return false;
	}
	if(*p==255) //if the pixel == background color(white)
	{
		q=pDst+w-2+wStep*(h-1);
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p -m*wStep+(n-1));
				if (pixel == 0 )
				{	
					/**q = (unsigned char)0;*/
					break;
				}
			}
		}
	}


    //the penultimate pixel of the last row
	p=pSrc+wStep*(h-2);
	if (*p != 255&&*p != 0)
	{
		ReleaseImage(org);
		return false;
	}
	if(*p==255) //not background pixel
	{
		q=pDst+wStep*(h-2);
		for (m = 0;m < 3;m++ )//rows of structure element
		{
			for (n = 0;n < 3;n++)//columns of structure element
			{
				pixel = *(p + (m-1)*wStep+n);
				if (pixel == 0 )
				{	
					*q = (unsigned char)0;
					break;
				}
			}
		}
	}



	//middle elements
	for (j=1;j<h-1;j++)
	{
		for (i=1;i<w-1;i++)
		{
			p=pSrc+j*wStep+i;
			if (*p != 255&&*p != 0)
			{
				ReleaseImage(org);
				return false;
			}
			if(*p==0) continue;//don't process the black pixel						
			q=pDst+j*wStep+i;
			//If there is a pixel that is not black in the structure element of the original image,
		//assign the pixel to black in the target image.
			for (m = 0;m < 3;m++ )//rows of structure element
			{
				for (n = 0;n < 3;n++)//columns of structure element
				{
					pixel = *(p + (m-1)*wStep +n-1);
					if (pixel == 0 )
					{	
						*q = (unsigned char)0;
						break;
					}
				}
			}
		}
	}
	
	
	ReleaseImage(org);//release the backup of the original image
	return true;
}


/************************************************************************/
/* Binary opening operation                                                               */
/************************************************************************/
bool Opening(MvImage * img)
{
	bool flag=Erosion(img);
	if (false==flag) 
	{
		return false;
	}
	flag=Dilation(img);
	if (false==flag) 
	{
		return false;
	}
	return true;
}



/************************************************************************/
/* Binary closing operation                                                                  */
/************************************************************************/
bool Closing(MvImage * img)
{
	bool flag=Dilation(img);
	if (false==flag) 
	{
		return false;
	}
	flag=Erosion(img);
	if (false==flag) 
	{
		return false;
	}
	return true;
}


/************************************************************************/
/*  Mean filter of 3 ¡Á 3 window                                                                 */
/************************************************************************/
bool AverageFilter(MvImage * img,int mode)
{
	if(img==NULL) return false;
	
	if (img->width<3||img->height<3) return false;
	
	MvImage* org=CloneImage(img);//original image
	if (org==NULL) return false;
	
	uchar* pSrc=org->imageData;
	uchar* pDst=img->imageData;
	int wStep=org->widthStep;
	int w=org->width;
	int h=org->height;

	uchar* p=NULL;
	uchar* q=NULL;
	int i,j;

	if (MV_3X3==mode)
	{
		for (i=1;i<h-1;i++)
		{
		    for (j=1;j<w-1;j++)
			{
			    p=pSrc+j+i*wStep;
			    q=pDst+j+i*wStep;
			
			    double a1=*(p-wStep-1);//3¡Á3 model 1.1
			    double a2=*(p-wStep);//3¡Á3m model 1.2
			    double a3=*(p-wStep+1);//3¡Á3 model 1.3
			    double a4=*(p-1);//3¡Á3 model 2.1
                double a5=*(p);//3¡Á3 model 2.2
			    double a6=*(p+1);//3¡Á3 model 2.3
			    double a7=*(p+wStep-1);//3¡Á3 model 3.1
			    double a8=*(p+wStep);//3¡Á3 model 3.2
			    double a9=*(p+wStep+1);//3¡Á3 model 3.3
			
			    double a10=(a1+a2+a3+a4+a5+a6+a7+a8+a9)/9;
			    int temp=(int)(a10+0.5);
			    *q=(uchar)temp;
			}
		}
	    return true;
	}

	if (MV_5X5==mode)
	{
		for (i=2;i<h-2;i++)
		{
		    for (j=2;j<w-2;j++)
			{
			    p=pSrc+j+i*wStep;
			    q=pDst+j+i*wStep;

			
			    double a1=*(p-2*wStep-2);//5¡Á5 model 1.1
			    double a2=*(p-2*wStep-1);//5¡Á5 model 1.2
			    double a3=*(p-2*wStep);//5¡Á5 model 1.3
			    double a4=*(p-2*wStep+1);//5¡Á5 model 1.4
                double a5=*(p-2*wStep+2);//5¡Á5 model 1.5
			
			    double a6=*(p-1*wStep-2);//5¡Á5 model 2.1
			    double a7=*(p-1*wStep-1);//5¡Á5 model 2.2
			    double a8=*(p-1*wStep);//5¡Á5 model 2.3
			    double a9=*(p-1*wStep+1);//5¡Á5 model 2.4
                double a10=*(p-1*wStep+2);//5¡Á5 model 2.5

                double a11=*(p-2);//5¡Á5 model 3.1
		  	    double a12=*(p-1);//5¡Á5 model 3.2
			    double a13=*(p);//5¡Á5 model 3.3
		    	double a14=*(p+1);//5¡Á5 model 3.4
                double a15=*(p+2);//5¡Á5 model 3.5

		     	double a16=*(p+1*wStep-2);//5¡Á5 model 4.1
		    	double a17=*(p+1*wStep-1);//5¡Á5 model 4.2
		    	double a18=*(p+1*wStep);//5¡Á5 model 4.3
			    double a19=*(p+1*wStep+1);//5¡Á5 model 4.4
		    	double a20=*(p+1*wStep+2);//5¡Á5 model 4.5

			    double a21=*(p+2*wStep-2);//5¡Á5 model 5.1
			    double a22=*(p+2*wStep-1);//5¡Á5 model 5.2
			    double a23=*(p+2*wStep);//5¡Á5 model 5.3
			    double a24=*(p+2*wStep+1);//5¡Á5 model 5.4
			    double a25=*(p+2*wStep+2);//5¡Á5 model 5.5

			    double a26=(a1+a2+a3+a4+a5+a6+a7+a8+a9+a10+a11+a12+a13+a14+a15+a16+a17+a18+a19+a20+a21+a22+a23+a24+a25)/25;

			
			   int temp=(int)(a26+0.5);
			   *q=(uchar)temp;
			}
		}
	    return true;
	}

	if ((MV_5X5!=mode)&&(MV_3X3!=mode))
	{
		//Input window type parameter error
		return false;
	}
    
	return false;
}



/************************************************************************/
/*  function: to sort the array needed bythe median filter                                                                */
/************************************************************************/
void ArrayOrder(uchar* array,int num)
{
	int i,j;
	uchar temp;
	for (i=0;i<num-1;i++)
	{
		for (j=i+1;j<num;j++)
		{
			if (array[j]<array[i])
			{
				temp=array[i];
				array[i]=array[j];
				array[j]=temp;
			}
		}
	}
}



/************************************************************************/
/*  Mean filter of 3 ¡Á 3 window                                                                    */
/************************************************************************/
bool MedianFilter(MvImage * img,int mode)
{
	if(img==NULL) return false;
	
	if (img->width<3||img->height<3) return false;
	
	MvImage* org=CloneImage(img);//orginal image
	if (org==NULL) return false;
	
	uchar* pSrc=org->imageData;
	uchar* pDst=img->imageData;
	int wStep=org->widthStep;
	int w=org->width;
	int h=org->height;

	uchar* p=NULL;
	uchar* q=NULL;
	int i,j;
	
	if (MV_3X3==mode)
	{
		uchar array[9];
		for (i=1;i<h-1;i++)
		{
		    for (j=1;j<w-1;j++)
			{
			    p=pSrc+j+i*wStep;
			    q=pDst+j+i*wStep;
			
			    array[1]=*(p-wStep-1);//3¡Á3 model 1.1
			    array[2]=*(p-wStep);//3¡Á3 model 1.2
		     	array[3]=*(p-wStep+1);//3¡Á3 model 1.3
			    array[4]=*(p-1);//3¡Á3 model 2.1
                array[5]=*(p);//3¡Á3 model 2.2
		    	array[6]=*(p+1);//3¡Á3 model 2.3
		        array[7]=*(p+wStep-1);//3¡Á3 model 3.1
		     	array[8]=*(p+wStep);//3¡Á3 model 3.2
		    	array[9]=*(p+wStep+1);//3¡Á3 model 3.3

			    ArrayOrder(array,9);

			    *q=array[4];
			
			}
		}
	    return true;
	}

	if (MV_5X5==mode)
	{
		uchar array[25];
		for (i=2;i<h-2;i++)
		{
		    for (j=2;j<w-2;j++)
			{
			    p=pSrc+j+i*wStep;
			    q=pDst+j+i*wStep;

     			array[1]=*(p-2*wStep-2);//5¡Á5 model 1.1
	    		array[2]=*(p-2*wStep-1);//5¡Á5 model 1.2
		    	array[3]=*(p-2*wStep);//5¡Á5 model 1.3
			    array[4]=*(p-2*wStep+1);//5¡Á5 model 1.4
                array[5]=*(p-2*wStep+2);//5¡Á5 model 1.5
			
			    array[6]=*(p-1*wStep-2);//5¡Á5 model 2.1
			    array[7]=*(p-1*wStep-1);//5¡Á5 model 2.2
			    array[8]=*(p-1*wStep);//5¡Á5 model 2.3
			    array[9]=*(p-1*wStep+1);//5¡Á5 model 2.4
                array[10]=*(p-1*wStep+2);//5¡Á5 model 2.5

                array[11]=*(p-2);//5¡Á5 model 3.1
			    array[12]=*(p-1);//5¡Á5 model 3.2
			    array[13]=*(p);//5¡Á5 model 3.3
			    array[14]=*(p+1);//5¡Á5 model 3.4
                array[15]=*(p+2);//5¡Á5 model 3.5

	    		array[16]=*(p+1*wStep-2);//5¡Á5 model 4.1
	    		array[17]=*(p+1*wStep-1);//5¡Á5 model 4.2
	    		array[18]=*(p+1*wStep);//5¡Á5 model 4.3
	    		array[19]=*(p+1*wStep+1);//5¡Á5 model 4.4
	    		array[20]=*(p+1*wStep+2);//5¡Á5 model 4.5

	     		array[21]=*(p+2*wStep-2);//5¡Á5 model 5.1
	     		array[22]=*(p+2*wStep-1);//5¡Á5 model 5.2
	    		array[23]=*(p+2*wStep);//5¡Á5 model 5.3
	    		array[24]=*(p+2*wStep+1);//5¡Á5 model 5.4
	    		array[25]=*(p+2*wStep+2);//5¡Á5 model 5.5
			

		    	ArrayOrder(array,25);

		    	*q=array[12];
			
			}
		}
        return true;
	}

	if ((MV_5X5!=mode)&&(MV_3X3!=mode))
	{
		//Input window type parameter error
		return false;
	}
	
	return false;
}


