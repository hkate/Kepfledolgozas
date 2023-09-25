#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

/*
fekete fehÈr kÈpre tetszıleges sz˚rı alkalmaz·sa, majd hisztogram kiegyenlÌtÈs
*/
void Exercise1()
{
	cv::Mat I = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/tutorial/build/shape.png", 0);
	cv::Mat filtered,equalized;

	cv::medianBlur(I, filtered, 5);
	cv::equalizeHist(filtered, equalized);

	cv::imshow("result", equalized);
	cv::waitKey();
}

/*
kÈp ÈlesÌtÈse sz˚rı segÌtsÈgÈvel
*/
void Exercise2()
{
	cv::Mat I = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/tutorial/build/shape.png", 0);
	cv::Mat filtered, sharp;

	cv::medianBlur(I, filtered, 5);
	cv::addWeighted(I, 2.5, filtered, -1.5, 1, sharp);

	cv::imshow("result",sharp);
	cv::waitKey();
}

/*
szÌnes kÈp hisztogram kiegyenlÌtÈse
*/
void Exercise3()
{
	cv::Mat I = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/tutorial/build/shape.png", 1);
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
	Exercise3();
	return 0;
}