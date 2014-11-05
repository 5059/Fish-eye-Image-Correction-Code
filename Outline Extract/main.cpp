//������ͷ�ļ�
#include "globalInclude.h"

#include "outlineExtract.h"
#include "latitudeCorrection.h"
#include "cylinderCorrection.h"
#include "panoramaExpansion.h"
//�÷���ʾ
void Usage()
{
	cout << "Usage: extract.exe <image-path> " << endl;
}


/* Best Parameter for images*/
//(2,10) for 1.jpg
//(6,149) for 2.jpg
//(5,20) for 3.jpg
//(5,50) for 4.jpg
//(5,30) for 5.jpg
//(6,40) for 6.jpg
//(6,30) for 7.jpg
//(5,40) for 8.jpg
//(8,16) for 9.jpg
//(5,20) for 10.jpg
//(7,32) for 11.jpg


//�������ʼֵ�趨
int N_slider = 5;				//��Ƕ���ɨ�跨�ĽǶȷ�������ֵ
const int N_max = 15;			//��Ƕ���ɨ�跨�ĽǶȷ���������趨ֵ

int threshold_slider = 40;		//��ɨ�����ֵ
const int threshold_max = 255;	//��ɨ����ֵ����趨ֵ


extern const char window_name[] = "Outline Extraction";

Mat imgOrg;						//ԭʼͼ��
Point2i center;					//��ȡ�������ģ������趨Ϊ����ͼ��Բ�����������
int radius = 0;					//����ͼ��Բ����Ч����İ뾶

//Ϊȷ������Բ����Ч������������õĻص���������OpenCVʹ��
void On_N_trackbar(int, void*)
{
	cout << endl;
	cout << "N_Slider"<<N_slider << endl;
	cout << "Threshold_Slider" << threshold_slider << endl;
	//�ñ�Ƕ���ɨ�跨ȡ��Բ����Ч�����Բ�ĺͰ뾶�Ĳ���
	revisedScanLineMethod(imgOrg, center, radius, threshold_slider, N_slider);
}
void On_threshold_trackbar(int, void*)
{
	cout << endl;
	cout << "N_Slider: " << N_slider << endl;
	cout << "Threshold_Slider: " << threshold_slider << endl;
	//�ñ�Ƕ���ɨ�跨ȡ��Բ����Ч�����Բ�ĺͰ뾶�Ĳ���
	revisedScanLineMethod(imgOrg, center, radius, threshold_slider, N_slider);
}


std::vector<std::vector<cv::Point>> lines;
std::vector<cv::Point> points;

std::string winname = "image";

cv::Mat source;
cv::Mat image;
cv::Mat result;

static void onMouse(int event, int x, int y, int, void* args)
{

	cv::Point pt(x, y);
	switch (event)
	{
	case cv::EVENT_LBUTTONDOWN:
		cv::circle(image, pt, 15, cv::Scalar(0, 255, 0), -1);
		cv::imshow(winname, image);
		points.push_back(pt);
		if (2 == points.size())
		{
			cv::line(image, points[0], points[1], cv::Scalar(0, 255, 255), 3);

			cv::imshow(winname, image);
			lines.push_back(points);
			points.clear();
		}

		break;
	case cv::EVENT_MOUSEMOVE:
		//cout << "(x, y) = (" << x << ", " << y << ")" << endl;
	default:
		;
	}
}

