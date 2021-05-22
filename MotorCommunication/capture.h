#ifndef CAPTURE_H
#define CAPTURE_H

#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QThread>
#include <opencv2/opencv.hpp>
#include <librealsense2/rs.hpp>
#include <librealsense2/rsutil.h>

using namespace std;
using namespace cv;

class capture : public QThread
{
    Q_OBJECT
public:
    explicit capture(QObject *parent = nullptr);

    QPixmap pixmap_Color() const
    {
        return Pixmap_Color ;
    }

    void findContour(cv::Mat frame, std::vector<std::vector<cv::Point>> blobs, size_t &numberblob, cv::Mat draw_box,
                     rs2::depth_frame depthframe);

    int StreamOption;
    rs2::pipeline pipe;
    bool camera_running = true;
    bool CreateMaskSingalAlready,MaskSignal = 0;
    QImage BackgroundImage;
    cv::Point MaskTLPoint, MaskBRPoint = cv::Point(0,0);
    size_t numberBlob=0;
    bool findcontour_ready=0;
    bool measure_size = 0;
    double theta;
    float dis;

    void run();

    // If called it will stop the thread
    void stop() { camera_running = false; }

    cv::Mat bgSubtraction;
    std::vector<std::vector<cv::Point> > blobs;
    cv::Mat Mask;


    float x_robot, y_robot, z_robot;


signals:
    void newPixmapCaptured_Color();
    void rectangle();
    void circle();
    void defect_shape();
    void noobject();
    void hexagon();
    void pass();
    void fail();

private:
    QPixmap Pixmap_Color;

    QImage cvMatToQImage(const cv::Mat &inMat);
    QPixmap cvMatToQPixmap(const cv::Mat &inMat);
    cv::Mat QImageToMat(QImage image);
    int cnt;
    double sum;

};

#endif // CAPTURE_H
