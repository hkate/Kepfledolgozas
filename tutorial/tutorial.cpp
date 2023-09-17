#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

void Exercise1() {
	//beolvassuk a kepet, elso parameter az eleresi utvonal kepnevvel
	//masodik parameter a megnyitasi mod, ami itt szines
	cv::Mat Image = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/tutorial/build/shape.png", 1);
	
	//letrehozunk egy a beolvasott kep meretevel megegyezo ures mat matrixot.
	//a size() metodus visszaadja a matrix meretet
	cv::Mat redChannel(Image.size(), CV_8UC3);

	//csak a priso csatorna ertekeit hagyjuk valtozatlanul, a tobbit kinullazzuk
	for (int i = 0; i < Image.rows; ++i) {
		for (int j = 0; j < Image.cols; ++j) {
			cv::Vec3b currentPixelGroup = Image.at<cv::Vec3b>(i, j);
			currentPixelGroup[0] = 0;
			currentPixelGroup[1] = 0;
			redChannel.at<cv::Vec3b>(i, j) = currentPixelGroup;
		}
	}

	cv::imshow("red",redChannel);
	cv::waitKey();

}

void Exercise2() {
	//beolvassuk a kepet, elso parameter az eleresi utvonal kepnevvel
	//masodik parameter a megnyitasi mod, ami itt szines
	cv::Mat Image = cv::imread("shape.png", 1);
	cv::Mat hsv, result;

	cv::cvtColor(Image, hsv, cv::COLOR_RGB2HSV);


	//az elso csatorna a szinezetet jelenti, ezen is allitunk
	//a masodik csatorna tartalmazza a vilagossagi ertekeket
	for (int i = 0; i < hsv.rows; ++i) {
		for (int j = 0; j < hsv.cols; ++j) {
			cv::Vec3b currentPixelGroup = hsv.at<cv::Vec3b>(i, j);
			
			//itt valasztjuk ki, hogy csak azokat szinezze at, amelyek beleesnek a zold szintartomanyaba
			if ( (currentPixelGroup[0] > 30) &&  (currentPixelGroup[0] <= 60) ) {
				currentPixelGroup[0] += 50;
			}
			
			currentPixelGroup[2] = 240;

			hsv.at<cv::Vec3b>(i, j) = currentPixelGroup;
		}
	}



	cv::cvtColor(hsv, result, cv::COLOR_HSV2RGB);

	cv::imshow("result",result);
	cv::waitKey();
}

int main()
{
	Exercise1();
	Exercise2();
	return 0;
}