//���̶���ڵ�
int main(int argc, char** argv)
{
	//����Ҫ��һ��ͼ����Ϊ�������
	if (argc < 2)
	{
		Usage();
		return -1;
	}
	//��ͼ������ڴ�
	imgOrg = imread(argv[1], IMREAD_COLOR);
	if (!imgOrg.data)
	{
		cout << "Failed to read in a image." << endl;
		return -1;
	}
	//namedWindow(window_name, CV_WINDOW_NORMAL);
	//resizeWindow(window_name, 512, 612);
	//moveWindow(window_name, 800, 300);
	//const char N_trackbar_name[]="N (0-15)";
	//const char Threshold_trackbar_name[] = "Threshold(0-255)";
	//createTrackbar(N_trackbar_name, window_name, &N_slider, N_max, On_N_trackbar);
	//createTrackbar(Threshold_trackbar_name, window_name, &threshold_slider, threshold_max, On_threshold_trackbar);
	//On_N_trackbar(N_slider,0);
	//On_threshold_trackbar(threshold_slider,0);
	//waitKey();//���������ͼ��Բ����Ч�����Բ������Ͱ뾶

	//�����������Ч����뾶��Բ�ĵĵĲ�����ȡ����
	center = Point(1097, 1102);
	radius = 1097;	

	image = imgOrg.clone();
	namedWindow(winname, CV_WINDOW_NORMAL);
	resizeWindow(winname, 512, 512);
	moveWindow(winname, 800, 300);
	//circle(image, center, radius, Scalar(0, 0, 255), image.cols / 300);
	//circle(image, center, image.cols/300, Scalar(0, 255, 255), -1);
	imshow(winname, image);
	setMouseCallback(winname, onMouse);
	waitKey();


















	/*��һ����ֻ���������Ƭ�ǳ�����պʹ�������ͼ����е�У��
		Mat img1, img2, img3;
	for (double r = PI / 20; r <= PI; r += PI / 20)
	{
		img1=panoramaExpansion(imgOrg.clone(), center, radius,r,Forward);
		if (img1.data)
		{
			imshow("ret", img1);
			waitKey(10);			
		}
	}
	*/



	//��һ����������ͼ���У��
	//Mat ret=latitudeCorrection2(imgOrg, center, radius);
	//destroyWindow(window_name);
	//namedWindow("ret", CV_WINDOW_NORMAL);
	//resizeWindow("ret", 512, 512);
	//imshow("ret", ret);
	//namedWindow("org", CV_WINDOW_NORMAL);
	//resizeWindow("org", 512, 512);
	//imshow("org", imgOrg);

	 
	/*
		//ʹ�ö��ַ�����У������ͼ�������Ǿ�γУ����
	//Mat img1, img2, img3;
	//img1=latitudeCorrection( imgOrg.clone(),  center,  radius,PI*17/20);
	//imshow("image1", img1);
	//for (double r = PI / 20; r <= PI; r += PI / 20)
	//{
	//	img2 = latitudeCorrection(imgOrg.clone(), center, radius,  r);
	//	//img2 = latitudeCorrection(imgOrg.clone(), center, radius, r,Forward);
	//	if (img2.data)
	//	{
	//		imshow("img2", img2);
	//		waitKey(5);
	//	}
	//	else
	//	{
	//		cout << "Failed to rectified!" << endl;
	//	}
	//}

	*/
		
	waitKey();
	return 0;
}



//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <stdlib.h>
//#include <stdio.h>
//using namespace cv;
///// Global variables
//Mat src, src_gray;
//Mat dst, detected_edges;
//int edgeThresh = 1;
//int lowThreshold;
//int const max_lowThreshold = 100;
//int ratio = 3;
//int kernel_size = 3;
//char* window_name = "Edge Map";
///**
//* @function CannyThreshold
//* @brief Trackbar callback - Canny thresholds input with a ratio 1:3
//*/
//void CannyThreshold(int, void*)
//{
//	/// Reduce noise with a kernel 3x3
//	blur(src_gray, detected_edges, Size(3, 3));
//	/// Canny detector
//	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
//	/// Using Canny��s output as a mask, we display our result
//	dst = Scalar::all(0);
//	src.copyTo(dst, detected_edges);
//	cvtColor(dst, dst, CV_BGR2GRAY);
//	cv::threshold(dst, dst, 60, 255, CV_THRESH_BINARY);
//	imshow(window_name, dst);
//	
//	imwrite("Hough_edge.tiff", dst);
//}
///** @function main */
//int main(int argc, char** argv)
//{
//	/// Load an image
//	src = imread(argv[1]);
//	if (!src.data)
//	{
//		return -1;
//	}
//	/// Create a matrix of the same type and size as src (for dst)
//	dst.create(src.size(), src.type());
//	/// Convert the image to grayscale
//		cvtColor(src, src_gray, CV_BGR2GRAY);
//	/// Create a window
//	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
//	/// Create a Trackbar for user to enter threshold
//	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
//	/// Show the image
//	CannyThreshold(0, 0);
//	/// Wait until user exit program by pressing a key
//	waitKey(0);
//	return 0;
//}