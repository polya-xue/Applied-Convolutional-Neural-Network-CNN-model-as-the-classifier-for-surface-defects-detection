#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <iostream>

using namespace cv;
using namespace cv::face;
using namespace std;

int main(int argc, char** argv) {
    string filename = string("/home/polya/mine/opencv_for_c++/orl_faces/image.csv");
    ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        printf("could not load file correctly...\n");
        return -1;
    }

    string line, path, classlabel;
    vector<Mat> images;
    vector<int> labels;
    char separator = ';';
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if (!path.empty() && !classlabel.empty()) {
            //printf("path : %s\n", path.c_str());
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }

    if (images.size() < 1 || labels.size() < 1) {
        printf("invalid image path...\n");
        return -1;
    }

    int height = images[0].rows;
    int width = images[0].cols;
    printf("height : %d, width : %d\n", height, width);

    // train it
    Ptr<BasicFaceRecognizer> model = EigenFaceRecognizer::create();
    model->train(images, labels);



    // predict result 输入多个不同人脸，判断训练结果
    string filename_test = string("/home/polya/mine/opencv_for_c++/orl_faces/test.csv");
    ifstream file_test(filename_test.c_str(), ifstream::in);
    if (!file_test) {
        printf("could not load test file correctly...\n");
        return -1;
    }

    string line_test, path_test, classlabel_test;
    vector<Mat> images_test;
    vector<int> labels_test;
    char separator_test = ';';
    while (getline(file_test, line_test)) {
        stringstream liness_test(line_test);
        getline(liness_test, path_test, separator_test);
        getline(liness_test, classlabel_test);
        if (!path_test.empty() && !classlabel_test.empty()) {
            //printf("path : %s\n", path.c_str());
            images_test.push_back(imread(path_test, 0));
            labels_test.push_back(atoi(classlabel_test.c_str()));
        }
    }

    if (images_test.size() < 1 || labels_test.size() < 1) {
        printf("invalid test image path...\n");
        return -1;
    }

    Mat testSample;
    int predictedLabel, num = 0;
    for(int i = 0; i < images_test.size(); i++){
        testSample = images_test[i];
        predictedLabel = model->predict(testSample);
        printf("actual label : %d, predict label :  %d\n", labels_test[i], predictedLabel);
        if(labels_test[i] == predictedLabel)
            num ++;
    }
    printf("accuracy rate: %d/%d\n", num, images_test.size());

//    //显示过程
//    Mat eigenvalues = model->getEigenValues();
//    Mat W = model->getEigenVectors();
//    Mat mean = model->getMean();
//    Mat meanFace = mean.reshape(1, height);
//    Mat dst;
//    if (meanFace.channels() == 1) {
//        normalize(meanFace, dst, 0, 255, NORM_MINMAX, CV_8UC1);
//    } else if (meanFace.channels() == 3) {
//        normalize(meanFace, dst, 0, 255, NORM_MINMAX, CV_8UC3);
//    }
//    imshow("Mean Face", dst);
//
//    // show eigen faces
//    printf("W.cols:%d\n",W.cols);
//    for (int i = 0; i < min(3, W.cols); i++) {
//        Mat ev = W.col(i).clone();
//        Mat grayscale;
//        Mat eigenFace = ev.reshape(1, height);
//        if (eigenFace.channels() == 1) {
//            normalize(eigenFace, grayscale, 0, 255, NORM_MINMAX, CV_8UC1);
//        }
//        else if (eigenFace.channels() == 3) {
//            normalize(eigenFace, grayscale, 0, 255, NORM_MINMAX, CV_8UC3);
//        }
//        Mat colorface;
//        applyColorMap(grayscale, colorface, COLORMAP_JET);
//        char* winTitle = new char[128];
//        sprintf(winTitle, "eigenface_%d", i);
//        imshow(winTitle, colorface);
//    }
//
//    // 重建人脸
//    for (int num = min(10, W.cols); num < min(W.cols, 300); num += 15) {
//        Mat evs = Mat(W, Range::all(), Range(0, num));
//        Mat projection = LDA::subspaceProject(evs, mean, images[0].reshape(1, 1));
//        Mat reconstruction = LDA::subspaceReconstruct(evs, mean, projection);
//
//        Mat result = reconstruction.reshape(1, height);
//        if (result.channels() == 1) {
//            normalize(result, reconstruction, 0, 255, NORM_MINMAX, CV_8UC1);
//        }
//        else if (result.channels() == 3) {
//            normalize(result, reconstruction, 0, 255, NORM_MINMAX, CV_8UC3);
//        }
//        char* winTitle = new char[128];
//        sprintf(winTitle, "recon_face_%d", num);
//        imshow(winTitle, reconstruction);
//    }

    waitKey(0);
    return 0;
}