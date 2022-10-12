#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MinimalPublisher : public rclcpp::Node {
   private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
    size_t count;
    rclcpp::TimerBase::SharedPtr timer;
    rclcpp::Logger logger = rclcpp::get_logger("MinimalPublisher");

   public:
    MinimalPublisher() : Node("MinimalPublisher"), count(0) {
        publisher = this->create_publisher<std_msgs::msg::String>("topic", 10);
        timer = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&MinimalPublisher::timer_callback, this));
    }

   private:
    void timer_callback() {
        auto message = std_msgs::msg::String();
        message.data = "Hello, world! " + std::to_string(count++);
        RCLCPP_INFO(logger, "Publishing: '%s'", message.data.c_str());
        publisher->publish(message);
    }
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalPublisher>());
    rclcpp::shutdown();
    return 0;
}