# Stereo-Vision_HighPerformanceComputing

**Objective:** The comparison between SIMD, [Pthread](https://en.wikipedia.org/wiki/POSIX_Threads) and [OpenCV](https://en.wikipedia.org/wiki/OpenCV) in implementation of [Stereo Vision](https://en.wikipedia.org/wiki/Computer_stereo_vision) algorithm

There are many method to calculate the image depth that one of them is Sterio Vision. The refrence picture is in the [link](http://vision.middlebury.edu/stereo/). This project is the implementation of stereo vision algorithm with SIMD and Pthread and OpenCV.

By using the OpenCV library, the tsukuba image has been loaded and the time is claculated. For SIMD the instruction which is used is listed [here](https://github.com/rabieifk/Stereo-Vision_HighPerformanceComputing/blob/master/Instructions).

To implement Pthread, the thread should be alocated by the programmer with using some instructions such as pthread_t thread(NUM_THREADS) that is shown [here](https://computing.llnl.gov/tutorials/pthreads/).

The result shows that with a larger image the excuation time of all method would increase but the excution time of SIMD is 3.5x better that the other methods in average. With increasing in the size of the window, SIMD has the better performance since the number of bytes which are read would increase, on the other hand increaaing in the window size would increase the excution time.

The Speedup is 3.54, it means that the execution time of SIMD is 3.54 better than OpenCV. The result picture can submit in [Middlebury Stereo Evaluation - Version 3](http://vision.middlebury.edu/stereo/submit3/) to calculate bad pixesls.
