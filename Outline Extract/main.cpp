//������ͷ�ļ�
#include "tools.h"
#include "findCircleParameter.h"
#include "corrector.h"

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

			if (IDOK == MessageBox(NULL, "Do you want to correct the fish-eye image using the LCCP method?", "Correction Select",IDOK))
			{
#pragma region У�������趨��
				correctParameters params;
				params.imgOrg = source_image;

				findCircleParameter::getCircleParatemer(params.center, params.radius);

				params.w_longtitude = PI / 2;
				params.w_latitude = PI / 2;
				params.distMap = LATITUDE_LONGTITUDE;
				params.theta_left = 0;
				params.phi_up = 0;
				params.camerFieldAngle = findCircleParameter::FOV;
				params.camProjMode = EQUIDISTANCE;
				params.typeOfCorrect = Reverse;
#pragma endregion

				corrector adjuster;
				adjuster.correctImage(params, corrector::correctMethod::PERSPECTIVE_LONG_LAT_MAP_CAMERA_LEN_MODEL_REVERSE_W_HALF_PI);
			}
		}
	}	 
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