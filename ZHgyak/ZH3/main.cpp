#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

void Exercise1()
 {
    //1. Feladat: tetszőleges képre alkalmazzanak képkorrekciós műveleteket
    cv::Mat image = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/ZHgyak/ZH3/build/IMG_2261.jpg", 1);
	cv::imshow("Alapkep", image);
	cv::waitKey();

    cv::Mat szuro, gauss_szuro, gray, hiszto, blurred, unsharped, sharp, filtered;
    int value = 15;
    int sigma_value = 2;
    int sizeofKernel = 55;
    int sigma = 27;

    //ezzel annyira nem éles
    cv::medianBlur(image, szuro, value);
	//cv::imshow("Median szurt kep", szuro);
    //cv::waitKey();

    //szurom
    cv::GaussianBlur(image, gauss_szuro, cv::Size(value, value),sigma_value);
	cv::imshow("Gauss szurt kep", gauss_szuro);
	cv::waitKey();

    //szint állítok
    cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);
    cv::imshow("szurkeve alakitom", gray);
	cv::waitKey();

    //kiegyenlités
    cv::equalizeHist(gray, hiszto);
    cv::imshow("hisztogram kiegyenlites", hiszto);
	cv::waitKey();

    //élesítés
    cv::GaussianBlur(gray, blurred, cv::Size(sizeofKernel, sizeofKernel), sigma);
    cv::addWeighted(gray, 1.5, blurred, -0.5, 0,unsharped);
    cv::imshow("gauss elesites", unsharped);
	cv::waitKey();

	cv::medianBlur(image, filtered, 5);
	cv::addWeighted(image, 2.5, filtered, -1.5, 1, sharp); //fokozza a kép kontrasztját
	cv::imshow("median elesites", sharp);
	cv::waitKey();

}

void Exercise2()
 {
    //2. Feladat: nyissanak meg fekete-fehér módban egy képet, majd futtassanak rá dilatációt és erre jelenítsék meg a kontúrokat is
    cv::Mat image = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/ZHgyak/ZH3/build/IMG_2261.jpg", 0);
	cv::imshow("Alapkep", image);
	cv::waitKey();

    cv::Mat dilated, eroded, contures;
    int sizeofKernel = 47;
    cv::Mat kernel = cv::getStructuringElement(1, cv::Size(sizeofKernel,sizeofKernel));
    cv::dilate(image, dilated, kernel);
    cv::erode(image, eroded, kernel);
    contures = dilated - eroded;

    cv::imshow("dilatacio", dilated);
    cv::waitKey();
    cv::imshow("contures", contures);
    cv::waitKey();
}

void Exercise3()
 {
    //3. Feladat: Mutassák be a háromfajta küszöbölést, amiket az órán tanultunk!
    cv::Mat image = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/ZHgyak/ZH3/build/IMG_2261.jpg", 0);
	cv::imshow("Alapkep", image);
	cv::waitKey();

    cv::Mat thresh, thresh2, thresh3, thresh4;
    int thresh_value = 33;

    //sima globalis -- szinessel is jó
    cv::threshold(image, thresh, thresh_value, 255, cv::THRESH_BINARY);
    cv::imshow("binary", thresh);
    cv::waitKey();
    cv::threshold(image, thresh2, thresh_value, 255, cv::THRESH_BINARY_INV);
    cv::imshow("binary_inv", thresh2);
    cv::waitKey();

    //globalis algoritmussal (Otsu) --- szürkén olvasd be
    cv::threshold(image, thresh3, 0,255,cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::imshow("otsu", thresh3);
    cv::waitKey();

    //adaptiv küszöbölés --- szürkén olvasd be
    int blockSize = 5;
    cv::adaptiveThreshold(image, thresh4, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY,blockSize,2);
    cv::imshow("adaptiv", thresh4);
    cv::waitKey();

}

void Exercise4()
 {

}

void Exercise5()
 {

}

int main() {
	//Exercise1();
	//Exercise2();
    Exercise3();
	return 0;
}