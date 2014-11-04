#include "panoramaExpansion.h"	

Mat panoramaExpansion(Mat imgOrg, Point center, int radius, double startRadian, CorrectType type)
{
	//�趨չ��ͼ�ĸ߶ȣ���Ϊ����ͼ���ܻҸ��߶���Ϣ������������Ը���ʵ����
	//���е���
	int heightOfPanorama=radius*2;

	//�趨չ��ͼ�Ŀ�ȣ������趨Ϊ����ͼ��Բ����Ч������ܳ�
	int widthOfPanorama=2*PI*radius;


	double dx = 2*PI/widthOfPanorama;
	double dy = radius / (double)heightOfPanorama;

	double p;
	double theta;

	double x, y;

	int u, v;

	//չ��ͼ�ı�������
	Mat retImg(heightOfPanorama,widthOfPanorama, CV_8UC3, Scalar(0, 0, 0));
	Mat_<Vec3b> _retImg = retImg;
	Mat_<Vec3b> _imgOrg = imgOrg.clone();

	switch (type)
	{
	case Reverse:	//ʹ�÷���ӳ�������չ��ͼ
		for (int j = 0; j < heightOfPanorama; j++)
		{
			for (int i = 0; i < widthOfPanorama; i++)
			{
				p = j*dy;
				theta = i*dx + startRadian;

				x = p*cos(theta);
				y = p*sin(theta);

				u = x + center.x;
				v = y + center.y;

				_retImg(j, i)[0] = _imgOrg(v, u)[0];
				_retImg(j, i)[1] = _imgOrg(v, u)[1];
				_retImg(j, i)[2] = _imgOrg(v, u)[2];

			}
		}
		break;

	case Forward:
		int left, top;
		left = center.x - radius;
		top = center.y - radius;
		for (int j = top; j < top + 2 * radius; j++)
		{
			for (int i = left; i < left + 2 * radius; i++)
			{
				if (pow(i - center.x, 2) + pow(j - center.y, 2)>pow(radius, 2))
					continue;

				u = i;
				v = j;

				x = (u - center.x) ;
				y = -(v - center.y);

				//convert to polar axes
				theta = cvFastArctan(y, x)*PI / 180;
				p = sqrt(pow(x, 2) + pow(y, 2));				

				theta -= startRadian;
				theta = theta < 0 ? theta + 2 * PI : theta;

				int u_ret = theta / dx;
				int v_ret = p / dy;	

				if (u_ret<0 || u_ret >= widthOfPanorama || v_ret<0 || v_ret >= heightOfPanorama)
					continue;

				//perform the map from the origin image to the latitude map image
				_retImg(v_ret, u_ret)[0] = _imgOrg(j, i)[0];
				_retImg(v_ret, u_ret)[1] = _imgOrg(j, i)[1];
				_retImg(v_ret, u_ret)[2] = _imgOrg(j, i)[2];
			}
		}

		break;
	}
	
#ifdef _DEBUG_
	namedWindow("expand fish-eye image",CV_WINDOW_AUTOSIZE);
	imshow("expand fish-eye image",retImg);
	waitKey();
#endif
	return	retImg;
}