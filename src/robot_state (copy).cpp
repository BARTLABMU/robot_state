#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Temperature.h>
#include <tf/transform_broadcaster.h>
bool forward = false;
bool backward = false;
bool right =false;
bool left = false;
bool stop = false;
bool FR = false;
bool FL = false;
bool BR = false;
bool BL = false;
bool joint = false;
bool up45down45 = false;
bool superman = false;
bool cup = false;
bool up45down0 = false;
int J1_angle = 0;
int J2_angle = 0;
int J3_angle = 0;
int J4_angle = 0;
int J5_angle = 0;
int J6_angle = 0;
int FR_angle = -90;
int FL_angle = -90;
int BR_angle = -90;
int BL_angle = -90;
int Max_angle = 180;
int min_angle = -180;
int j1_min = -90;
int j1_max = 90;
int j2_min = 0;
int j2_max = 100;
int j3_min = 0;
int j3_max = 170;
int j4_min = 0;
int j4_max = 20;
int j5_min = -180;
int j5_max = 180;
int j6_min = -180;
int j6_max = 180;
int step_angle = 10;
int step_joint_angle = 1;
double px =0;
double py =0;
double step_move = 0.0001;
double step_rotate = 0.05;
ros::Publisher tele_pub;
std_msgs::String sent;
void joy_callback(const sensor_msgs::JoyConstPtr& joy)
{
    ROS_INFO("joy_callback");

    if(joy->axes[3]==0 && joy->axes[0] == 0 && joy->axes[1]==0&&joy->axes[2] == 0&&joy->axes[4]==0&&joy->axes[5]==1 && joy->buttons[0]==0&& joy->buttons[1]==0&& joy->buttons[2]==0
            &&joy->buttons[3]==0&& joy->buttons[4]==0&&joy->buttons[5]==0&& joy->buttons[6]==0&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        ROS_INFO("Forward");
        forward = true;
        backward = false;
        left = false;
        right = false;
        stop = false;
        FL = false;
        up45down45 = false;
        up45down0 = false;
        superman = false;
        cup = false;
        joint = false;
        sent.data = "forward";
        tele_pub.publish(sent);
    }
    else if(joy->axes[3]==0 && joy->axes[0] == 0 && joy->axes[1]==0&&joy->axes[2] == 0&&joy->axes[4]==0&&joy->axes[5]==-1 && joy->buttons[0]==0&& joy->buttons[1]==0&& joy->buttons[2]==0
            &&joy->buttons[3]==0&& joy->buttons[4]==0&&joy->buttons[5]==0&& joy->buttons[6]==0&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        ROS_INFO("Backward");
        backward=true;
        forward = false;
        left = false;
        right = false;
        stop = false;
        FL = false;
        up45down45 = false;
        up45down0 = false;
        superman = false;
        cup = false;
        joint = false;
        sent.data = "backward";
        tele_pub.publish(sent);

    }
    else if(joy->axes[3]==0 && joy->axes[0] == 0 && joy->axes[1]==0&&joy->axes[2] == 0&&joy->axes[4]==1 && joy->axes[5]==0 && joy->buttons[0]==0&& joy->buttons[1]==0&& joy->buttons[2]==0
            &&joy->buttons[3]==0&& joy->buttons[4]==0&&joy->buttons[5]==0&& joy->buttons[6]==0&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        ROS_INFO("left");
        left=true;
        forward = false;
        backward = false;
        right = false;
        stop = false;
        FL = false;
        up45down45 = false;
        up45down0 = false;
        superman = false;
        cup = false;
        joint = false;
        sent.data = "left";
        tele_pub.publish(sent);
    }
    else if(joy->axes[3]==0 && joy->axes[0] == 0 && joy->axes[1]==0&&joy->axes[2] == 0&&joy->axes[4]==-1 && joy->axes[5]==0 && joy->buttons[0]==0&& joy->buttons[1]==0&& joy->buttons[2]==0
            &&joy->buttons[3]==0&& joy->buttons[4]==0&&joy->buttons[5]==0&& joy->buttons[6]==0&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        ROS_INFO("right");
        right=true;
        left = false;
        forward =false;
        backward=false;
        stop =false;
        FL = false;
        up45down45 = false;
        up45down0 = false;
        superman = false;
        cup = false;
        joint = false;
        sent.data = "right";
        tele_pub.publish(sent);
    }
    else if(joy->axes[3]==0 && joy->axes[0] == 0 && joy->axes[1]==0&&joy->axes[2] == 0&&joy->axes[4]==0 &&joy->axes[5]==0 && joy->buttons[0]==0&& joy->buttons[1]==0&& joy->buttons[2]==0
            &&joy->buttons[3]==0&& joy->buttons[4]==0&&joy->buttons[5]==0&& joy->buttons[6]==0&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        ROS_INFO("stop");
        stop = true;
        right=false;
        left = false;
        forward =false;
        backward=false;
        FL = false;
        up45down45 = false;
        up45down0 = false;
        superman = false;
        cup = false;
        joint = false;
        sent.data = "stop";
        tele_pub.publish(sent);
        sent.data = "stop";
        tele_pub.publish(sent);

    }
    else if(joy->axes[3]!= 0 &&joy->axes[0] == 0 && joy->axes[1] == 0&&joy->axes[2] == 0&&joy->axes[4]==0 && joy->buttons[0]==0&& joy->buttons[1]==0&& joy->buttons[2]==0
            &&joy->buttons[3]==0&& joy->buttons[4]==1&&joy->buttons[5]==0&& joy->buttons[6]==0&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        if(joy->axes[3]== 1)
        {
        ROS_INFO("FL_move up");
        stop = false;
        right=false;
        left = false;
        forward =false;
        backward=false;
        FL = true;
        FR = false;
        BR = false;
        BL =false;
        up45down45 = false;
        up45down0 = false;
        superman = false;
        cup = false;
        joint = false;
            FL_angle = FL_angle +step_angle;
            sent.data = "FLup";
            tele_pub.publish(sent);
        }
        else if(joy->axes[3]==-1)
        {
            ROS_INFO("FL_move down");
            stop = false;
            right=false;
            left = false;
            forward =false;
            backward=false;
            FL = true;
            BR = false;
            BL = false;
            FR = false;
            up45down45 = false;
            up45down0 = false;
            superman = false;
            cup = false;
            joint = false;
        FL_angle = FL_angle -step_angle;
        sent.data = "FLdown";
        tele_pub.publish(sent);
        }
    }
    else if(joy->axes[3]!=0&&joy->axes[0] == 0 && joy->axes[1]==0&&joy->axes[2] == 0&&joy->axes[4]==0 && joy->buttons[0]==0&& joy->buttons[1]==0&& joy->buttons[2]==0
            &&joy->buttons[3]==0&& joy->buttons[4]==0&&joy->buttons[5]==1&& joy->buttons[6]==0&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        if(joy->axes[3] == 1)
        {
        ROS_INFO("FR_move up");
        stop = false;
        right=false;
        left = false;
        forward =false;
        backward=false;
        FL = false;
        FR = true;
        BR = false;
        BL = false;
        up45down45 = false;
        up45down0 = false;
        superman = false;
        cup = false;
        joint = false;
        FR_angle = FR_angle +step_angle;
        sent.data = "FRup";
        tele_pub.publish(sent);
        }
        else if(joy->axes[3]==-1)
        {
            ROS_INFO("FR_move down");
            stop = false;
            right=false;
            left = false;
            forward =false;
            backward=false;
            FR = true;
            FL = false;
            BR = false;
            BL = false;
            up45down45 = false;
            up45down0 = false;
            superman = false;
            cup = false;
            joint = false;
            FR_angle = FR_angle -step_angle;
            sent.data = "FRdown";
            tele_pub.publish(sent);
        }
    }
    else if(joy->axes[3]!=0 &&joy->axes[0] == 0 && joy->axes[1]==0&&joy->axes[2] == 0&&joy->axes[4]==0 && joy->buttons[0]==0&& joy->buttons[1]==0&& joy->buttons[2]==0
            &&joy->buttons[3]==0&& joy->buttons[4]==0&&joy->buttons[5]==0&& joy->buttons[6]==1&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        if(joy->axes[3]==1)
        {
        ROS_INFO("BL_move up");
        stop = false;
        right=false;
        left = false;
        forward =false;
        backward=false;
        FL = false;
        FR = false;
        BL =true;
        BR =false;
        up45down45 = false;
        up45down0 = false;
        superman = false;
        cup = false;
        joint = false;
        BL_angle = BL_angle +step_angle;
        sent.data = "BLup";
        tele_pub.publish(sent);
        }
        else if(joy->axes[3]==-1)
        {
            ROS_INFO("BL_move down");
            stop = false;
            right=false;
            left = false;
            forward =false;
            backward=false;
            FR = false;
            FL = false;
            BL = true;
            BR = false;
            up45down45 = false;
            up45down0 = false;
            superman = false;
            cup = false;
            joint = false;
            BL_angle = BL_angle -step_angle;
            sent.data = "BLdown";
            tele_pub.publish(sent);
        }
    }
    else if( joy->axes[3]!=0&&joy->axes[0] == 0 && joy->axes[1]==0&&joy->axes[2] == 0&&joy->axes[4]==0 && joy->buttons[0]==0&& joy->buttons[1]==0&& joy->buttons[2]==0
            &&joy->buttons[3]==0&& joy->buttons[4]==0&&joy->buttons[5]==0&& joy->buttons[6]==0&& joy->buttons[7]==1&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        if(joy->axes[3] ==1)
        {
        ROS_INFO("BR_move up");
        stop = false;
        right=false;
        left = false;
        forward =false;
        backward=false;
        FL = false;
        FR = false;
        BL =false;
        BR = true;
        up45down45 = false;
        up45down0 = false;
        superman = false;
        cup = false;
        joint = false;
        BR_angle = BR_angle +step_angle;
        sent.data = "BRup";
        tele_pub.publish(sent);
        }
        else if(joy->axes[3]==-1)
        {
            ROS_INFO("BR_move down");
            stop = false;
            right=false;
            left = false;
            forward =false;
            backward=false;
            FR = false;
            FL = false;
            BR = true;
            BL = false;
            up45down45 = false;
            up45down0 = false;
            superman = false;
            cup = false;
            joint = false;
            BR_angle = BR_angle -step_angle;
            sent.data = "BRdown";
            tele_pub.publish(sent);
        }
    }
    else if( joy->axes[3]!=0&&joy->axes[0] == 0 && joy->axes[1]==0&&joy->axes[2] == 0&&joy->axes[4]==0 && joy->buttons[0]==0&& joy->buttons[1]==0&& joy->buttons[2]==0
            &&joy->buttons[3]==0&& joy->buttons[4]==1&&joy->buttons[5]==1&& joy->buttons[6]==0&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        if(joy->axes[3] ==1)
        {
            ROS_INFO("FL_FR move up");
            stop = false;
            right=false;
            left = false;
            forward =false;
            backward=false;
            FL = true;
            FR = true;
            BR = false;
            BL =false;
            up45down45 = false;
            up45down0 = false;
            superman = false;
            cup = false;
            joint = false;
            FL_angle = FL_angle +step_angle;
            FR_angle = FR_angle +step_angle;
            sent.data = "FLup";
            tele_pub.publish(sent);
            sent.data = "FRup";
            tele_pub.publish(sent);
        }
        else if(joy->axes[3]==-1)
        {
            ROS_INFO("FL_FR move up");
            stop = false;
            right=false;
            left = false;
            forward =false;
            backward=false;
            FL = true;
            FR = true;
            BR = false;
            BL =false;
            up45down45 = false;
            up45down0 = false;
            superman = false;
            cup = false;
            joint = false;
            FL_angle = FL_angle-step_angle;
             FR_angle = FR_angle -step_angle;
             sent.data = "FLdown";
             tele_pub.publish(sent);
             sent.data = "FRdown";
             tele_pub.publish(sent);
        }
    }
    else if(joy->axes[3]!=0&&joy->axes[0] == 0 && joy->axes[1]==0&&joy->axes[2] == 0&&joy->axes[4]==0 && joy->buttons[0]==0&& joy->buttons[1]==0&& joy->buttons[2]==0
            &&joy->buttons[3]==0&& joy->buttons[4]==0&&joy->buttons[5]==0&& joy->buttons[6]==1&& joy->buttons[7]==1&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        if(joy->axes[3] == 1)
        {
            ROS_INFO("BL_BR move up");
            stop = false;
            right=false;
            left = false;
            forward =false;
            backward=false;
            FL = false;
            FR = false;
            BR = true;
            BL =true;
            up45down45 = false;
            up45down0 = false;
            superman = false;
            cup = false;
            joint = false;
            BL_angle = BL_angle +step_angle;
            BR_angle = BR_angle +step_angle;
            sent.data = "BLup";
            tele_pub.publish(sent);
            sent.data = "BRup";
            tele_pub.publish(sent);
        }
        else if(joy->axes[3]==-1)
        {
            ROS_INFO("BL_BR move down");
            stop = false;
            right=false;
            left = false;
            forward =false;
            backward=false;
            FL = false;
            FR = false;
            BR = true;
            BL =true;
            up45down45 = false;
            up45down0 = false;
            superman = false;
            cup = false;
            joint = false;
            BL_angle = BL_angle-step_angle;
             BR_angle = BR_angle -step_angle;
             sent.data = "BLdown";
             tele_pub.publish(sent);
             sent.data = "BRdown";
             tele_pub.publish(sent);
        }
    }
    else if( joy->axes[3]!=0&&joy->axes[0] == 0 && joy->axes[1]==0&&joy->axes[2] == 0&&joy->axes[4]==0 && joy->buttons[0]==0&& joy->buttons[1]==0&& joy->buttons[2]==0
            &&joy->buttons[3]==0&& joy->buttons[4]==1&&joy->buttons[5]==1&& joy->buttons[6]==1&& joy->buttons[7]==1&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        if(joy->axes[3] ==1)
        {
            ROS_INFO("all move up");
            stop = false;
            right=false;
            left = false;
            forward =false;
            backward=false;
            FL = true;
            FR = true;
            BR = true;
            BL =true;
            up45down45 = false;
            up45down0 = false;
            superman = false;
            cup = false;
            joint = false;
            BL_angle = BL_angle +step_angle;
            BR_angle = BR_angle +step_angle;

            FL_angle = FL_angle+step_angle;
             FR_angle = FR_angle +step_angle;

             sent.data = "FLup";
             tele_pub.publish(sent);
             ros::Duration(0.02).sleep();
             sent.data = "FRup";
             tele_pub.publish(sent);
             ros::Duration(0.02).sleep();
             sent.data = "BLup";
             tele_pub.publish(sent);
             ros::Duration(0.02).sleep();
             sent.data = "BRup";
             tele_pub.publish(sent);
        }
        else if(joy->axes[3]==-1)
        {
            ROS_INFO("all move up");
            stop = false;
            right=false;
            left = false;
            forward =false;
            backward=false;
            FL = true;
            FR = true;
            BR = true;
            BL =true;
            up45down45 = false;
            up45down0 = false;
            superman = false;
            cup = false;
            joint = false;
            BL_angle = BL_angle-step_angle;
             BR_angle = BR_angle -step_angle;

             FL_angle = FL_angle-step_angle;
              FR_angle = FR_angle -step_angle;
              sent.data = "FLdown";
              tele_pub.publish(sent);
              ros::Duration(0.02).sleep();
              sent.data = "FRdown";
              tele_pub.publish(sent);
              ros::Duration(0.02).sleep();
              sent.data = "BLdown";
              tele_pub.publish(sent);
              ros::Duration(0.02).sleep();
              sent.data = "BRdown";
              tele_pub.publish(sent);
        }
    }
    else if( joy->axes[3]==0&& (joy->axes[0] != 0 || joy->axes[1]!=0 )&&joy->axes[2] == 0&&joy->axes[4]==0 &&
             joy->buttons[0]==0&& (joy->buttons[1]==1|| joy->buttons[2]==1 ||joy->buttons[3]==1)&& joy->buttons[4]==0&&joy->buttons[5]==0&& joy->buttons[6]==0&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {

        stop = false;
        right=false;
        left = false;
        forward =false;
        backward=false;
        FL = false;
        FR = false;
        BR = false;
        BL =false;
        joint = true;
        up45down45 = false;
        up45down0 = false;
        superman = false;
        cup = false;

        if(joy->axes[0]>0 && joy->buttons[1]==1)
        {
            // j1 rotate left
            J1_angle = J1_angle + step_joint_angle;

        }
        else if(joy->axes[0]<0 && joy->buttons[1]==1)
        {
               // j1 rotate right
           J1_angle = J1_angle - step_joint_angle;
        }
        else if(joy->axes[1]>0 && joy->buttons[1]==1)
        {
            // j2 rotate left
            J2_angle = J2_angle + step_joint_angle;

        }
        else if(joy->axes[1]<0 && joy->buttons[1]==1)
        {
               // j2 rotate right
           J2_angle = J2_angle - step_joint_angle;
        }
        else if(joy->axes[1]>0 && joy->buttons[2]==1)
        {
            // j3 rotate left
            J3_angle = J3_angle + step_joint_angle;

        }
        else if(joy->axes[1]<0 && joy->buttons[2]==1)
        {
               // j2 rotate right
           J3_angle = J3_angle - step_joint_angle;
        }
        else if(joy->axes[0]>0 && joy->buttons[2]==1)
        {
            // j2 rotate left
            J4_angle = J4_angle + step_joint_angle;

        }
        else if(joy->axes[0]<0 && joy->buttons[2]==1)
        {
               // j4 rotate right
           J4_angle = J4_angle - step_joint_angle;
        }
        else if(joy->axes[0]>0 && joy->buttons[3]==1)
        {
            // j5 rotate left
            J5_angle = J5_angle + step_joint_angle;

        }
        else if(joy->axes[0]<0 && joy->buttons[3]==1)
        {
               // j5 rotate right
           J5_angle = J5_angle - step_joint_angle;
        }
        else if(joy->axes[1]>0 && joy->buttons[3]==1)
        {
            // j6 rotate left
            J6_angle = J6_angle + step_joint_angle;

        }
        else if(joy->axes[1]<0 && joy->buttons[3]==1)
        {
               // j5 rotate right
           J6_angle = J6_angle - step_joint_angle;
        }

    }
    else if( joy->axes[3]==0&& joy->axes[0] == 0 && joy->axes[1]==0 &&joy->axes[2] == 0&&joy->axes[4]==0 &&
             joy->buttons[0]==1&& joy->buttons[1]==0&& joy->buttons[2]==0 && joy->buttons[3]==0 && joy->buttons[4]==1&&joy->buttons[5]==0&& joy->buttons[6]==0&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        stop = false;
        right=false;
        left = false;
        forward =false;
        backward=false;
        FL = false;
        FR = false;
        BR = false;
        BL =false;
        joint = false;
        up45down45 = true;
        up45down0 = false;
        superman = false;
        cup = false;

               //  \-\   up 45 down 45
                FL_angle = -45;
                FR_angle = -45;
                BL_angle = -45;
                BR_angle = -45;
                sent.data = "up45down45";
                tele_pub.publish(sent);

    }
    else if( joy->axes[3]==0&& joy->axes[0] == 0 && joy->axes[1]==0 &&joy->axes[2] == 0&&joy->axes[4]==0 &&
             joy->buttons[0]==0&& joy->buttons[1]==1&& joy->buttons[2]==0 && joy->buttons[3]==0 && joy->buttons[4]==1&&joy->buttons[5]==0&& joy->buttons[6]==0&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        stop = false;
        right=false;
        left = false;
        forward =false;
        backward=false;
        FL = false;
        FR = false;
        BR = false;
        BL =false;
        joint = false;
        up45down45 = false;
        up45down0 = false;
        superman = true;
        cup = false;
               //  -- - --  superman
                FL_angle = 0;
                FR_angle = 0;
                BL_angle = 0;
                BR_angle = 0;
                sent.data = "superman";
                tele_pub.publish(sent);

    }
    else if( joy->axes[3]==0&& joy->axes[0] == 0 && joy->axes[1]==0 &&joy->axes[2] == 0&&joy->axes[4]==0 &&
             joy->buttons[0]==0&& joy->buttons[1]==0&& joy->buttons[2]==1 && joy->buttons[3]==0 && joy->buttons[4]==1&&joy->buttons[5]==0&& joy->buttons[6]==0&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {

        stop = false;
        right=false;
        left = false;
        forward =false;
        backward=false;
        FL = false;
        FR = false;
        BR = false;
        BL =false;
        joint = false;
        up45down45 = false;
        up45down0 = false;
        superman = false;
        cup = true;
        //  \___/   cup
                FL_angle = -45;
                FR_angle = -45;
                BL_angle = 45;
                BR_angle = 45;
                sent.data = "cup";
                tele_pub.publish(sent);

    }
    else if( joy->axes[3]==0&& joy->axes[0] == 0 && joy->axes[1]==0 &&joy->axes[2] == 0&&joy->axes[4]==0 &&
             joy->buttons[0]==0&& joy->buttons[1]==0&& joy->buttons[2]==0 && joy->buttons[3]==1 && joy->buttons[4]==1&&joy->buttons[5]==0&& joy->buttons[6]==0&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
               //  \____ _   up 45 down 0

        stop = false;
        right=false;
        left = false;
        forward =false;
        backward=false;
        FL = false;
        FR = false;
        BR = false;
        BL =false;
        joint = false;
        up45down45 = false;
        up45down0 = true;
        superman = false;
        cup = false;
        FL_angle = -45;
                FR_angle = -45;
                BL_angle = 0;
                BR_angle = 0;
                sent.data = "up45down0";
                tele_pub.publish(sent);

    }
    else if( joy->axes[3]==0&& joy->axes[0] == 0 && joy->axes[1]==0 &&joy->axes[2] == 0&&joy->axes[4]==0 &&
             joy->buttons[0]==0&& joy->buttons[1]==1&& joy->buttons[2]==0 && joy->buttons[3]==0 && joy->buttons[4]==0&&joy->buttons[5]==1&& joy->buttons[6]==0&& joy->buttons[7]==0&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        //Manipulator reset
        stop = false;
        right=false;
        left = false;
        forward =false;
        backward=false;
        FL = false;
        FR = false;
        BR = false;
        BL =false;
        joint = true;
        up45down45 = false;
        up45down0 = false;
        superman = false;
        cup = false;


        J1_angle = 0;
        J2_angle = j2_min;
        J3_angle = j3_min;
        J4_angle = j4_min;
        J5_angle = 0;
        J6_angle = 0;

    }
    else if( joy->axes[3]==0&& joy->axes[0] == 0 && joy->axes[1]==0 &&joy->axes[2] == 0&&joy->axes[4]==0 &&
             joy->buttons[0]==0&& joy->buttons[1]==1&& joy->buttons[2]==0 && joy->buttons[3]==0 && joy->buttons[4]==1&&joy->buttons[5]==1&& joy->buttons[6]==1&& joy->buttons[7]==1&& joy->buttons[8]==0&& joy->buttons[9]==0)
    {
        // leg reset

        stop = false;
        right=false;
        left = false;
        forward =false;
        backward=false;
        FL = true;
        FR = true;
        BR = true;
        BL =true;
        joint = false;
        up45down45 = false;
        up45down0 = false;
        superman = false;
        cup = false;

        FL_angle = -90;
        FR_angle = -90;
        BL_angle = 90;
        BR_angle = 90;

    }


}
int main(int argc, char** argv)

{
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 100);
    tele_pub = n.advertise<std_msgs::String>("teleop_control",100);
    ros::Subscriber joy_sub = n.subscribe("joy",10,joy_callback);
    tf::TransformBroadcaster broadcaster;
  // ros::Rate loop_rate(30);

    const double degree = M_PI/180;

    // robot state
    double FR_ro = 0, FL_ro = 0 , BR_ro=0, BL_ro=0, j1_ro=0,j2_ro=0,j3_ro=0,j4_ro=0,j5_ro=0,j6_ro=0;

    // message declarations
    geometry_msgs::TransformStamped odom_top, odom_fix, odom_FL, odom_FR, odom_BL, odom_BR,odom_j1, odom_j2, odom_j3, odom_j4, odom_j5, odom_j6, odom_base;
    sensor_msgs::JointState joint_state;


    odom_base.header.frame_id = "map";
    odom_base.child_frame_id = "base_link";

    odom_FL.header.frame_id = "base_link";
    odom_FL.child_frame_id = "LFrontLeg_link";
    odom_FR.header.frame_id = "base_link";
    odom_FR.child_frame_id = "RFrontLeg_link";
    odom_BL.header.frame_id = "base_link";
    odom_BL.child_frame_id = "LBackLeg_link";
    odom_BR.header.frame_id = "base_link";
    odom_BR.child_frame_id = "RBackLeg_link";

    odom_top.header.frame_id = "base_link";
    odom_top.child_frame_id = "top_link";

    odom_j1.header.frame_id = "base_link";
    odom_j1.child_frame_id = "mani0_link";
    odom_j2.header.frame_id = "mani0_link";
    odom_j2.child_frame_id = "mani1_link";
    odom_j3.header.frame_id = "mani1_link";
    odom_j3.child_frame_id = "mani2_link";
    odom_fix.header.frame_id ="mani2_link";
    odom_fix.child_frame_id = "mani3_link";
    odom_j4.header.frame_id = "mani3_link";
    odom_j4.child_frame_id = "mani4_link";
    odom_j5.header.frame_id = "mani4_link";
    odom_j5.child_frame_id = "mani5_link";
    odom_j6.header.frame_id = "mani5_link";
    odom_j6.child_frame_id = "endeffector_link";
 ros::Rate loop_rate(100);

    while (ros::ok()) {
        //update joint_state
        if(forward == true)
        {
            px=px+step_move;
            //sent.data = "forward";
           // tele_pub.publish(sent);
           // ROS_INFO("sent Forward");
        }
        else if(backward == true)
        {
            //ROS_INFO("sent backward");
            //sent.data = "backward";
            //tele_pub.publish(sent);
            //px = px-step_move;
        }
        else if(left == true)
        {
            py= py+step_move;
            //sent.data = "left";
            //tele_pub.publish(sent);
            //ROS_INFO("sent left");
        }
        else if(right == true)
        {
            py = py-step_move;
            //sent.data = "right";
            //tele_pub.publish(sent);
            //ROS_INFO("sent right");
        }
        else if(stop == true)
        {
            //ROS_INFO("sent stop");

        }
        else if(FL == true && FR == false && BL == false && BR==false)
        {
            if(FL_angle > Max_angle)
            {
            FL_angle = Max_angle;

            }
            else if(FL_angle<min_angle)
            {
                 FL_angle = min_angle;

            }

 ROS_INFO("FL move: %d",FL_angle);

        }
        else if(FL == false && FR == true && BL == false && BR==false)
        {
            if(FR_angle > Max_angle)
            {
            FR_angle = Max_angle;

            }
            else if(FR_angle<min_angle)
            {
                 FR_angle = min_angle;

            }
            ROS_INFO("FR move: %d",FR_angle);


        }
        else if(FL == false && FR == false && BL == true && BR==false)
        {
            if(BL_angle > Max_angle)
            {
            BL_angle = Max_angle;

            }
            else if(BL_angle<min_angle)
            {
                 BL_angle = min_angle;

            }
            ROS_INFO("BL move: %d",BL_angle);

        }
        else if(FL == false && FR == false && BL == false && BR==true)
        {
            if(BR_angle > Max_angle)
            {
            BR_angle = Max_angle;

            }
            else if(BR_angle<min_angle)
            {
                 BR_angle = min_angle;

            }
            ROS_INFO("BR move: %d",BR_angle);

        }
        else if(FL == true && FR == true&&BL == false && BR==false)
        {
            if(FL_angle > Max_angle)
            {
            FL_angle = Max_angle;

            }
            else if(FL_angle<min_angle)
            {
                 FL_angle = min_angle;

            }
            else if(FR_angle >Max_angle)
            {
                FR_angle = Max_angle;
            }
            else if(FR_angle<min_angle)
            {
                FR_angle = min_angle;
            }

            ROS_INFO("FL FR MOVE : %d : %d",FL_angle,FR_angle);
        }
        else if(BL == true && BR == true&&FL == false && FR == false)
        {

            if(BL_angle > Max_angle)
            {
            BL_angle = Max_angle;

            }
            else if(BL_angle<min_angle)
            {
                 BL_angle = min_angle;

            }
            else if(BR_angle >Max_angle)
            {
                BR_angle = Max_angle;
            }
            else if(BR_angle<min_angle)
            {
                BR_angle = min_angle;
            }

            ROS_INFO("BL BR MOVE : %d : %d",BL_angle,BR_angle);
        }
        else if(FL == true && FR == true && BL == true && BR == true )
        {

            if(FL_angle > Max_angle)
            {
            FL_angle = Max_angle;

            }
            else if(FL_angle<min_angle)
            {
                 FL_angle = min_angle;

            }
            else if(FR_angle >Max_angle)
            {
                FR_angle = Max_angle;
            }
            else if(FR_angle<min_angle)
            {
                FR_angle = min_angle;
            }
            else if(BL_angle > Max_angle)
            {
            BL_angle = Max_angle;

            }
            else if(BL_angle<min_angle)
            {
                 BL_angle = min_angle;

            }
            else if(BR_angle >Max_angle)
            {
                BR_angle = Max_angle;
            }
            else if(BR_angle<min_angle)
            {
                BR_angle = min_angle;
            }
            ROS_INFO("FL FR BL BR MOVE : %d : %d: %d : %d",FL_angle,FR_angle,BL_angle,BR_angle);
        }
        else if(FL == false && FR == false && BL == false && BR == false && forward == false && backward == false && right == false && left == false && stop == false && joint == true )
        {
            if(J1_angle > j1_max)
            {
            J1_angle = j1_max;

            }
            else if(J1_angle< j1_min)
            {
                      J1_angle = j1_min;

            }

            if(J2_angle > j2_max)
            {
            J2_angle = j2_max;

            }
            else if(J2_angle< j2_min)
            {
                      J2_angle = j2_min;

            }

            if(J3_angle > j3_max)
            {
            J3_angle = j3_max;

            }
            else if(J3_angle< j3_min)
            {
                      J3_angle = j3_min;

            }

            if(J4_angle > j4_max)
            {
            J4_angle = j4_max;

            }
            else if(J4_angle< j4_min)
            {
                      J4_angle = j4_min;

            }

            if(J5_angle< j5_min)
            {
                      J5_angle = j5_min;

            }
            else if(J5_angle< j5_min)
            {
                      J5_angle = j5_min;

            }

            if(J6_angle > j6_max)
            {
            J6_angle = j6_max;

            }
            else if(J6_angle< j6_min)
            {
                      J6_angle = j6_min;

            }

            ROS_INFO("%d : %d : %d : %d : %d : %d",J1_angle,J2_angle,J3_angle,J4_angle,J5_angle,J6_angle);
        }
        else if(up45down45 == true)
        {

        }
        else if(up45down0 == true)
        {

        }
        else if(superman == true)
        {

        }
        else if(cup =true)
        {

        }
        FL_ro = (FL_angle)*degree;
        FR_ro = (FR_angle)*degree;
        BL_ro = (-BL_angle)*degree;
        BR_ro = (-BR_angle)*degree;
        j1_ro = (J1_angle)*degree;
        j2_ro = (J2_angle)*degree;
        j3_ro = (-J3_angle)*degree;
       // j4_ro = (J4_angle-180)*degree;
        j4_ro = J4_angle*0.01;
        j5_ro = (J5_angle-180)*degree;
        j6_ro = (J6_angle-180)*degree;
        joint_state.header.stamp = ros::Time::now();
        joint_state.name.resize(10);
        joint_state.position.resize(10);
        joint_state.name[0] ="LFrontLeg_link";
        joint_state.position[0] = FL_ro;
        joint_state.name[1] ="LBackLeg_link";
        joint_state.position[1] = BL_ro;
        joint_state.name[2] ="RFrontLeg_link";
        joint_state.position[2] = FR_ro;
        joint_state.name[3] ="RBackLeg_link";
        joint_state.position[3] = BR_ro;
        joint_state.name[4] ="mani0_link";
        joint_state.position[4] = j1_ro;
        joint_state.name[5] ="mani1_link";
        joint_state.position[5] = j2_ro;
        joint_state.name[6] ="mani2_link";
        joint_state.position[6] = j3_ro;
        joint_state.name[7] ="mani4_link";
        joint_state.position[7] = j4_ro;
        joint_state.name[8] ="mani5_link";
        joint_state.position[8] = j5_ro;
        joint_state.name[9] ="endeffector_link";
        joint_state.position[9] = j6_ro;
        // update transform
        // (moving in a circle with radius=2)
        // FL_odom
        odom_FL.header.stamp = ros::Time::now();
        odom_FL.transform.translation.x = 0.203;
        odom_FL.transform.translation.y = 0.178;
        odom_FL.transform.translation.z = -0.075;
        odom_FL.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(0,FL_ro,0);
        //FR_odom
        odom_FR.header.stamp = ros::Time::now();
        odom_FR.transform.translation.x = 0.203;
        odom_FR.transform.translation.y = -0.178;
        odom_FR.transform.translation.z = -0.075;
        odom_FR.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(0,FR_ro,0);
        //BL_odom
        odom_BL.header.stamp = ros::Time::now();
        odom_BL.transform.translation.x = -0.203;
        odom_BL.transform.translation.y = 0.178;
        odom_BL.transform.translation.z = -0.075;
        odom_BL.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(0,BL_ro,0);
        //BR_odom
        odom_BR.header.stamp = ros::Time::now();
        odom_BR.transform.translation.x = -0.203;
        odom_BR.transform.translation.y = -0.178;
        odom_BR.transform.translation.z = -0.075;
        odom_BR.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(0,BR_ro,0);

        //j1 odom
        odom_j1.header.stamp = ros::Time::now();
        odom_j1.transform.translation.x = 0.1885;
        odom_j1.transform.translation.y = 0;
        odom_j1.transform.translation.z = 0;
        odom_j1.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(0,0,j1_ro);
        //j2 odom
        odom_j2.header.stamp = ros::Time::now();
        odom_j2.transform.translation.x = 0;
        odom_j2.transform.translation.y = 0;
        odom_j2.transform.translation.z = 0.145;
        odom_j2.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(0,j2_ro,0);
        //j3 odom
        odom_j3.header.stamp = ros::Time::now();
        odom_j3.transform.translation.x = -0.36;
        odom_j3.transform.translation.y = 0;
        odom_j3.transform.translation.z = 0.08;
        odom_j3.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(0,j3_ro,0);
        //j4 odom
        odom_j4.header.stamp = ros::Time::now();
        odom_j4.transform.translation.x = 0.391+j4_ro;
        odom_j4.transform.translation.y = 0;
        odom_j4.transform.translation.z = 0;
       odom_j4.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(0,0,0);

        //j5 odom
        odom_j5.header.stamp = ros::Time::now();
        odom_j5.transform.translation.x = 0;
        odom_j5.transform.translation.y = 0;
        odom_j5.transform.translation.z = 0;
        odom_j5.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(j5_ro,0,0);
        //j6 odom
        odom_j6.header.stamp = ros::Time::now();
        odom_j6.transform.translation.x = 0.09;
        odom_j6.transform.translation.y = 0;
        odom_j6.transform.translation.z = 0;
        odom_j6.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(0,j6_ro,0);

        odom_fix.header.stamp = ros::Time::now();
        odom_fix.transform.translation.x = 0.05;
        odom_fix.transform.translation.y = 0;
        odom_fix.transform.translation.z = 0.015;
        odom_fix.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(0,0,0);

        odom_base.header.stamp = ros::Time::now();
        odom_base.transform.translation.x = px;
        odom_base.transform.translation.y = py;
        odom_base.transform.translation.z = 0;
        odom_base.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(0,0,0);


        odom_top.header.stamp = ros::Time::now();
        odom_top.transform.translation.x = 0;
        odom_top.transform.translation.y = 0;
        odom_top.transform.translation.z = 0;
        odom_top.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(0,0,0);


        //send the joint state and transform
        joint_pub.publish(joint_state);
        broadcaster.sendTransform(odom_FL);
        broadcaster.sendTransform(odom_FR);
        broadcaster.sendTransform(odom_BL);
        broadcaster.sendTransform(odom_BR);
        broadcaster.sendTransform(odom_j1);
        broadcaster.sendTransform(odom_j2);
        broadcaster.sendTransform(odom_j3);
        broadcaster.sendTransform(odom_j4);
        broadcaster.sendTransform(odom_j5);
        broadcaster.sendTransform(odom_j6);
         broadcaster.sendTransform(odom_base);
         broadcaster.sendTransform(odom_fix);
     broadcaster.sendTransform(odom_top);


        // Create new robot state
      //  tilt += tinc;
       // if (tilt<-.5 || tilt>0) tinc *= -1;
        //height += hinc;
        //if (height>.2 || height<0) hinc *= -1;
        //swivel += degree;
        //angle += degree/4;

       //  This will adjust as needed per iteration
        loop_rate.sleep();
        ros::spinOnce();
    }




    return 0;
}
