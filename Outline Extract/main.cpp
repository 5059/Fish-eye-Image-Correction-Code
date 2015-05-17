//������ͷ�ļ�
#include "tools.h"
#include "findCircleParameter.h"
#include "corrector.h"

#include "latitudeCorrection.h"


//���̶���ڵ�
int main(int argc, char** argv)
{
	//��ͼƬ���ڴ���
	if (tools::readImage())
	{
		Mat source_image = tools::GetImage();

		if (findCircleParameter::init(source_image))
		{
			findCircleParameter::findCircle();

			if (IDOK == MessageBox(NULL, "Would you want to check the FOV of fish-eye lens is valid?", "Check FOV", IDOK))
			{
				findCircleParameter::checkVarify();
			}
			else
				cout << "You have not choose to check the FOV" << endl;

			if (IDOK == MessageBox(NULL, "Is this Image a HeaveAndEarth circular fish-eye image?", "Answer a question", IDOK))
			{
				corrector::dispHeaveAndEarthCorrectImage(source_image);
			}
		}
	}	 

//
//
//
//	//��һ����������ͼ���У��
//	Mat ret=latitudeCorrection4(imgOrg, center, radius,/*PI*5/6*/PI/180*90,PI/180*90);
//	imwrite("left.jpg", ret);
//	destroyWindow(window_name);
////	destroyWindow(winname);
//	namedWindow("ret", CV_WINDOW_NORMAL);
//	resizeWindow("ret", 512, 512);
//	imshow("ret", ret);
//
//
//	namedWindow("org", CV_WINDOW_NORMAL);
//	resizeWindow("org", 512, 512);
//	imshow("org", imgOrg);
//	Mat ret1 = latitudeCorrection5(imgOrg, center, radius,PI/180*90,PI/180*90);//�������������ĵ�������Ӱ��
//	imshow("org", ret1);	 
//	imwrite("forwardMap.jpg",ret1);
//	/*
//		//ʹ�ö��ַ�����У������ͼ�������Ǿ�γУ����
//	//Mat img1, img2, img3;
//	//img1=latitudeCorrection( imgOrg.clone(),  center,  radius,PI*17/20);
//	//imshow("image1", img1);
//	//for (double r = PI / 20; r <= PI; r += PI / 20)
//	//{
//	//	img2 = latitudeCorrection(imgOrg.clone(), center, radius,  r);
//	//	//img2 = latitudeCorrection(imgOrg.clone(), center, radius, r,Forward);
//	//	if (img2.data)
//	//	{
//	//		imshow("img2", img2);
//	//		waitKey(5);
//	//	}
//	//	else
//	//	{
//	//		cout << "Failed to rectified!" << endl;
//	//	}
//	//}
//
//	*/
//	
//
//	//�����㷨����
//	//std::ostringstream fileName;
//	//double stepAng = PI / 6;
//	//int Number = 0;
//	//for (double i = -PI / 2; i < PI / 2; i += stepAng)
//	//{
//	//	for (double j = -PI / 2; j < PI / 2; j += stepAng)
//	//	{
//	//		Mat ret1 = latitudeCorrection3(imgOrg, center, radius, PERSPECTIVE, i, j);
//	//		////imshow("org", ret1);
//	//		fileName << "stitch\\" << ++Number << ".jpg";
//	//		imwrite(fileName.str().c_str(), ret1);
//	//		//std::cout << fileName.str() << endl;
//	//		fileName.str("");
//	//	}
//	//}
//
//	
//	waitKey();
	return 0;
}