# Stereo-Vision_HighPerformanceComputing

**Objective:** The comparison between [Pthread](https://en.wikipedia.org/wiki/POSIX_Threads) and [OpenCV](https://en.wikipedia.org/wiki/OpenCV) in implementation of [stereo vision](https://en.wikipedia.org/wiki/Computer_stereo_vision) algorithm

There are many method to calculate the image depth that one of them is Sterio Vision. The refrence picture is in the [link](http://vision.middlebury.edu/stereo/). This project is the implementation of stereo vision algorithm with SIMD and Pthread and OpenCV.

By using the OpenCV library, the tsukuba image has been loaded and the time is claculated. For SIMD the instruction which is used is listed here.

The larger size of the image, the more excution time in all methods, but this increase fo SIMD is less than others.

With increase in the size of the window, SIMD has the better performance since the numbers of bytes which are read increase.

The Speedup is 3.54, it means that the execution time of SIMD is 3.54 better than OpenCV. The result picture can submit in [Middlebury Stereo Evaluation - Version 3](http://vision.middlebury.edu/stereo/submit3/) to calculate bad pixesls.
