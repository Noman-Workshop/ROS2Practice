#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class MinimalSubscriber : public rclcpp::Node {
   private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription;
    rclcpp::Logger logger = rclcpp::get_logger("MinimalSubscriber");

   public:
    MinimalSubscriber() : Node("MinimalSubscriber") {
        subscription = this->create_subscription<std_msgs::msg::String>("topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, std::placeholders::_1));
    }

   private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const {
        RCLCPP_INFO(logger, "I heard: '%s'", msg->data.c_str());
    }
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalSubscriber>());
    rclcpp::shutdown();
    return 0;
}