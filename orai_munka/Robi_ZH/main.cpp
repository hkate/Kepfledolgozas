#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>

//Bekérem a felhasználótól az elérési útvonalat
void Feladat1_elsopont() {
    std::string path;
	std::cout << "Kep eleresi utvonala : "; //IMG_2261.jpg
    //   /Users/halaszkata/git/2023/2.felev/Kepfledolgozas/orai_munka/Robi_ZH/build/bunny.jpeg
	std::cin >> path;
	cv::Mat img = cv::imread(path, 1);
    cv::imshow("img from path", img);
	cv::waitKey();
}

void Feladat1_masodikpont() {
    cv::Mat image = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/orai_munka/Robi_ZH/build/IMG_2261.jpg", 0); //0 fekete fehér, 1 színes
	cv::imshow("Alapkep", image);
	cv::waitKey();

    cv::Mat output1, output2, output3;
    int value = 15; //always odd, ha ezt az értéket változtatom látszódik különbség
    int sigma_value = 2;
    cv::boxFilter(image, output1, -1, cv::Size(value, value));
    cv::GaussianBlur(image, output2, cv::Size(value, value),sigma_value);
    cv::medianBlur(image, output3, value);

    //szűrők
    //box: hatékonyan simítja a képet, de nem feltétlenül alkalmas az élek, részletek megőrzésére
    //Gauss: zajt csökkent, részleteket elveszítni
    //MEDIAN: kisebb zajokat eltávolítja és az éles éleket megőrzi a kontúrokat

    cv::imshow("box", output1);
	cv::waitKey();

    cv::imshow("gauss", output2);
	cv::waitKey();

    cv::imshow("median", output3);
	cv::waitKey();

    ///////////////////////////////////////////////////////////////
    //hisztogram-kiegyenlítés
    cv::Mat output4;
    cv::equalizeHist(image, output4);

    cv::imshow("hisztogram", output4); //ez csak fekete fehérben működik, ha színesben 1-el olvasom be, nem csinál semmit
    //_src.type() == CV_8UC1 in function 'equalizeHist' = hiba ha színesbe van
	cv::waitKey();

    ///////////////////////////////////////////////////////////////
    //élesítés
    //kernel mérete mindig

    int sizeofKernel = 5;
    cv::Mat blurred, unsharped;
    cv::GaussianBlur(image, blurred, cv::Size(sizeofKernel, sizeofKernel), 1);
    cv::addWeighted(image, 1.5, blurred, -0.5, 0,unsharped);
    cv::imshow("gaussian blurred elesitesenel", blurred);
	cv::waitKey();
    cv::imshow("unsharped elesitesenel", unsharped);
	cv::waitKey();
    //Itt a lényeg, hogy először tetszőleges szűrővel kiszámoljuk az eredeti kép homályosabb
    //verzióját, majd kivonjuk az eredeti képből, ezzel megkapjuk az élesebb változatot. Az
    //összegzés során a súlyok előjelei ellentétesek, és nagyon fontos, hogy az előjeles
    //összegük egyenlő legyen 1-gyel.

    //második ponthoz kellene még a színezés is, de azt most nem csináltuk meg
}

void Feladat1_harmadikpont() {

    //Robi meg a tanár splitelve oldotta meg, lehet hogy úgy kéne idk:(
    cv::Mat image = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/orai_munka/Robi_ZH/build/IMG_2261.jpg", 0); //0 fekete fehér, 1 színes
	cv::imshow("Alapkep", image);
	cv::waitKey();

    unsigned char n = 0;
    cv::Mat thresh;
	std::cout << "Kuszobertek: ";
	std::cin >> n;
    cv::threshold(image, thresh, n, 255, cv::THRESH_BINARY);

    cv::imshow("sima globalis kuszoboles", thresh);
	cv::waitKey();

}

void Feladat1_negyedikpont() {
    cv::Mat image = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/orai_munka/Robi_ZH/build/bunny.jpeg", 0); //0 fekete fehér, 1 színes
	cv::imshow("Alapkep", image);
	cv::waitKey();
}

void Feladat1_ötödikpont() {

    cv::Mat image = cv::imread("/Users/halaszkata/git/2023/2.felev/Kepfledolgozas/orai_munka/Robi_ZH/build/bunny.jpeg", 0); //0 fekete fehér, 1 színes

    //mindig tudod ezt használni mikor le kell külön menteni a képet
    //de ezt úgy használd hogy előtte szerkesztettél már a képen, ne az eredetit mentsd valahova, így magába, külön függvénybe nem jó
    std::vector<int> formatParameters_jpg;
	formatParameters_jpg.push_back(cv::IMWRITE_JPEG_QUALITY);
	int out_value = 0;
	std::cin >> out_value;
	formatParameters_jpg.push_back(out_value);
	cv::imwrite("out.jpg", result, formatParameters_jpg);

	cv::imshow("image", image);
	cv::imshow("result", result);
	cv::waitKey();
}

int main() {

	//Feladat1_elsopont();
    //Feladat1_masodikpont();
    //Feladat1_harmadikpont();
    Feladat1_negyedikpont();

	return 0;
}