Face recognition system based on linux system C++ environment
Details: The core idea of EgienFace algorithm is to reduce the dimensionality of image data using PCA algorithm and do the shape similarity calculation after spatial transformation. The face recognition system is based on the EgienFace algorithm, which generates a set of feature vectors for each face in the database, so as to distinguish different faces. At present, the database contains 40 sets of face data, and the process of recognizing faces is fast and the error rate is low.
Specific process.
1、First call the original database and use it as the basis to adjust the new face features.
2、Enable the video_capture program and use the computer's own camera to start capturing. The program will capture different expressions at two-second intervals, normalize the size and store them in the database.
3、Recognize faces: enable recFace_project, the camera is turned on and faces are recognized. The recognition result will be marked on the screen.






