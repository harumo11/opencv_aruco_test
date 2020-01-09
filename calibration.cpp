#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char const* argv[])
{
	cv::VideoCapture cap(0);	//カメラを開く
	cv::Mat frame;				//作業用フレーム
	std::vector<cv::Point2f> corners;	//1枚分のチェスボードのコーナー座標
	std::vector<std::vector<cv::Point2f>> imagePoints;//全てのチェスボードのコーナー座標

	//チェスボードのコーナー検出
	while (true) {
		cap >> frame;
		cv::imshow("camera", frame);	//通常のカメラ
		cv::waitKey(10);
		if (cv::findChessboardCorners(frame, cv::Size(10,7), corners)) {
			cv::drawChessboardCorners(frame, cv::Size(10,7), corners, true);
			cv::imshow("chess board", frame);	//チェスボードのコーナーを描画
			//適当なキーを押すとその画像を保存
			if (cv::waitKey(1) > 0) {
				if (imagePoints.size() < 15) {
					imagePoints.push_back(corners);
					std::cout << "coners are saved" << std::endl;
				}
				else {
					std::cout << "saving process is finished" << std::endl;
					break;
				}
			}
		}
		else {
			std::cout << "No corners are found" << std::endl;
		}
	}

	//保存したコーナーの全座標を表示
	int i = 0;
	for (auto&& corner : imagePoints){
		for (auto&& point : corner){
			std::cout << i++ << "\t" << point.x << "\t" << point.y << std::endl;
		}
		std::cout << "------------------------------------------" << std::endl;
		i = 0;
	}


	//コーナーの３次元空間の座標を作成(z=0.0)
	std::vector<std::vector<cv::Point3f>> worldPoints;
	//1毎分のworldPointsを作成する
	std::vector<cv::Point3f> point;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 9; j++) {
			point.push_back(cv::Point3f((j+1)*24, (i+1)*24, 0.0));
		}
	}
	//15毎分のworldPointsを作成する
	for (int i = 0; i < 15; i++) {
		worldPoints.push_back(point);
	}

	//キャリブレーション
	cv::Mat cameraMatrix, distCoeffs;	//カメラ内部行列，係数行列
	std::vector<cv::Mat> rvec, tvec;	//rotation vector, translation vector
	
	double rms = cv::calibrateCamera(worldPoints, imagePoints, frame.size(), cameraMatrix, distCoeffs, rvec, tvec);
	std::cout << cameraMatrix << std::endl;	//カメラ内部行列を確認のため表示
	std::cout << rms << std::endl;	//root mean square誤差を表示


	//保存する
	cv::FileStorage fswrite("params", cv::FileStorage::WRITE);
	if (fswrite.isOpened()) {
		cv::write(fswrite, "intrinsic", cameraMatrix);
		cv::write(fswrite, "distortion", distCoeffs);
	}

	//歪み補正画像を作成
	cv::Mat undistorted;
	cv::undistort(frame, undistorted, cameraMatrix, distCoeffs);
	cv::imshow("src", frame);
	cv::imshow("und", undistorted);
	cv::waitKey(0);
	return 0;
}
