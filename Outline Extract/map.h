#pragma once
#include "globalInclude.h"

#define FOV		PI	//�����ӳ���
void findPoints(Point2i center, int radius,std::vector<cv::Point> &points, camMode projMode = ORTHOGONAL);