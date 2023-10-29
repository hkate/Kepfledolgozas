#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

void Exercise1()
{
/*
A program a felhasználótól bekéri a szerkesztendő kép teljes elérési útvonalát,
majdmegnyitja ezt a képfájlt. (1p)
*/

	std::string path;
	std::cout << "Kep eleresi utvonala : ";
    // "/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/ZHgyak/ZH1.1/build/IMG_2261.jpg"
	std::cin >> path;
	cv::Mat img = cv::imread(path, 1);
	cv::imshow("result1", img);
	cv::waitKey();


/*
A program elvégzi automatikusan a szükséges képkorrekciós műveleteket. (3p)
*/

//Gaussian elmosás (életlenítő szűrő)
	//cv::Mat I = cv::imread("IMG_2261.jpg", 1);
	cv::Mat filtered;
	cv::GaussianBlur(img, filtered, cv::Size(5, 5), 0.5);
	cv::imshow("result2.1", filtered);
	cv::waitKey();

//Medián elmosás (életlenítő szűrő)
	cv::medianBlur(img, filtered, 3);
	cv::imshow("result2.2", filtered);
	cv::waitKey();

//Box elmosás (életlenítő szűrő)
	int value = 3; //always odd
	cv::boxFilter(img,filtered, -1, cv::Size(value, value));
	cv::imshow("result2.3", filtered);
	cv::waitKey();

//színes kép hisztogram kiegyenlítése
	cv::Mat hsv, splitted[3], equalized[3], merged, result;
	cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV); //konvertálja hsv színtérbe
	cv::split(hsv, splitted); //szétspliteljük 3 részre
	cv::equalizeHist(splitted[2], equalized[2]); //a kép világosságát javítjuk
	//-->Másolja a telítettség és színárnyalat csatornákat a módosított érték csatornára
	splitted[1].copyTo(equalized[1]);
	splitted[0].copyTo(equalized[0]);
	cv::merge(equalized, 3, merged); //összemergeljük a szerkesztett képet
	cv::cvtColor(merged, result, cv::COLOR_HSV2BGR); //visszaállítjuk RGB-re
	cv::imshow("result2.4", result);
	cv::waitKey();

//élesítés --> Gyenge kontrasztú képek esetében alkalmazzuk.
	cv::Mat sharp;
	cv::medianBlur(img, filtered, 5);
	cv::addWeighted(img, 2.5, filtered, -1.5, 1, sharp); //fokozza a kép kontrasztját
	cv::imshow("result2.5", sharp);
	cv::waitKey();

//élesítés --> Gyenge kontrasztú képek esetében alkalmazzuk.
	cv::Mat blurred, unsharped;
	cv::GaussianBlur(img, blurred, cv::Size(5, 5), 1);
	cv::addWeighted(img, 1.5, blurred, -0.5, 0, unsharped);
	cv::imshow("result2.6", sharp);
	cv::waitKey();

/*
• A program a felhasználó által megadott érték alapján küszöbölést hajt végre. (2p)
*/
	int thresh_value;
	std::cout << "Kerem adja meg a kuszoberteket: ";
	std::cin >> thresh_value;
	cv::Mat thresh;
	//Sima globális küszöbölés :
	cv::threshold(img, thresh, thresh_value, 255, cv::THRESH_BINARY);
	cv::threshold(img, thresh, thresh_value, 255, cv::THRESH_BINARY_INV);
	cv::imshow("return2.7-sima", thresh);
	cv::waitKey();

/*
A program lehetőséget biztosít a felhasználó számára a kinyert rész színparamétereinek
(színezet, színtelítettség és világosság) megadására. (4p)
*/
	unsigned char hue = 0, sat = 0, val = 0;
	std::cout << "Kérem a színárnyalatot: ";
	std::cin >> hue;
	std::cout << "Kérem a telítettséget: ";
	std::cin >> sat;
	std::cout << "Kérem a világosságot: ";
	std::cin >> val;
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			cv::Vec3b pixelGroup = hsv.at<cv::Vec3b>(i, j);
			pixelGroup[0] += hue;
			pixelGroup[1] += sat;
			pixelGroup[2] += val;
			hsv.at<cv::Vec3b>(i, j) = pixelGroup;
		}
	}
	cv::cvtColor(hsv, result, cv::COLOR_HSV2RGB);
	std::vector<int> formatParameters_jpg;
	formatParameters_jpg.push_back(cv::IMWRITE_JPEG_QUALITY);
	formatParameters_jpg.push_back(92);
/*
A program eredményként kimenti a felhasználó által megadott elérési útvonalra a
szerkesztett képet JPEG formátumban, 92%-os minőségi arányban. (2p)
*/
	cv::imwrite("out.jpg", result, formatParameters_jpg);
	cv::imshow("img", img);
	cv::imshow("return8", result);
	cv::waitKey();
}


int main()
{
	Exercise1();
	return 0;
}