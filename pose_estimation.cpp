#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

int main(int argc, char const* argv[])
{
	//キャリブレーション情報を読み込む
	cv::FileStorage fs("params.yml", cv::FileStorage::READ);
	if (!fs.isOpened()) {
		std::cout << "File does not opened" << std::endl;
	}

	cv::Mat cameraMatrix, distCoeffs;
	fs["intrinsic"] >> cameraMatrix;
	fs["distortion"] >> distCoeffs;

	
	//ARマーカーの辞書を設定
	cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

	//カメラを起動
	cv::VideoCapture cap(0);
	cv::UMat frame;

	while (true) {
		//カメラから画像を取得
		cap >> frame;
		cv::imshow("src", frame);
		cv::waitKey(1);
		
		//ARマーカーを取得
		std::vector<int> ids;
		std::vector<std::vector<cv::Point2f>> corners;
		cv::aruco::detectMarkers(frame, dictionary, corners, ids);

		if (ids.size() > 0) {
			//検出したARマーカーを描画
			cv::aruco::drawDetectedMarkers(frame, corners, ids);

			//検出したマーカーの位置・姿勢を推定
			std::vector<cv::Vec3d> rvecs, tvecs;
			cv::aruco::estimatePoseSingleMarkers(corners, 0.07, cameraMatrix, distCoeffs, rvecs, tvecs);

			//検出したマーカーの基底を描画
			for (int i = 0; i < ids.size(); i++) {
				cv::aruco::drawAxis(frame, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1);
				for (auto&& point : tvecs){
					std::cout <<  std::sqrt(point[0]*point[0] + point[1]*point[1] + point[2]*point[2]) << std::endl;
				}
				cv::imshow("out", frame);
				cv::waitKey(1);
			}
		}
		else {
			std::cout << "AR marker is not detected" << std::endl;
		}
	}

	return 0;
}
