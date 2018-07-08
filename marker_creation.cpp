#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char const* argv[])
{
	cv::Mat markerImage0;	//ARマーカーを描画するようのフレーム
	cv::Mat markerImage1;	//ARマーカーを描画するようのフレーム
	cv::Mat markerImage2;	//ARマーカーを描画するようのフレーム
	//ARマーカーの辞書6X6_250を開く．6X6のドットで構成される２５０個のidを持つ辞書を指定する
	cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
	cv::aruco::drawMarker(dictionary, 0, 200, markerImage0);	//マーカを200px, id=23のARマーカーを描画
	cv::aruco::drawMarker(dictionary, 1, 200, markerImage1);	//マーカを200px, id=23のARマーカーを描画
	cv::aruco::drawMarker(dictionary, 2, 200, markerImage2);	//マーカを200px, id=23のARマーカーを描画
	cv::imshow("my marker0", markerImage0);	//作成したARマーカーを表示
	cv::imshow("my marker1", markerImage1);	//作成したARマーカーを表示
	cv::imshow("my marker2", markerImage2);	//作成したARマーカーを表示
	cv::waitKey(0);

	return 0;
}
