#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


void Exercise1()
{
    //sima fekete fehérbe beolvasom a képet
	cv::Mat image = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/orai_munka/ora5/build/CuteCat.png", 0); //ha a 0 helyére 1-et írok akkor szinsbe olvassa be
	cv::imshow("Alapkep fekete feheren", image);
	cv::waitKey();

    //sima globális küszöbölés
    cv::Mat thresh;
    cv::threshold(image, thresh, 200, 255, cv::THRESH_BINARY);
    cv::imshow("Globalis kuszoboles", thresh);
    cv::waitKey();

    //sima globális küszöbölés inverze
    cv::Mat thresh_inv;
    cv::threshold(image, thresh_inv, 180, 255, cv::THRESH_BINARY_INV);
    cv::imshow("Globalis kuszoboles inverze", thresh_inv);
    cv::waitKey();

}

void Exercise2()
{
    //Adaptív küszöbölés
    cv::Mat image = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/orai_munka/ora5/build/2CuteCats.png", 0); //ha a 0 helyére 1-et írok akkor szinsbe olvassa be
	cv::imshow("Alapkep fekete feheren", image);
	cv::waitKey();

    cv::Mat thresh;
    int blockSize = 5;
    cv::adaptiveThreshold(image, thresh, 255, cv::ADAPTIVE_THRESH_MEAN_C,
    cv::THRESH_BINARY,blockSize,2);
    cv::imshow("Adaptiv kuszoboles", thresh);
    cv::waitKey();
}

void Exercise3()
{
    cv::Mat image = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/orai_munka/ora5/build/ZajosKep.png", 0); //ha a 0 helyére 1-et írok akkor szinsbe olvassa be
	cv::imshow("Alapkep fekete feheren", image);
	cv::waitKey();

	cv::Mat filtered,equalized;

	cv::medianBlur(image, filtered, 5);
	cv::equalizeHist(filtered, equalized);
	cv::imshow("equalized", equalized);
	cv::waitKey();

    cv::Mat thresh;
    int blockSize = 5;
    cv::adaptiveThreshold(equalized, thresh, 255, cv::ADAPTIVE_THRESH_MEAN_C,
    cv::THRESH_BINARY,blockSize,2);
    cv::imshow("Adaptiv kuszoboles", thresh);
    cv::waitKey();
    //Ez lehet nem jó, kérdezzük meg Kittit
}



int main()
{
	Exercise1();
    Exercise2();
    Exercise3();
	return 0;
}