#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


void Exercise1()
{
    //Adaptív küszöbölés
    cv::Mat image = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/orai_munka/ora6/build/drift.jpeg", 0); //ha a 0 helyére 1-et írok akkor szinsbe olvassa be
	cv::imshow("Alapkep fekete feheren", image);
	cv::waitKey();

    cv::Mat thresh;
    int blockSize = 5;
    cv::adaptiveThreshold(image, thresh, 255, cv::ADAPTIVE_THRESH_MEAN_C,
    cv::THRESH_BINARY,blockSize,2);
    cv::imshow("Adaptiv kuszoboles", thresh);
    cv::waitKey();

    //dilatáció, erózió

    cv::Mat kernel = cv::Mat::ones(cv::Size(5, 5), CV_8UC1);
    cv::Mat dilated,eroded;

    cv::dilate(image, dilated, kernel);
    cv::erode(image, eroded, kernel);

    cv::imshow("blabla", kernel);
    cv::imshow("blabla2", kernel);

    //BE KELL PÓTOLNI, HAMARABB ELJÖTTÜNK

}


int main()
{
	Exercise1();
	return 0;
}