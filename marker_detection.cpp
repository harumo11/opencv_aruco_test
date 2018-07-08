#include <iostream>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>

int main(int argc, char const* argv[])
{
	//カメラを起動
	cv::VideoCapture cap(0);
	
	//ARマーカー6X6_250の辞書を開く
	cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

	while (true) {
		//カメラからフレームに変換
		cv::Mat image, imageCopy;
		cap >> image;
		image.copyTo(imageCopy);

		std::vector<int> ids;	//ARマーカーのidを保存するvector
		std::vector<std::vector<cv::Point2f>> corners;	//ARマーカーの四つ角の座標を保存するvector
		cv::aruco::detectMarkers(image, dictionary, corners, ids);	//ARマーカーを画像から抽出

		if (ids.size() > 0) {	//もし，１つ以上ARマーカーが見つかった場合は，ARマーカーを囲無用に描画する
			cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
		}
		else {	//そうでない場合は，その旨を表示
			std::cout << "||| nothing to be shown!" << std::endl;
		}

		//結果を表示する
		cv::imshow("out", imageCopy);
		if (cv::waitKey(30)>0) {
			std::exit(0);
		}
	}
	return 0;
}
