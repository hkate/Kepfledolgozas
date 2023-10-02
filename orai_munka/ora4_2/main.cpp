#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

void Exercise1()
{
	cv::Mat image = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/ora4_2/build/kep1.png", 0);
    cv::Mat blurred, unsharped;
    cv::GaussianBlur(image, blurred, cv::Size(3, 3), 1);
    cv::addWeighted(image, 1.5, blurred, -0.5, 0,unsharped);
    cv::imshow("unsharped", unsharped);
    cv::waitKey();
}

void Exercise2()
{
	cv::Mat I = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/ora4_2/build/kep1.png", 1);
	cv::Mat hsv,splitted[3], equalized[3],merged,result;

	cv::cvtColor(I, hsv, cv::COLOR_BGR2HSV);

	cv::split(hsv, splitted);
	cv::equalizeHist(splitted[2], equalized[2]);
	splitted[1].copyTo(equalized[1]);
	splitted[0].copyTo(equalized[0]);

	cv::merge(equalized, 3, merged);
	cv::cvtColor(merged, result, cv::COLOR_HSV2BGR);
	cv::imshow("result", result);
	cv::waitKey();
}

int main()
{
	Exercise1();
	Exercise2();
	return 0;
}