#include "capture.h"
#include <opencv2/opencv.hpp>
#include <QDebug>

capture::capture(QObject *parent) : QThread(parent)
{

}

cv::Mat CreateMask (cv::Point TL, cv::Point BR ,QImage BackgroundImage)
{
    cv::Mat Mask(BackgroundImage.height(),BackgroundImage.width(), CV_8UC3, cv::Scalar(0, 0, 0));
    cv::rectangle(Mask, BR, TL, cv::Scalar(255, 255, 255),-1);
    return Mask;
}

cv::Mat BackgroundSubtraction(cv::Mat Frame, cv::Mat BackgroundMat, cv::Mat Mask, cv::Point TL, cv::Point BR)
{
    cv::Mat FrameGray, BGGray, MaskGray, Subtraction;
    cv::cvtColor(Frame, FrameGray, cv::COLOR_BGR2GRAY );
    cv::cvtColor(BackgroundMat, BGGray, cv::COLOR_BGR2GRAY );
    cv::cvtColor(Mask, MaskGray, cv::COLOR_BGR2GRAY );
    cv::GaussianBlur(FrameGray, FrameGray, cv::Size(5, 5), 0 );
    cv::GaussianBlur(BGGray, BGGray, cv::Size(5, 5), 0 );

    cv::absdiff(FrameGray,BGGray,Subtraction) ;
    Subtraction = Subtraction & MaskGray ;

    int sum,cnt = 0;
    for (int i = TL.x; i < BR.x; i++)
    {
        for (int j = TL.y; j < BR.y; j++)
        {
            if ( ((int)Subtraction.at<uchar>(j,i) <= 255)&& ((int)Subtraction.at<uchar>(j,i) >= 0))
            {cnt++;
            sum += (int)Subtraction.at<uchar>(j,i) ;}
        }
    }
    float threshold = sum/cnt ;
    if (threshold <20)  threshold = 20;
    cv::threshold(Subtraction,Subtraction,threshold,255,0);

    cv::dilate(Subtraction, Subtraction, cv::Mat(),cv::Point(-1,-1) );
    cv::erode(Subtraction, Subtraction, cv::Mat(),cv::Point(-1,-1));

    return Subtraction;

}

void labelBlobs(const cv::Mat gray, std::vector < std::vector<cv::Point> > &blobs)
{

    blobs.clear();

    // Using labels from 2+ for each blob
    cv::Mat label_image;
    cv::Mat binary;

    gray.copyTo(label_image);

    int label_count = 2; // starts at 2 because 0,1 are used already


    for(int y=0; y < gray.rows; y++) {
        for(int x=0; x < gray.cols; x++) {
            if((int)label_image.at<uchar>(y,x) != 255) {

                continue;
            }

            cv::Rect rect;
            cv::floodFill(label_image, cv::Point(x,y), cv::Scalar(label_count), &rect, cv::Scalar(0), cv::Scalar(0), 4);

            std::vector<cv::Point>  blob;

            for(int i=rect.y; i < (rect.y+rect.height); i++) {
                for(int j=rect.x; j < (rect.x+rect.width); j++) {
                    if((int)label_image.at<uchar>(i,j) != label_count) {
                        continue;
                    }

                    blob.push_back(cv::Point(j,i));
                }
            }
            if ((blob.size() > 3000)&&(blob.size() <15000))
                blobs.push_back(blob);

            label_count++;
        }
    }
}

float FindDistance (rs2::depth_frame depth_frame,cv::Point center,float &x,float &y, float &z)
{
    float dis = depth_frame.get_distance(int(center.x),int(center.y));
    float center_pixel[2],center_point[3] ;
    center_pixel[0] = int(center.x); center_pixel[1] = int(center.y);

    rs2_intrinsics intr = depth_frame.get_profile().as<rs2::video_stream_profile>().get_intrinsics();

    rs2_deproject_pixel_to_point(center_point, &intr, center_pixel, dis);
    x = center_point[0] ; y = center_point[1] ; z = center_point[2];
    return dis;
}

