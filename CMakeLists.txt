cmake_minimum_required(VERSION 3.20)
project(AP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AP
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        MainTrain.cpp
        SimpleAnomalyDetector.cpp
        SimpleAnomalyDetector.h
        AnomalyDetector.h
        timeseries.cpp
        timeseries.h
        minCircle.cpp
        minCircle.h
        HybridAnomalyDetector.cpp
        HybridAnomalyDetector.h)