//Képfeldolgozás a gyakorlatban (2020/2021 I.)
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

void Exercise2() {
	/*
	 A program a felhasználótól bekéri a kép teljes elérési útvonalát.
	*/
	std::string path;
	std::cout << "Kep eleresi utvonala : ";
    // /Users/halaszkata/git/2023/2.felev/Kepfledolgozas/ZHgyak/ZH1.2/build/IMG_2261.jpg
	std::cin >> path;
	cv::Mat img = cv::imread(path, 1);
	cv::imshow("res1", img);
	cv::waitKey();

	/*
	A program bekér a felhasználótól egy küszöbértéket, és a küszöbölést* követően első
	lépésként kimaszkolja azokat a részeket a szerkesztendő képről, amelyek az alábbi
	kritériumnak megfelelnek: (4p)
	-Az adott pixelérték színértéke a küszöbérték kétszeresét nem haladja meg,
	-Az adott pixelérték szaturációs értéke a 50 és 170-as sávba,
	-Az adott pixelérték világossági értéke a 100 és 200-as sávba esik.
	Fontos rész, hogy a maszkolás mellett ezeket a pixeleknek az indexeit is tárolja a program
	tetszőlegesen megválasztott adatstruktúrában (tömb, verem, stb.)
	*/
	cv::Mat mask, hsv, splitted[3];
	unsigned char thresholdValue = 0;
	std::cout << "Kerek egy kuszoberteket: ";
	std::cin >> thresholdValue;
	cv::cvtColor(img, hsv, cv::COLOR_RGB2HSV); //RGB-ből HSV-be konvertálás
	cv::split(hsv, splitted); //HSV színtér csatornáit szátválasztja és splitted tömben eltárolja
	cv::threshold(splitted[0], mask, thresholdValue, 255, cv::THRESH_BINARY); //Hue-n elvégzi a küszöbölést, eredményt elmenti a mask-ban
	cv::Mat masked(hsv.size(), CV_8UC3); //Létrehoz egy üres képet (masked) ugyanakkora mérettel, mint a HSV kép.
	std::vector<cv::Point> indexes;
	cv::imshow("mask", mask);
	cv::waitKey();
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			//Végigmegy a képen egy dupla for ciklussal, és ellenőrzi minden pixelre,
			//hogy a mask maszkban nem nulla-e. Ha nem nulla, akkor további ellenőrzéseket végez
			if (mask.at<uchar>(i, j)) {
				cv::Vec3b pixelgroup = hsv.at<cv::Vec3b>(i, j);
				if (pixelgroup[0] <= thresholdValue * 2 &&
					(pixelgroup[1] >= 50 && pixelgroup[1] <= 170) &&
					(pixelgroup[2] >= 100 && pixelgroup[2] <= 200)
					) {
					//Ha minden feltétel teljesül,
					//akkor a pixel értékét a masked képben az eredeti hsv kép értékére állítja.
					masked.at<cv::Vec3b>(i, j) = pixelgroup;
					indexes.push_back(cv::Point(i, j)); //A pixel koordinátáit elmenti a indexes vektorban.
				}

			}
		}
	}
	//std::cout << indexes;
	/*
		A program csak a maszkolt részek felét hagyja meg véletlenszerűen az eredeti képen, a többi
		részt törli az eredeti szerkesztendő képről, majd ezt követően eltünteti a megmaradt apróbb
		hibákat a felhasználó által megadott méret** szerint. (2p)
	*/
	//veletlenszeru torles es morfologia
	cv::Mat structElement = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
	//itt sokfajta megoldas is van a vector bejarasara, ez a fapados verzio
	for (int i = 0; i < indexes.size(); ++i) {
		float n = std::rand() / RAND_MAX;
		//itt a vector adott elemet erjuk el a begin a legelso elem lesz mig az i hogy hanyadik elemnel jarunk
		if (n > 0.5) indexes.erase(indexes.begin() + i);
	}
	cv::Mat mask2(mask.size(), CV_8UC1);
	for (int i = 0; i < indexes.size(); ++i) {
		mask2.at<uchar>(indexes.at(i).x, indexes.at(i).y) = 255;
	}

	cv::Mat opened;
	cv::Mat eroded;
	cv::Mat tempMask[3], finalMask;
	cv::Mat hsv_result;

	cv::erode(mask2, eroded, structElement);
	cv::dilate(eroded, opened, structElement);

	for (int i = 0; i < 3; ++i)
		tempMask[i] = opened.clone();

	cv::merge(tempMask, 3, finalMask);
	cv::bitwise_and(hsv, finalMask, hsv_result);

	cv::imshow("finalMask", finalMask);
	cv::imshow("hsv_result", hsv_result);
	cv::waitKey();

	/*
	A program a törölt képrészeket feltölti a felhasználó által megadott háttérszín értékeivel. (2p)
	*/
	unsigned char hue, sat, val;
	std::cout << "Kérem a színárnyalatot: ";
	std::cin >> hue;
	std::cout << "Kérem a telítettséget: ";
	std::cin >> sat;
	std::cout << "Kérem a világosságot: ";
	std::cin >> val;
	for (int i = 0; i < hsv_result.rows; ++i) {
		for (int j = 0; j < hsv_result.cols; ++j) {
			cv::Vec3b pixelGroup = hsv_result.at<cv::Vec3b>(i, j);
			if (pixelGroup == cv::Vec3b(0, 0, 0))
				pixelGroup = cv::Vec3b(hue, sat, val);
			hsv_result.at<cv::Vec3b>(i, j) = pixelGroup;
		}
	}

	cv::Mat result;
	cv::cvtColor(hsv_result, result, cv::COLOR_HSV2RGB);

	cv::imshow("result", result);
	cv::waitKey();
}

int main() {
	Exercise2();
	return 0;
}