void Mearsure_Size (rs2::depth_frame depth_frame,cv::Point2f tltr,cv::Point2f blbr,cv::Point2f tlbl,cv::Point2f trbr,
                     float &width , float &height )
{
    float tltr_pixel[2], blbr_pixel[2], tlbl_pixel[2], trbr_pixel[2];
    tltr_pixel[0] = int(tltr.x); tltr_pixel[1] =  int(tltr.y);
    blbr_pixel[0] = int(blbr.x); blbr_pixel[1] =  int(blbr.y);

    tlbl_pixel[0] = int(tlbl.x) + 1 ; tlbl_pixel[1] =  int(tlbl.y);
    trbr_pixel[0] = int(trbr.x) - 1; trbr_pixel[1] =  int(trbr.y);

    float tltr_point[3],blbr_point[3] ;
    float tlbl_point[3],trbr_point[3] ;

    rs2_intrinsics intr = depth_frame.get_profile().as<rs2::video_stream_profile>().get_intrinsics();
    auto tltr_dis = depth_frame.get_distance(tltr_pixel[0],tltr_pixel[1]);
    auto blbr_dis = depth_frame.get_distance( blbr_pixel[0],blbr_pixel[1]);


    rs2_deproject_pixel_to_point(tltr_point, &intr, tltr_pixel, tltr_dis);
    rs2_deproject_pixel_to_point(blbr_point, &intr, blbr_pixel, blbr_dis);

     width = sqrt(pow(tltr_point[0] - blbr_point[0], 2) +
            pow(tltr_point[1] - blbr_point[1], 2) +
            pow(tltr_point[2] - blbr_point[2], 2));


    auto tlbl_dis = depth_frame.get_distance(tlbl_pixel[0],tlbl_pixel[1]);
    auto trbr_dis = depth_frame.get_distance( trbr_pixel[0],trbr_pixel[1]);


    rs2_deproject_pixel_to_point(tlbl_point, &intr, tlbl_pixel, tlbl_dis);
    rs2_deproject_pixel_to_point(trbr_point, &intr, trbr_pixel, trbr_dis);

    height = sqrt(pow(tlbl_point[0] - trbr_point[0], 2) +
            pow(tlbl_point[1] - trbr_point[1], 2) +
            pow(tlbl_point[2] - trbr_point[2], 2));

}

void transfer(float x_cam, float y_cam, float z_cam, float &x_robot, float &y_robot, float &z_robot)
{
    float T[4][4] =
          {
        {0.03037785743,  0.9995033893,  0.008376186877,  255.5757974},
        {0.9993555291,  -0.0302108997,  -0.01938628351,  -271.3832071},// y+22
        {-0.01912360393,  0.008959702424,  -0.9997769809,  257.2911586},
        {0,  0,  0,  1}
    };
    float B[4][1]=
          {
            {x_cam},
            {y_cam},
            {z_cam},
            {1}
          };
    // Multiply 2 Matrix : C = T*B
          float C[4][1] ;
          int i,j,k;
          for(i=0;i<4;i++)
            for(j=0;j<1;j++)
            {
              C[i][j]=0;
              for(k=0;k<4;k++)
              {
                C[i][j]+=T[i][k]*B[k][j];
              }
            }
    //Object Position in Robot Coordinate
       x_robot = C[0][0];
       y_robot = C[1][0];
       z_robot = C[2][0];
}


