//������ͷ�ļ�
#include "tools.h"
#include "findCircleParameter.h"
#include "corrector.h"
#include "imagesStitcher.h"
#include "viewer.h"

//���̶���ڵ�
int main(int argc, char** argv)
{	
	correctParameters params;
	bool isDispCorrectRet = false;
	corrector adjuster;
	vector<Mat> outputs;

	imagesStitcher stitcher;

	bool saveResult = true;

	//��ͼƬ���ڴ���
	if (tools::readImage())
	{
		vector<Mat>& inputs = tools::GetImages();

			Mat source_image = inputs[0];

			if (findCircleParameter::init(source_image))
			{
				findCircleParameter::findCircle();				 

#pragma region У�������趨��
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

				cout <<endl			
					<< "Correct Image(s) with the same circular region params: " << endl
					<< "radius = " << params.radius << ", center = " << params.center << endl << endl;

#pragma region ͼ��У����
				corrector::correctMethod method = corrector::correctMethod::PERSPECTIVE_LONG_LAT_MAP_CAMERA_LEN_MODEL_REVERSE_W_HALF_PI;

				outputs.push_back(
					adjuster.correctImage(params, method,
						isDispCorrectRet)
					);

				for (int i = 1;i < inputs.size();i++)
				{
					source_image = inputs[i];
					params.imgOrg = source_image;

					outputs.push_back(
						adjuster.correctImage(params, method,isDispCorrectRet)
						);
				}
			}
		}	
#pragma endregion
	cout << endl
		<<"Start Stitch images" << endl;
#pragma region ͼ��ӽӲ���

	if (outputs.size() > 1)
	{
		vector<Mat> images1, images2;
		string filenamePath;
		char suffix[MAX_PATH];
		for (int i = 0;i < outputs.size();i++)
		{
			if (saveResult)
			{
				sprintf_s(suffix, "_corrected%d.jpg", i);
				string tmp(suffix);
				filenamePath = tmp;
				imwrite(filenamePath, outputs[i]);
			}

			if (i < outputs.size() - 1)
				images1.push_back(outputs[i]);
			else
				images2.push_back(outputs[i]);
		}
		Mat tmpRet = stitcher.stitchImages(images1);
		images2.insert(images2.begin(), tmpRet.clone());
		stitcher.stitchImages(images2);
		stitcher.showPanorama();
	}
#pragma endregion
	cout << "Stitch Images completes!" << endl;

#pragma region ���ȫ��ͼ��
	Mat panoramaImage = stitcher.getPanorama();
	if (panoramaImage.empty()) return 0;
	imwrite("panorama.jpg", panoramaImage);
	viewer panoViewer(panoramaImage);
	panoViewer.showWindow();
#pragma endregion
	return 0;
}