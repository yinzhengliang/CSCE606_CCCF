/************************************************************************/
/* Image processing related operations                                               */
/************************************************************************/
#include "imgProc.h"

bool ImRotate(MvImage* ImageBufId,double Angle,double CenX,double CenY)
{
	if (ImageBufId==NULL) return false;
	MvImage* rotImage=CreateImage(ImageBufId->width,ImageBufId->height,ImageBufId->depth,ImageBufId->nChannels);
	int width=ImageBufId->width;
	int height=ImageBufId->height;
	int widthStep=ImageBufId->widthStep;
	uchar* rotData=rotImage->imageData;
	Angle=Angle*PI/180;
	for (int y2=0;y2<height;y2++)
	{
		for (int x2=0;x2<width;x2++)
		{
			float x1=(x2-CenX)*cos(Angle)-(y2-CenY)*sin(Angle)+CenX;
			float y1=(x2-CenX)*sin(Angle)+(y2-CenY)*cos(Angle)+CenY;
			int fx1=floor(x1);
			int fy1=floor(y1);
			float x=x1-fx1;
			float y=y1-fy1;
			if (fx1>=0&&fy1>=0&&fx1<width&&fy1<height)
			{
				if(fx1<=width-1||fy1<=height-1) rotData[y2*widthStep+x2]=ImageBufId->imageData[fy1*widthStep+fx1];
				else
				{
					uchar f00=ImageBufId->imageData[fy1*widthStep+fx1];
					uchar f10=ImageBufId->imageData[fy1*widthStep+fx1+1];
					uchar f01=ImageBufId->imageData[(fy1+1)*widthStep+fx1];
					uchar f11=ImageBufId->imageData[(fy1+1)*widthStep+fx1+1];
					rotData[y2*widthStep+x2]=(f10-f00)*x+(f01-f00)*y+(f11+f00-f01-f10)*x*y+f00;
				}
			}
			else
				rotData[y2*widthStep+x2]=(uchar)255;
		}
	}
	SetImageROI(rotImage,mvRect(0,0,ImageBufId->width,ImageBufId->height));
	Copy(rotImage,ImageBufId);
	ReSetImageROI(rotImage);
	ReleaseImage(rotImage);
	return true;
}


bool ImTranslate(MvImage* ImageBufId,double XDisplacement,double YDisplacement)
{
	if (ImageBufId==NULL) return false;
	MvImage* dstImage=CreateImage(ImageBufId->width,ImageBufId->height,ImageBufId->depth,ImageBufId->nChannels);
	int width=ImageBufId->width;
	int height=ImageBufId->height;
	int widthStep=ImageBufId->widthStep;
	uchar* dstData=dstImage->imageData;
	for (int y2=0;y2<height;y2++)
	{
		for (int x2=0;x2<width;x2++)
		{
			float x1=x2-XDisplacement;
			float y1=y2-YDisplacement;
			int fx1=floor(x1);
			int fy1=floor(y1);
			float x=x1-fx1;
			float y=y1-fy1;
			if (fx1>=0&&fy1>=0&&fx1<width-1&&fy1<height-1)
			{
				if(fx1<=width-1||fy1<=height-1) dstData[y2*widthStep+x2]=ImageBufId->imageData[fy1*widthStep+fx1];
				else
				{
					uchar f00=ImageBufId->imageData[fy1*widthStep+fx1];
					uchar f10=ImageBufId->imageData[fy1*widthStep+fx1+1];
					uchar f01=ImageBufId->imageData[(fy1+1)*widthStep+fx1];
					uchar f11=ImageBufId->imageData[(fy1+1)*widthStep+fx1+1];
					dstData[y2*widthStep+x2]=(f10-f00)*x+(f01-f00)*y+(f11+f00-f01-f10)*x*y+f00;
				}
			}
			else
				dstData[y2*widthStep+x2]=(uchar)255;
		}
	}
	SetImageROI(dstImage,mvRect(0,0,ImageBufId->width,ImageBufId->height));
	Copy(dstImage,ImageBufId);
	ReSetImageROI(dstImage);
	ReleaseImage(dstImage);
	return true;
}

