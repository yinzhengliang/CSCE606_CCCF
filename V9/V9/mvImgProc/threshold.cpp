//////////////////////////////////////////////////////////////////////////////
//
// threshold.CPP 
//
//////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "threshold.h"

void ImBinarize (MvImage* pSrcImageBufId, long Condition, double* thresholdValue)
{
	//traverse the ordinate of the image
	int y;
	//traverse the abscissa of the image
	int x;
	MvImage* SrcImageBufId;

	uchar*  pImageDataSrc;


	if (pSrcImageBufId)
	{
		SrcImageBufId = pSrcImageBufId;
	}

	

	//width and height of image
	int nWidth			= SrcImageBufId->width;
	int nHeight			= SrcImageBufId->height;
	
	//Actual space occupied by one pixel in the memory
	int nSaveWidth = SrcImageBufId->widthStep;
	
	
	//pointer to the original image
	pImageDataSrc = SrcImageBufId->imageData;
		
	
	
	switch (Condition)
	{
	case MV_MANUAL:
				
		for(y=0; y<nHeight ; y++ )
			for(x=0; x<nWidth ; x++ )
			{
				if( *(pImageDataSrc+y*nSaveWidth+x) < *thresholdValue)
					*(pImageDataSrc+y*nSaveWidth+x) = 0;
				else
					*(pImageDataSrc+y*nSaveWidth+x) = 255;
				
			}
		break;
	case MV_ITERATE:

		long i,j;					// loop variable	
		unsigned char pixel;		// pixel value	
		long lHistogram[256];		// histogram array
		
		//threshold value£¬max gray value and min gray value£¬mean gray value of two zones
		unsigned char iThreshold,iNewThreshold,iMaxGrayValue,iMinGrayValue,
			iMean1GrayValue,iMean2GrayValue;
		
		long lP1,lP2,lS1,lS2;		// intermediate variables used to calculate mean gray value of a zone
		int iIterationTimes;		// repetitions
	
		for (i = 0; i < 256;i++)
		{
			lHistogram[i]=0;
		}
		
		//get histogram
		iMaxGrayValue = 0;
		iMinGrayValue = 255;
		for (i = 0;i < nWidth ;i++)
		{
			for(j = 0;j < nHeight ;j++)
			{
				// pointer to	penultimate j row, i-th pixel in the original image	
				// 	lpSrc = pImageData+j*lLineBytes+i;
				pixel = (unsigned char)*(pImageDataSrc+j*nSaveWidth+i);
				
				lHistogram[pixel]++;
				//modify max gray value and min gray value
				if(iMinGrayValue > pixel)
				{
					iMinGrayValue = pixel;
				}
				if(iMaxGrayValue < pixel)
				{
					iMaxGrayValue = pixel;
				}
			}
		}
		
		//calculate the optimal threshold by iteration
		iNewThreshold = (iMinGrayValue + iMaxGrayValue)/2;
		iThreshold = 0;
		
		for(iIterationTimes = 0; iThreshold != iNewThreshold && 
			iIterationTimes < 100;iIterationTimes ++)
		{
			iThreshold = iNewThreshold;
			lP1 =0;
			lP2 =0;
			lS1 = 0;
			lS2 = 0;
			//calculate mean gray value of two zones
			for (i = iMinGrayValue;i < iThreshold;i++)
			{
				lP1 += lHistogram[i]*i;
				lS1 += lHistogram[i];
			}
			iMean1GrayValue = (unsigned char)(lP1 / lS1);
			for (i = iThreshold+1;i < iMaxGrayValue;i++)
			{
				lP2 += lHistogram[i]*i;
				lS2 += lHistogram[i];
			}
			iMean2GrayValue = (unsigned char)(lP2 / lS2);
			iNewThreshold =  (iMean1GrayValue + iMean2GrayValue)/2;
		}
		
		//	RegionSegFixThreshold(pDib,iThreshold);
		if (thresholdValue)
		{
			*thresholdValue = iThreshold;
		}
		
		for(y=0; y<nHeight ; y++ )
			for(x=0; x<nWidth ; x++ )
			{
				if( *(pImageDataSrc+y*nSaveWidth+x) < iThreshold)
					*(pImageDataSrc+y*nSaveWidth+x) = 0;
				else
					*(pImageDataSrc+y*nSaveWidth+x) = 255;
				
			}

		break;
	case MV_OSTU:
			
		int x0=0; int y0=0;  int dx=nHeight;  int dy=nWidth;
		
		unsigned char *np; //image pointer
		int threshold=1; // threshold
		int ihist[256]; // image histogram£¬256 points
		int k; // various counters
		int n, n1, n2, gmin, gmax;
		double m1, m2, sum, csum, fmax, sb;
		// set the histogram to 0
		memset(ihist, 0, sizeof(ihist));
		gmin=255; gmax=0;
		// create the histogram
		for (i = x0 + 1; i < x0 + dx - 1; i++)
		{
			np = pImageDataSrc+i*nSaveWidth+x0+1;
			for (j = y0 + 1; j < y0 + dy - 1; j++)
			{
				int m = *np;
				ihist[*np]++;
				if(*np > gmax)
					gmax=*np;
				if(*np < gmin)
					gmin=*np;
				np++; /* next pixel */
			}
		}
		// set up everything
		sum = csum = 0.0;
		n = 0;
		for (k = 0; k <= 255; k++)
		{
			sum += (double) k * (double) ihist[k]; /* x*f(x) mass moment*/
			n += ihist[k]; /* f(x) mass */
		}
		
	
		// do the otsu global thresholding method
		fmax = -1.0;
		n1 = 0;
		for (k = 0; k < 255; k++) 
		{
			n1 += ihist[k];
			if (!n1)
			{ continue; }
			
			n2 = n - n1;
			if (n2 == 0)
			{ break; }
			
			csum += (double) k *ihist[k];
			m1 = csum / n1;
			m2 = (sum - csum) / n2;
			sb = (double) n1 *(double) n2 *(m1 - m2) * (m1 - m2);
			/* bbg: note: can be optimized. */
			
			if (sb > fmax) 
			{
				fmax = sb;
				threshold = k;
			}
		}
		if (thresholdValue)
		{
			*thresholdValue = threshold;
		}
		
		for(y=0; y<nHeight ; y++ )
			for(x=0; x<nWidth ; x++ )
			{
				if( *(pImageDataSrc+y*nSaveWidth+x) < threshold)
					*(pImageDataSrc+y*nSaveWidth+x) = 0;
				else
					*(pImageDataSrc+y*nSaveWidth+x) = 255;
				
			}
			
				
	}

}