#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16MultiArray.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/PoseStamped.h>      //robot posisiton and orientation
#include <sensor_msgs/Imu.h>
int J1_angle = 0;
int J2_angle = 0;
int J3_angle = 0;
int J4_angle = 0;
int J5_angle = 0;
int J6_angle = 0;
int FR_angle = 0;
int FL_angle = 0;
int BR_angle = 0;
int BL_angle = 0;
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
geometry_msgs::PoseStamped Robot_pose;
double roll = 0;
double picth =0;
double step_move = 0.0001;
double step_rotate = 0.05;
ros::Publisher tele_pub;
std_msgs::String sent;
int FL_o, FR_o, BL_o, BR_o;
void leg_callback(const std_msgs::Int16MultiArrayConstPtr& leg)
{
    if(leg->data[0] !=0)FL_angle=leg->data[0]-90;
    if(leg->data[1]!=0)FR_angle = leg->data[1]-90;
    if(leg->data[2]!=0)BL_angle = leg->data[2]-90;
    if(leg->data[3]!=0)BR_angle = leg->data[3]-90;
    ROS_INFO("%d %d %d %d",FL_angle,FR_angle,BL_angle,BR_angle);

}
void RobotPoseCallback(const geometry_msgs::PoseStamped& Pose)
{
     Robot_pose = Pose;
}
void imucallback(const sensor_msgs::Imu& msg)
{
    roll = msg.orientation.x;
    picth = msg.orientation.y;
}

int main(int argc, char** argv)

{
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 100);  // advertised for updated
    tele_pub = n.advertise<std_msgs::String>("teleop_control",100);                        // advertise for teleopcontrol\
    ros::Subscriber joy_sub = n.subscribe("leg_pos",10,leg_callback);
   ros::Subscriber pose_sub = n.subscribe("slam_out_pose",10,RobotPoseCallback);           //
   ros::Subscriber imu = n.subscribe("imu_topic",10,imucallback);                          // subsribe IMU information
    tf::TransformBroadcaster broadcaster;
  // ros::Rate loop_rate(30);
Robot_pose.pose.position.x = 0;         // robot position in x-axis
Robot_pose.pose.position.y=0;           // robot position in y-axis
Robot_pose.pose.position.z=0;           // robot position in z-axis
Robot_pose.pose.orientation =  tf::createQuaternionMsgFromRollPitchYaw(0,0,0);  // create quaternion msg from RPY

    const double degree = M_PI/180;

    // robot state
    double FR_ro = 0, FL_ro = 0 , BR_ro=0, BL_ro=0, j1_ro=0,j2_ro=0,j3_ro=0,j4_ro=0,j5_ro=0,j6_ro=0;

    // message declarations
    geometry_msgs::TransformStamped odom_laser, odom, odom_top, odom_fix, odom_FL, odom_FR, odom_BL, odom_BR,odom_j1, odom_j2, odom_j3, odom_j4, odom_j5, odom_j6, odom_base;
    sensor_msgs::JointState joint_state;


    odom_base.header.frame_id = "map";
    odom_base.child_frame_id = "base_link";
     //odom.header.frame_id = "base_link";
     //odom.child_frame_id ="base_stabilized";

    odom_laser.header.frame_id ="base_link";
    odom_laser.child_frame_id = "laser";

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
        odom_base.transform.translation.x = Robot_pose.pose.position.x;
        odom_base.transform.translation.y = Robot_pose.pose.position.y;
        odom_base.transform.translation.z = Robot_pose.pose.position.z;
        odom_base.transform.rotation = Robot_pose.pose.orientation;


        odom_top.header.stamp = ros::Time::now();
        odom_top.transform.translation.x = 0;
        odom_top.transform.translation.y = 0;
        odom_top.transform.translation.z = 0;
        odom_top.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(0,0,0);

        odom_laser.header.stamp = ros::Time::now();
        odom_laser.transform.translation.x = 0.38;
        odom_laser.transform.translation.y = 0;
        odom_laser.transform.translation.z = 0;
        odom_laser.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(0,0,0);

     //   odom.header.stamp = ros::Time::now();
      // odom.transform.translation.x = 0;
       //odom.transform.translation.y = 0;
       //odom.transform.translation.z = 0;
       //odom.transform.rotation = tf::createQuaternionMsgFromRollPitchYaw(roll,picth,0);

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
       //broadcaster.sendTransform(odom);
       broadcaster.sendTransform(odom_laser);
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
