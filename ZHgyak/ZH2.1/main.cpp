#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

void Exercise1() {
/*
A program a felhasználótól bekéri a szerkesztendő kép teljes elérési útvonalát, majd megnyitja ezt a képfájlt. (1p)
*/
	std::string path;
	std::cout << "Kep eleresi utvonala : ";
    // /Users/halaszkata/git/2023/2.felev/Kepfledolgozas/ZHgyak/ZH2.1/build/IMG_2261.jpg
	std::cin >> path;
	cv::Mat img = cv::imread(path, 1);
	// Ellenőrizzük, hogy a kép mérete nem nagyobb-e az ablak méreténél
	if (img.cols > 800 || img.rows > 600) {
		cv::resize(img, img, cv::Size(800, 600));
	}
	cv::namedWindow("result1", cv::WINDOW_NORMAL);
	cv::resizeWindow("result1", 800, 600);
	cv::imshow("result1", img);
	cv::waitKey();

/*
A program elvégzi a szükséges képkorrekciós műveleteket. (2p)
*/
	//Gaussian elmosás (életlenítő szűrő)
	cv::Mat filtered;
	cv::GaussianBlur(img, filtered, cv::Size(5, 5), 0.5);
	cv::imshow("result2.1", filtered);
	cv::waitKey();

	//Medián elmosás (életlenítő szűrő)
	cv::medianBlur(img, filtered, 3);
	cv::imshow("result2.2", filtered);
	cv::waitKey();

//A program lehetőséget ad a felhasználónak a kép részeinek kimaszkolására, 
//melyet a felhasználó által megadott küszöbérték alapján fog elvégezni. (3p)
	cv::Mat hsv, mask, masked;
	cv::Mat splitted[3], tempmask[3], finalmask, result;
	cv::cvtColor(filtered, hsv, cv::COLOR_RGB2HSV);
	int n = 0;
	std::cout << "Kuszobertek: ";
	std::cin >> n;
	cv::split(hsv, splitted);
	cv::threshold(splitted[0], mask, n, 255, cv::THRESH_BINARY);

	//Készít egy másolatot a mask mátrixról mindhárom csatornánál, 
	// és az eredményt a tempmask tömbben tárolja.
	for (int i = 0; i < 3; ++i)
		tempmask[i] = mask.clone();

	//Az összes csatornát egyesíti a tempmask mátrixokból, 
	//így létrehozva a finalmask mátrixot.
	cv::merge(tempmask, 3, finalmask);
	//A bitwise AND művelettel alkalmazza a finalmask maszkot az eredeti képre (img), 
	//eredményül kapva a masked mátrixot.
	cv::bitwise_and(img, finalmask, masked);

	cv::imshow("mask", mask);
	cv::waitKey();
	cv::imshow("masked", masked);
	cv::waitKey();
	cv::imshow("finalmask", finalmask);
	cv::waitKey();


/*
A program lehetőséget biztosít az adott színcsatorna százalékos kompenzációjára, 
melynek értékeit* a felhasználótól olvassa be. (2p)
*/
	int piros = 0, kek = 0, zold = 0;
	std::cout << "Kek: ";
	std::cin >> kek;
	std::cout << "Zold: ";
	std::cin >> zold;
	std::cout << "Piros: ";
	std::cin >> piros;

	cv::Mat rgb = img.clone();

	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			cv::Vec3b pixelGroup = rgb.at<cv::Vec3b>(i, j);
			pixelGroup[0] = pixelGroup[0] + (1 + kek);
			pixelGroup[1] = pixelGroup[1] + (1 + zold);
			pixelGroup[2] = pixelGroup[2] + (1 + piros);

			rgb.at<cv::Vec3b>(i, j) = pixelGroup;
		}
	}
	std::string savePath;
	std::cout << "Kep eleresi utvonala a menteshez : ";
	std::cin >> savePath;

    // létrehozok egy üreset amibe bele clone-ozom az rgb eredményét
    cv::Mat result2 = rgb.clone();

	std::vector<int> formatParameters_jpg;
	formatParameters_jpg.push_back(cv::IMWRITE_JPEG_QUALITY);
	int out_value = 0;
	std::cout << "Kep minosegi aranya (0-100): ";
	std::cin >> out_value;
	formatParameters_jpg.push_back(out_value);
	cv::imwrite(savePath, result2, formatParameters_jpg);
	cv::imshow("result2", result2);
	cv::waitKey();
}

int main() {
	Exercise1();
	//Exercise2();
	return 0;
}