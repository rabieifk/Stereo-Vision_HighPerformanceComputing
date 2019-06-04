#include "stdafx.h"
#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <highgui.h>
#include <windows.h> 
#include<math.h> 
#include <stdio.h> 
#include <conio.h>
#include <iostream>
#include <fstream>
#include <ctime> 
#include <smmintrin.h>
#include "time.h"
//define-------------------------------
#define		IMG_NO_OF_COLUMNS  		384
#define		IMG_NO_OF_ROWS			288
//prototype----------------------------
double openCv();//normal Implementation of stereo_vision
double SIMD();//SSE3 Implementation of stereo_vision
//main function
int _tmain(int argc, _TCHAR* argv[])
{
	double time1, time2;
	time1 = openCv ();
	time2 = SIMD ();
	printf ("Execution time (Normal Implementation) = %lf\n", time1);
	printf ("Execution time (SSE3 Implementation) = %lf\n", time2);
	printf ("Speedup = %lf\n", time1 / time2);
	printf ("Press ENTER to continue ...");
	getchar();
	return 0;
}

double openCv()
{
	//defenition of image in openCv
	IplImage *img_L;
	IplImage *img_R;
	IplImage *img_out;
	//function that load image
	img_L = cvLoadImage("imL.png",0);
	img_R = cvLoadImage("imR.png",0);
	//for showing loaded image
	//cvShowImage("imgL.png",img_L);
	//cvShowImage("imgR.png",img_R);

	//defenition of imageData for access to each pixel
	unsigned char *imgData_out;
	unsigned char *imgDataL;
	unsigned char *imgDataR;

	unsigned int row_indx;
	unsigned int col_indx;

	int s;
	int smin;
	int kStar;

	clock_t start, end;
	double elapsed;

	img_out = cvCreateImage(cvGetSize(img_L),img_L->depth,1);
	imgData_out = (unsigned char *)img_out->imageData;
	imgDataL = (unsigned char *)img_L->imageData;
	imgDataR = (unsigned char *)img_R->imageData;

	start = clock();
		for (int i = 1; i < IMG_NO_OF_ROWS; i++) 
		{
			for (int j = 1; j < IMG_NO_OF_COLUMNS; j++) 
			{
				smin = 255;
				kStar = 0;
				for(int k=0 ;k<16;k++){
					s=0;
					for(int a=-2 ;a<3;a++)
						for(int b=-2 ;b<3;b++)
						{
							s+=abs(*(imgDataR + (i+a) * IMG_NO_OF_COLUMNS + (j+b))- *(imgDataL + (i+a) * IMG_NO_OF_COLUMNS + (j+b+k)));		
						}
						if ( s < smin)
						{
							smin = s;
							kStar = k;
						}					
					*(imgData_out + i*IMG_NO_OF_COLUMNS +j)= kStar*16;
				}
			}
		}
	end = clock ();
	elapsed = ((double) (end-start));
	cvSaveImage("output_openCv.png",img_out,0);
	return elapsed;
}


double SIMD()
{
	IplImage *in_img_L;
	IplImage *in_img_R;
	IplImage *out_img;

	unsigned char *pSrc_L;
	unsigned char *pRes;
	unsigned char *pSrc_R;
	__m128i r,l,s;
	__m128i temp;
	
	unsigned int row_indx;
	unsigned int col_indx;

	clock_t start, end;
	double elapsed;

	in_img_L = cvLoadImage("imL.png",0);
	in_img_R = cvLoadImage("imR.png",0);

	//cvShowImage("imL.png",in_img_L);
	//cvShowImage("imR.png",in_img_R);

	out_img = cvCreateImage (cvGetSize(in_img_L),in_img_L->depth,1);
	
	pSrc_L = (unsigned char *) in_img_L->imageData;
	pSrc_R = (unsigned char *) in_img_R->imageData;
	pRes =	 (unsigned char *) out_img->imageData;
	__m128i smin,shift,shift1,smax ;
	int kstar,diff;

	shift  = _mm_set1_epi8(unsigned char(255));
	shift1 = shift;
	shift = _mm_srli_si128 (shift,13);
	shift1 = _mm_srli_si128 (shift1,14);
	smax = _mm_set1_epi16 (3*3*255);
	smax = _mm_and_si128 (smax, shift1);

	start = clock();
	for (row_indx = 1; row_indx < IMG_NO_OF_ROWS -1; row_indx++) 
	{
			for (col_indx = 1; col_indx < IMG_NO_OF_COLUMNS ; col_indx++)
			{ 
				smin = smax;
				kstar = 0;
				for(int k=0 ;k<16;k++)
				{
					s = _mm_setzero_si128();
					for(int i=row_indx-1 ;i<row_indx+1;i++)
					{
						r = _mm_loadu_si128((__m128i *) (pSrc_R + i*IMG_NO_OF_COLUMNS +  col_indx));
						l = _mm_loadu_si128((__m128i *) (pSrc_L + i*IMG_NO_OF_COLUMNS +  col_indx + k));
						r = _mm_and_si128 (r, shift);
						l = _mm_and_si128 (l, shift);
						s = _mm_add_epi16(s,_mm_sad_epu8(r,l));

					}
					diff = _mm_cvtsi128_si32( _mm_cmplt_epi16 (s,smin));
					smin = _mm_min_epi16(smin,s);
					if(diff)
						kstar = k;
				}
				*(pRes + row_indx * IMG_NO_OF_COLUMNS + col_indx) = kstar*15;			
			}
	}
	end = clock ();
	cvSaveImage("output_SIMD.png",out_img,0);
	elapsed = ((double) (end-start)); 
    return elapsed;
}
