#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

//tetszőleges képre alkalmazzanak képkorrekciós műveleteket
void Exercise1()
{
    //sima fekete fehérbe beolvasom a képet
	cv::Mat image = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/orai_munka/mintaZH/build/sad_cat2.jpeg", 0); //ha a 0 helyére 1-et írok akkor szinsbe olvassa be
	cv::imshow("Alapkep fekete feheren", image);
	cv::waitKey();

    //élesítés
    cv::Mat blurred, unsharped;
    cv::GaussianBlur(image, blurred, cv::Size(3, 3), 1);
    cv::addWeighted(image, 1.5, blurred, -0.5, 0,unsharped);
	cv::imshow("unsharped", unsharped);
    cv::waitKey();

    //sima globális küszöbölés
    cv::Mat thresh;
    cv::threshold(image, thresh, 200, 255, cv::THRESH_BINARY);
    cv::imshow("Globalis kuszoboles", thresh);
    cv::waitKey();

    //3 szűrő bemutatása
    //Életlenítő szűrők (box,gauss,median)

    //median?? hát inkább homályosabb lett xd
    cv::Mat filtered,equalized;

	cv::medianBlur(image, filtered, 5);
	cv::equalizeHist(filtered, equalized);

	cv::imshow("result", equalized);
	cv::waitKey();

}


int main()
{
	Exercise1();
	return 0;
}