void capture::findContour(cv::Mat frame, std::vector<std::vector<cv::Point>> blobs, size_t &numberblob, cv::Mat draw_box,
                          rs2::depth_frame depthframe)
{
    cv::Mat mask(frame.rows,frame.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat graymask;
    cv::cvtColor(mask,graymask,cv::COLOR_BGR2GRAY);
    cv::Mat detected_edges;
    std::vector< std::vector<cv::Point> > contours;
    //std::vector<cv::RotatedRect> minRect( contours.size() );
    cv::RotatedRect minRect;
    cv::Mat boxPoints; //output array of cv::boxPoints
    cv::Mat mean;
    bool findindex_ready =0;
    std::vector<cv::Point> approx;

    if (!blobs.empty())
    {
        if (numberblob >= blobs.size()) {numberblob = 0;}

        for(size_t i=0; i < blobs.at(numberblob).size(); i++)
        {
            graymask.at<uchar>(blobs.at(numberblob).at(i).y,blobs.at(numberblob).at(i).x) = 255 ;
        }
    }

    cv::Canny( graymask, detected_edges, 35, 125 );
    cv::dilate(detected_edges, detected_edges, cv::Mat(),cv::Point(-1,-1) );
    cv::erode(detected_edges, detected_edges, cv::Mat(),cv::Point(-1,-1));
    cv::findContours( detected_edges, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );

    //Find largest countour
    int largest_area=0;
    double largest_contour_index=0;
    for( size_t i = 0; i< contours.size(); i++ ) // iterate through each contour.
        {
            double area = cv::contourArea( contours[i] );  //  Find the area of contour

            if (area > largest_area)
            {
              largest_area = area;
              largest_contour_index = i;
              findindex_ready = 1;
            }
        }
    draw_box = frame;

    if(findindex_ready==1)
    {
        cv::approxPolyDP(contours[largest_contour_index], approx, cv::arcLength(contours[largest_contour_index], true)*0.02, true);
        cv::Point2f cen;
        float radius;
        cv::minEnclosingCircle(contours[largest_contour_index],cen,radius);
       // qDebug()<<radius;

        if(approx.size()==4)
        {
            Q_EMIT rectangle();
        }
        else if(approx.size()>6 && radius>70)
        {
            Q_EMIT hexagon();
        }
        else if(approx.size()>6 && radius<45)
        {
            Q_EMIT circle();
        }
            else
            {
                Q_EMIT defect_shape();
            }
        minRect =cv::minAreaRect(contours[largest_contour_index]);
        cv::boxPoints(minRect,boxPoints); //boxPts: bottom-left,top-left, top-right, bottom-right
        cv::Point2f rect_points[4];
        minRect.points(rect_points);
        for(int i = 0; i <4; i++)
            cv::line(draw_box,rect_points[i],rect_points[(i+1)%4],cv::Scalar(0, 0, 255), 2 ); //draw bounding box

        //calculate mean to find center
        cv::reduce(boxPoints, mean, 0, cv::REDUCE_AVG);
        cv::Point2f center(mean.at<float>(0,0), mean.at<float>(0,1));
        cv::circle(draw_box, center, 3, cv::Scalar(0, 255, 0), -1);

        // After find and draw center and bounding box
        // Calculate Theta
        cv::Point2f tl = cv::Point2f(boxPoints.at<float>(1,0),boxPoints.at<float>(1,1));
        cv::Point2f tr = cv::Point2f(boxPoints.at<float>(2,0),boxPoints.at<float>(2,1));
        cv::Point2f bl = cv::Point2f(boxPoints.at<float>(0,0),boxPoints.at<float>(0,1));
        cv::Point2f A =tl ,B = tl;

        if (((tl.x - tr.x)*(tl.x - tr.x)* + (tl.y - tr.y)*(tl.y - tr.y)) >
                ((tl.x - bl.x)*(tl.x - bl.x)* + (tl.y - bl.y)*(tl.y - bl.y))   )
            B = tr;
        else if (((tl.x - tr.x)*(tl.x - tr.x)* + (tl.y - tr.y)*(tl.y - tr.y)) <
                 ((tl.x - bl.x)*(tl.x - bl.x)* + (tl.y - bl.y)*(tl.y - bl.y))   )
            B = bl;

        if (A != B) theta = std::atan(-(A.y - B.y)/(A.x - B.x))*180/3.14;
        else theta =0;

        //between the top-left and top-right coordinates, followed by
        //the midpoint between bottom-left and bottom-right coordinates
        cv::Point2f tltr =  (cv::Point2f(boxPoints.at<float>(2,0),boxPoints.at<float>(2,1))+
                             cv::Point2f(boxPoints.at<float>(1,0),boxPoints.at<float>(1,1)))*.5;
        cv::Point2f blbr =  (cv::Point2f(boxPoints.at<float>(0,0),boxPoints.at<float>(0,1))+
                             cv::Point2f(boxPoints.at<float>(3,0),boxPoints.at<float>(3,1)))*.5;
        //compute the midpoint between the top-left and bottom-left points,
        //followed by the midpoint between the top-right and bottom-right
        cv::Point2f tlbl =  (cv::Point2f(boxPoints.at<float>(0,0),boxPoints.at<float>(0,1))+
                         cv::Point2f(boxPoints.at<float>(1,0),boxPoints.at<float>(1,1)))*.5;
        cv::Point2f trbr =  (cv::Point2f(boxPoints.at<float>(2,0),boxPoints.at<float>(2,1))+
                         cv::Point2f(boxPoints.at<float>(3,0),boxPoints.at<float>(3,1)))*.5;

        //calculate size
        float width, height;
        Mearsure_Size(depthframe,tltr,blbr,tlbl,trbr,width,height);

        char text_height[200] , text_width[200];
        sprintf(text_height,"%.1f cm",height*100);
        sprintf(text_width,"%.1f cm",width*100);

        //calculate x_cam,y_cam,z_cam,theta,distance
        float x_cam,y_cam,z_cam;
        dis = FindDistance(depthframe,center, x_cam,y_cam,z_cam );
        transfer(x_cam*1000,y_cam*1000,z_cam*1000,x_robot,y_robot,z_robot);
        if(z_robot <-38)
        {
            Q_EMIT pass();
        }
        else
        {
            Q_EMIT fail();
        }

        cv::putText(draw_box, text_height,
            cv::Point2f(tltr.x - 15, tltr.y - 10), cv::FONT_HERSHEY_SIMPLEX,
            0.65, cv::Scalar(255, 255, 255), 2);
        cv::putText(draw_box, text_width,
            cv::Point2f(trbr.x + 10, trbr.y), cv::FONT_HERSHEY_SIMPLEX,
            0.65, cv::Scalar(255, 255, 255), 2);
    }

}



void capture::run()
{
    rs2::config cfg;
    // Start streaming with default recommended configuration
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;
    // Declare RealSense pipeline, encapsulating the actual device and sensors
    rs2::pipeline pipe;
    // Start streaming with default recommended configuration
    pipe.start(cfg);
    rs2::align align_to_color(RS2_STREAM_COLOR);

    while (camera_running)
    {
        rs2::frameset data = pipe.wait_for_frames(); // Wait for next set of frames from the camera
        data = align_to_color.process(data);
        rs2::frame depth = data.get_depth_frame().apply_filter(color_map);
        rs2::frame color = data.get_color_frame();

        //rs2::depth frame
        rs2::depth_frame depthframe = data.get_depth_frame();

        // Query frame size (width and height)
        const int w_depth = depth.as<rs2::video_frame>().get_width();
        const int h_depth = depth.as<rs2::video_frame>().get_height();

        const int w_color = color.as<rs2::video_frame>().get_width();
        const int h_color = color.as<rs2::video_frame>().get_height();

        // Create OpenCV matrix of size (w,h) from the colorized depth data
        cv::Mat depth_frame(cv::Size(w_depth, h_depth), CV_8UC3, (void*)depth.get_data(), cv::Mat::AUTO_STEP);
        cv::Mat color_frame(cv::Size(w_color, h_color), CV_8UC3, (void*)color.get_data(), cv::Mat::AUTO_STEP);

        cv::Mat another_depthframe = cv::Mat (cv::Size(w_depth, h_depth), CV_16UC1, (void*)depthframe.get_data(), cv::Mat::AUTO_STEP);
        another_depthframe.convertTo(another_depthframe, CV_8UC1, 15 / 256.0);

        cv::Mat BackgroundMat = QImageToMat(BackgroundImage);

        if (!BackgroundMat.empty() && MaskSignal==1)
        {
            Mask = CreateMask(MaskTLPoint,MaskBRPoint,BackgroundImage);
            CreateMaskSingalAlready = 1;

        }
        if (!BackgroundMat.empty() && CreateMaskSingalAlready ==1)
        {
            bgSubtraction = BackgroundSubtraction(color_frame,BackgroundMat,Mask,MaskTLPoint,MaskBRPoint);

            labelBlobs(bgSubtraction,blobs);

            if(blobs.size()==0)
            {
                Q_EMIT noobject();
            }

            if(findcontour_ready == 1)
            {
                cv::Mat draw_box;
                findContour(color_frame, blobs, numberBlob, draw_box, depthframe);
            }

        }
        if (!color_frame.empty() && !depth_frame.empty())
        {
            if(StreamOption == 0)
                Pixmap_Color = cvMatToQPixmap(color_frame);
            else
                Pixmap_Color = cvMatToQPixmap(depth_frame);
            Q_EMIT newPixmapCaptured_Color();
        }
     }
}
QPixmap capture:: cvMatToQPixmap( const cv::Mat &inMat )
   {
      return QPixmap::fromImage( cvMatToQImage( inMat ) );
   }

QImage capture:: cvMatToQImage( const cv::Mat &inMat )
   {
      switch ( inMat.type() )
      {
         // 8-bit, 4 channel
         case CV_8UC4:
         {
            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_ARGB32 );

            return image;
         }

         // 8-bit, 3 channel
         case CV_8UC3:
         {
            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_RGB888 );

            return image.rgbSwapped();
         }

         // 8-bit, 1 channel
         case CV_8UC1:
         {
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 2)
            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_Grayscale8 );
#else
            static QVector<QRgb>  sColorTable;

            // only create our color table the first time
            if ( sColorTable.isEmpty() )
            {
               sColorTable.resize( 256 );

               for ( int i = 0; i < 256; ++i )
               {
                  sColorTable[i] = qRgb( i, i, i );
               }
            }

            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_Indexed8 );

            image.setColorTable( sColorTable );
#endif

            return image;
         }

         default:
            qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
      }

      return QImage();
   }

cv::Mat capture::QImageToMat(QImage image)
{
    cv::Mat mat;
    switch (image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
        break;
    /*case QImage::Format_Grayscale8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;*/
    }
    return mat;
}

