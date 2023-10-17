#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>

void Feladat1() {
	std::string path;
	std::cout << "Kep eleresi utvonala : "; //IMG_2261.jpg
    //   /Users/halaszkata/git/2023/2.felev/Kepfledolgozas/orai_munka/gyak/build/sad_cat2.jpeg
	std::cin >> path; 
	cv::Mat img = cv::imread(path, 1);

	//cv::imshow("Megnyitas", img);
	//cv::waitKey();

	cv::Mat filtered;
	cv::Mat hsv, mask, masked;
	cv::Mat splitted[3], tempmask[3], finalmask, result;

	cv::GaussianBlur(img, filtered, cv::Size(5, 5), 0.5);
	cv::medianBlur(img, filtered, 3);

	cv::cvtColor(filtered, hsv, cv::COLOR_RGB2HSV);
	unsigned char n = 0;

	std::cout << "Kuszobertek: ";
	std::cin >> n;
	cv::split(hsv, splitted);
	cv::threshold(splitted[0], mask, n, 255, cv::THRESH_BINARY);

	for (int i = 0; i < 3; ++i)
		tempmask[i] = mask.clone();

	cv::merge(tempmask, 3, finalmask);
	cv::bitwise_and(img, finalmask, masked);

	unsigned char piros = 0, kek = 0, zold = 0;
	std::cout << "Kek: ";
	std::cin >> kek;
	std::cout << "Zold: ";
	std::cin >> zold;
	std::cout << "Piros: ";
	std::cin >> piros;

	cv::Mat rgb;

	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			cv::Vec3b pixelGroup = rgb.at<cv::Vec3b>(i, j);
			pixelGroup[0] = pixelGroup[0] + (kek / 100);
			pixelGroup[1] = pixelGroup[1] + (zold / 100);
			pixelGroup[2] = pixelGroup[2] + (kek / 100);

			rgb.at<cv::Vec3b>(i, j) = pixelGroup;
		}
	}

	std::vector<int> formatParameters_jpg;
	formatParameters_jpg.push_back(cv::IMWRITE_JPEG_QUALITY);
	int out_value = 0;
	std::cin >> out_value;
	formatParameters_jpg.push_back(out_value);
	cv::imwrite("out.jpg", result, formatParameters_jpg);

	cv::imshow("img", img);
	cv::imshow("result", result);
	cv::waitKey();
}

void Feladat2() {
	std::cout << "Kep eleresi utvonala : ";
	std::string path;
	std::cin >> path;
	cv::Mat img = cv::imread(path);

	//cv::imshow("img", img);
	//cv::waitKey();

	std::cout << "Adj meg 3 egesz szamot!" << std::endl;
	int a = 0, b = 0, c = 0;
	std::cin >> a >> b >> c;

	cv::Mat mask, hsv, splitted[3];
	cv::cvtColor(img, hsv, cv::COLOR_RGB2HSV);
	cv::split(hsv, splitted);

	cv::Mat masked(hsv.size(), CV_8UC3);
	std::vector<cv::Point> indexes;
	cv::imshow("mask", mask);
	cv::waitKey();
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			
			if (mask.at<uchar>(i, j)) {
				cv::Vec3b pixelgroup = hsv.at<cv::Vec3b>(i, j);
				if ((!(pixelgroup[0] >= -0.25 && pixelgroup[0] <= 0.25) &&
					(pixelgroup[1] <= b) &&
					(pixelgroup[2] > c)
					)) {
					masked.at<cv::Vec3b>(i, j) = pixelgroup;
					indexes.push_back(cv::Point(i, j));
				}

			}
		}
	}

	cv::Mat ures(img.size(), CV_8UC1);

	for (int i = 0; i < indexes.size()/2; ++i) {
		ures.push_back(a);
		ures.push_back(b);
		ures.push_back(c);
	}

	/*for (int i = indexes.size() / 2; i < indexes.size(); ++i) {
		ures.push_back();
	}*/

	for (int i = 0; i < ures.rows; ++i) {
		for (int j = 0; j < ures.cols; ++j) {

			if (mask.at<uchar>(i, j)) {
				cv::Vec3b pixelgroup = hsv.at<cv::Vec3b>(i, j);

				masked.at<cv::Vec3b>(i, j) = pixelgroup;
				//ures.push_back(cv::Point(i, j)/(ures.size());
			}

		}

	}
	//kontur
	cv::Mat dilated, eroded, contures;
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(5, 5));
	cv::dilate(img, dilated, kernel);
	cv::erode(img, eroded, kernel);
	contures = dilated - eroded;

	//img.copyTo(result);

	
	unsigned char hue = 0, sat = 0, value = 0;
	std::cout << "Szinezet: ";
	std::cin >> hue;
	std::cout << "Szintelitettseg: ";
	std::cin >> sat;
	std::cout << "Vilagossag: ";
	std::cin >> value;

	//?
	cv::Mat tempMask[3], finalMask;
	cv::Mat hsv_result;
	cv::merge(tempMask, 3, finalMask);
	cv::bitwise_and(hsv, finalMask, hsv_result);
}

int main() {

	//Feladat1();
	Feladat1();

	return 0;
}