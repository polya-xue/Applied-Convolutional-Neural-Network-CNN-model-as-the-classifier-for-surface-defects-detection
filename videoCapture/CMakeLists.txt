cmake_minimum_required(VERSION 3.3)

project(EgienFace)

add_compile_options(-std=c++11)


# 添加头文件所在目录
include_directories("/usr/local/include/opencv")
include_directories("/usr/local/include/opencv2")


set(src main.cpp)
add_executable(${PROJECT_NAME} ${src})


# tianjia suo xuyao de kuwenjian
target_link_libraries(${PROJECT_NAME}
    /usr/local/lib/libopencv_imgcodecs.so
    /usr/local/lib/libopencv_core.so
    /usr/local/lib/libopencv_features2d.so
    /usr/local/lib/libopencv_flann.so
    /usr/local/lib/libopencv_highgui.so
    /usr/local/lib/libopencv_imgcodecs.so
    /usr/local/lib/libopencv_xfeatures2d.so
    /usr/local/lib/libopencv_xfeatures2d.so.3.4
    /usr/local/lib/libopencv_xfeatures2d.so.3.4.8
    /usr/local/lib/libopencv_imgproc.so.3.4
    /usr/local/lib/libopencv_calib3d.so
    /usr/local/lib/libopencv_calib3d.so.3.4
        /usr/local/lib/libopencv_face.so.3.4.8
        /usr/local/lib/libopencv_video.so.3.4
        /usr/local/lib/libopencv_videoio.so.3.4
        /usr/local/lib/libopencv_highgui.so.3.4
        /usr/local/lib/libopencv_objdetect.so.3.4.8
        )




