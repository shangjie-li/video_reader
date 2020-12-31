#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <string>

class Videoreader
{
public:
    Videoreader(ros::NodeHandle &nh);
    ~Videoreader();

private:
    void read();

private:
    std::string pub_topic_;
    std::string video_path_;
    float video_fps_;
    
    ros::Publisher pub_image_;
};

Videoreader::Videoreader(ros::NodeHandle &nh)
{
    nh.param<std::string>("pub_topic", pub_topic_, "/image_raw");
    nh.param<std::string>("video_path", video_path_, "");
    nh.param<float>("video_fps", video_fps_, 30);
    
    pub_image_ = nh.advertise<sensor_msgs::Image>(pub_topic_, 1);
    
    read();
}

Videoreader::~Videoreader()
{
}

void Videoreader::read()
{
    cv::namedWindow("reader", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;
    cap.open(video_path_);
    cv::Mat frame;
    sensor_msgs::ImagePtr msg;
    
    int time_interval;
    time_interval = int(1000 / video_fps_);
    
    bool start_reader = false;
    
    for(;;)
    {
        cap >> frame;
        if (frame.empty())
        {
            if (!start_reader) ROS_ERROR("Not found %s", video_path_.c_str());
            break;
        }
        start_reader = true;
        cv::imshow("reader", frame);
        msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
        pub_image_.publish(msg);
        if (cv::waitKey(time_interval) == 27) break;
    }
    cv::destroyWindow("reader");
    ros::shutdown();
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "video_reader");
    ros::NodeHandle nh("~");
    
    Videoreader videoreader(nh);
    return 0;
}
