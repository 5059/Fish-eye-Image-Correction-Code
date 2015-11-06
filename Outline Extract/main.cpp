//������ͷ�ļ�
#include "tools.h"
#include "findCircleParameter.h"
#include "corrector.h"
#include "viewer.h"
#include "imagesStitcher.h"


void help()
{

}

//���̶���ڵ�
int main(int argc, char** argv)
{
	/*
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
				//adjuster.correctImage(params, corrector::correctMethod::LONG_LAT_MAP_REVERSE_FORWARD);
				//adjuster.correctImage(params, corrector::correctMethod::PERSPECTIVE_LONG_LAT_MAP_CAMERA_LEN_MODEL_FORWORD_W_VARIABLE);
			}
		}
	}
	*/

#pragma region ͼ��ӽӲ���
	vector<Mat> images1,images2;
	for (int i = 1;i < argc;i++)
	{
		if (i < argc - 1)
			images1.push_back(imread(argv[i]));
		else
			images2.push_back(imread(argv[i]));
	}
	imagesStitcher composer;
	images2.insert(images2.begin(),composer.stitchImages(images1));	
	composer.showPanorama();
#pragma endregion
	return 0;
}