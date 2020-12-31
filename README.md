# video_reader

ROS package for converting a video to rostopic

## 安装
 - 建立工作空间并拷贝这个库
   ```Shell
   mkdir -p ros_ws/src
   cd ros_ws/src
   git clone https://github.com/shangjie-li/video_reader.git
   cd ..
   catkin_make
   ```

## 参数配置
 - 修改`video_reader/launch/video_reader.launch`
   ```Shell
   <param name="pub_topic" value="/image_raw"/>
   <param name="video_path" value="/your_path_to/video.mp4"/>
   <param name="video_fps" value="30"/>
   ```
    - `pub_topic`指明发布的图像话题。
    - `video_path`指明视频的绝对路径。
    - `video_fps`指明视频的帧率。

## 运行
 - 启动`video_reader`
   ```Shell
   roslaunch video_reader video_reader.launch
   ```

