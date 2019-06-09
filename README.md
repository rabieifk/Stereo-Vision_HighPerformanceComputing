# Stereo-Vision_HighPerformanceComputing

[stereo vision](https://en.wikipedia.org/wiki/Computer_stereo_vision) is the extraction of 3D information from digital images.

The refrence picture is in [link](http://vision.middlebury.edu/stereo/).

This project is the implementation of stereo vision algorithm with SIMD and [Pthread](https://en.wikipedia.org/wiki/POSIX_Threads) and [OpenCv](https://en.wikipedia.org/wiki/OpenCV).

The larger size of the image, the excution time is more in all methods. but this increase fo SIMD is less than others.

With increase in the size of the window, SIMD has the better performance since the numbers of byte which is read an process become more.

The Speedup is 3.54, it means that the execution time of SIMD is 3.54 better than OpenCv.

The result picture can submit in [Middlebury Stereo Evaluation - Version 3](http://vision.middlebury.edu/stereo/submit3/) to calculate bad pixesls.