MvImage* ImFourier(MvImage* ImageBufId)
{
	if (ImageBufId==NULL) return NULL;
	int width=ImageBufId->width;
	int height=ImageBufId->height;
	int widthStep=ImageBufId->widthStep;
	uchar* srcData=ImageBufId->imageData;
	double dTemp;

	long	i;
	long	j;
	// the width and height for FFT£¨integer power of 2£©
	long	w;
	long	h;
	int		wp;
	int		hp;
	// initial value assignment
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	// calculate the width and height for FFT£¨integer power of 2£©
	while(w * 2 <= width)
	{
		w *= 2;
		wp++;
	}
	while(h * 2 <= height)
	{
		h *= 2;
		hp++;
	}
	// memory allocation
	MvImage* dstImage=CreateImage(w,h,ImageBufId->depth,ImageBufId->nChannels);
	uchar* dstData=dstImage->imageData;
	int dstStep=dstImage->widthStep;
	complex<double> *TD = new complex<double>[w * h];
	complex<double> *FD = new complex<double>[w * h];
	for(i = 0; i < h; i++)	// rows
	{
		for(j = 0; j < w; j++)	// columns
		{			
			// assign values to time domain
			TD[w * i+j] = complex<double>(srcData[i*widthStep+j], 0);
		}
	}
	for(i = 0; i < h; i++)
	{	// FFT for y direction
		FFT(&TD[w * i], &FD[w * i], wp);
	}
	// save the transform result
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			TD[i + h * j] = FD[j + w * i];
		}
	}
	for(i = 0; i < w; i++)
	{
		// FFT for x direction
		FFT(&TD[i * h], &FD[i * h], hp);
	}
	for(i = 0; i < h; i++)	// rows
	{
		for(j = 0; j < w; j++)	// columns
		{	// calculate spectrum
			dTemp = sqrt(FD[j * h + i].real() * FD[j * h + i].real() + 
				FD[j * h + i].imag() * FD[j * h + i].imag()) / 100;
			// > 255?
			if (dTemp > 255)
			{	// if yes, set to 255
				dTemp = 255;
			}
			//pointer pointing to (i<h/2 ? i+h/2 : i-h/2) row£¬(j<w/2 ? j+w/2 : j-w/2)th pixel  of DIB
			//don't use directly i or j. Aim to move the origin after transform to the center
			//lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			dstData[(h - 1 - (i<h/2 ? i+h/2 : i-h/2))*dstStep+(j<w/2 ? j+w/2 : j-w/2)]=(uchar)(dTemp);
		}
	}
	// delete tempory variables
	delete TD;
	delete FD;
	// return
	return dstImage;
}


static void FFT(complex<double> * TD, complex<double> * FD, int r)
{
	long	count; 
	int		i,j,k; 
	int		bfsize,p; 	
	double	angle,cos_angle,sin_angle; 	// angle
	complex<double> *W,*X1,*X2,*X; 	// calculate FFT points
	count = 1 << r;
	W  = new complex<double>[count / 2]; //allocate memory for computing
	X1 = new complex<double>[count];
	X2 = new complex<double>[count];
	for(i = 0; i < count/2; i++) 	// calculate weighted coefficent
	{
		angle = -i * PI * 2 / count;
		cos_angle = cos(angle);
		sin_angle = sin(angle);
		W[i] = complex<double> (cos_angle, sin_angle);
	}
	memcpy(X1, TD, sizeof(complex<double>) * count); // write time domain to X1
	for(k = 0; k < r; k++) // use butterfly algorithm for FFT
	{
		for(j = 0; j < 1 << k; j++)
		{
			bfsize = 1 << (r-k);
			for(i = 0; i < bfsize / 2; i++)
			{
				p = j * bfsize;
				X2[i + p] = X1[i + p] + X1[i + p + bfsize / 2];
				X2[i + p + bfsize / 2] = (X1[i + p] - X1[i + p + bfsize / 2]) * W[i * (1<<k)];
			}
		}
		X  = X1;
		X1 = X2;
		X2 = X;
	}
	for(j = 0; j < count; j++) // resort
	{
		p = 0;
		for(i = 0; i < r; i++)
		{
			if (j&(1<<i))
			{
				p+=1<<(r-i-1);
			}
		}
		FD[j]=X1[p];
	}
	// release the memory
	delete W;
	delete X1;
	delete X2;
}