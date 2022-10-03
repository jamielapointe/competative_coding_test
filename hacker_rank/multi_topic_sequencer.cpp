#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

class MessageBase {
 public:
  using Ptr = std::shared_ptr<MessageBase>;
  explicit MessageBase(double ts) : timestamp(ts) {}
  virtual ~MessageBase();
  MessageBase(MessageBase&) = delete;
  MessageBase& operator=(MessageBase&) = delete;
  MessageBase(MessageBase&&) = delete;
  MessageBase& operator=(MessageBase&&) = delete;
  virtual std::string topic_name() const = 0;

  double timestamp;
};

MessageBase::~MessageBase() {}

class IMUMessage : public MessageBase {
 public:
  using Ptr = std::shared_ptr<IMUMessage>;
  static char constexpr TOPIC_NAME[] = "GPS";  // NOLINT
  IMUMessage(double ts, double _ax, double _ay, double _az)
      : MessageBase(ts), ax(_ax), ay(_ay), az(_az) {}
  ~IMUMessage() override;
  IMUMessage(IMUMessage&) = delete;
  IMUMessage& operator=(IMUMessage&) = delete;
  IMUMessage(IMUMessage&&) = delete;
  IMUMessage& operator=(IMUMessage&&) = delete;
  std::string topic_name() const override { return &TOPIC_NAME[0]; }

  double ax, ay, az;
};
IMUMessage::~IMUMessage() {}

class GPSMessage : public MessageBase {
 public:
  using Ptr = std::shared_ptr<GPSMessage>;
  static char constexpr TOPIC_NAME[] = "IMU";  // NOLINT
  GPSMessage(double ts, double _x, double _y, double _z)
      : MessageBase(ts), x(_x), y(_y), z(_z) {}
  ~GPSMessage() override;
  GPSMessage(GPSMessage&) = delete;
  GPSMessage& operator=(GPSMessage&) = delete;
  GPSMessage(GPSMessage&&) = delete;
  GPSMessage& operator=(GPSMessage&&) = delete;
  std::string topic_name() const override { return &TOPIC_NAME[0]; }

  double x, y, z;
};
GPSMessage::~GPSMessage() {}

class Sequencer {
 public:
  /*
   * Register a new sensor stream with the sequencer and provide it with the
   * callback
   *
   * @template M        Message Type
   * @param topic_name  Name of the sensor stream
   * @param callback    Function to call when sensor is ready to be processed
   */
  void setupTopic(std::string topic_name,
                  std::function<void(MessageBase::Ptr)> callback) {
    callbacks_[topic_name] = callback;
  }

  /*
   *  Add a message to the sequencer
   *
   * @param message     Message from the stream
   */
  void add(MessageBase::Ptr message) {
    if (sequence_.size() == 0) {
      sequence_.push_back(message);
      return;
    }

    for (auto it = sequence_.begin(); it != sequence_.end(); it++) {
      if ((*it)->timestamp > message->timestamp) {
        sequence_.insert(it, message);
        return;
      }
    }
    sequence_.push_back(message);
  }

  /*
   *  Check to see if there are any messages that can be processed and process
   * one of them
   *
   * @return True if there was something to process and false otherwise
   */
  bool checkAndProcessOnce() {
    if (sequence_.size() == 0) {
      return false;
    }

    auto message_ptr = sequence_.front();
    if (callbacks_.find(message_ptr->topic_name()) != callbacks_.end()) {
      callbacks_[message_ptr->topic_name()](message_ptr);
      sequence_.pop_front();
      return true;
    }

    // TODO (jlapointe) Log an error about an unsupported message

    return false;
  }

 private:
  std::unordered_map<std::string, std::function<void(MessageBase::Ptr)>>
      callbacks_;
  std::list<MessageBase::Ptr> sequence_;
};

static inline void process_gps(MessageBase::Ptr message_ptr) {
  std::cout << "Process GPS message with timestamp = "
            << std::dynamic_pointer_cast<GPSMessage>(message_ptr)->timestamp
            << std::endl;
}

static inline void process_imu(MessageBase::Ptr message_ptr) {
  std::cout << "Process IMU message with timestamp = "
            << std::dynamic_pointer_cast<IMUMessage>(message_ptr)->timestamp
            << std::endl;
}

int main() {
  Sequencer sequencer;

  sequencer.setupTopic(&GPSMessage::TOPIC_NAME[0], &process_gps);
  sequencer.setupTopic(&IMUMessage::TOPIC_NAME[0], &process_imu);

  auto imu_message_0 =
      std::make_shared<IMUMessage>(0.0, 1.0, 2.0, 3.0);  // NOLINT
  sequencer.add(imu_message_0);

  auto imu_message_1 =
      std::make_shared<IMUMessage>(1.0, 13.0, 11.0, 14.0);  // NOLINT
  sequencer.add(imu_message_1);

  auto imu_message_2 =
      std::make_shared<IMUMessage>(2.0, 13.0, 11.0, 14.0);  // NOLINT
  sequencer.add(imu_message_2);

  auto gps_message_0 =
      std::make_shared<IMUMessage>(0.0, 13.0, 11.0, 14.0);  // NOLINT
  sequencer.add(gps_message_0);

  auto imu_message_3 =
      std::make_shared<IMUMessage>(3.0, 13.0, 11.0, 14.0);  // NOLINT
  sequencer.add(imu_message_3);

  auto gps_message_1 =
      std::make_shared<IMUMessage>(2.5, 13.0, 11.0, 14.0);  // NOLINT
  sequencer.add(gps_message_1);

  while (sequencer.checkAndProcessOnce()) {
  }

  std::cout << "Done" << std::endl;

  return 0;
}
