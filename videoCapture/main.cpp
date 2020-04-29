#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

string haar_face_datapath = "/home/polya/mine/opencv_for_c++/videoCapture/haarcascade_frontalface_alt_tree.xml";
int main(int argc, char** argv) {
	VideoCapture capture(0); // open camera
	if (!capture.isOpened()) {
		printf("could not open camera...\n");
		return -1;
	}
	Size S = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH), (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));
	int fps = capture.get(CV_CAP_PROP_FPS);

	CascadeClassifier faceDetector;
	faceDetector.load(haar_face_datapath);

	int code = 43;

	Mat frame;
	namedWindow("camera-demo", CV_WINDOW_AUTOSIZE);
	vector<Rect> faces;
	int count = 1;
	while (capture.read(frame)) {
		flip(frame, frame, 1);
		faceDetector.detectMultiScale(frame, faces, 1.1, 1, 0, Size(100, 120), Size(380, 400));
		for (int i = 0; i < faces.size(); i++) {
			if (count % 30 == 0 && count < 301) {
				Mat dst;
				resize(frame(faces[i]), dst, Size(92, 112));
				imwrite(format("/home/polya/mine/opencv_for_c++/EgienFace/orl_faces/s%d/%d.jpg", code ,count/30), dst);
			}
			rectangle(frame, faces[i], Scalar(0, 0, 255), 2, 8, 0);
		}
		imshow("camera-demo", frame);
		char c = waitKey(10);
		if (c == 27 && count > 300 ) {
			break;
		}
		//有时别到人脸，才计数
		if (faces.size()!=0)
		    count++;
	}

	capture.release();

	waitKey(0);



//    // 创建流对象
//    ofstream csv_file;
//    // 打开文件
//    csv_file.open("/home/polya/mine/opencv_for_c++/orl_faces/image.csv", ios::out | ios::app);
//    for(int i = 1; i < 10; i ++){
//        csv_file << "/home/polya/mine/opencv_for_c++/EgienFace/orl_faces/s"<< code <<"/"<< i <<".jpg;" << code << endl;
//    }
//    csv_file.close();

//    //测试数据
//    ofstream test_file;
//    test_file.open("/home/polya/mine/opencv_for_c++/orl_faces/test.csv", ios::out | ios::app);
//    test_file << "/home/polya/mine/opencv_for_c++/EgienFace/orl_faces/s"<< code <<"/10.jpg;"<< code << endl;
//    test_file.close();
    return 0;
}