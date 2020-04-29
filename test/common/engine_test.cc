#include "gtest/gtest.h"
#include "library/common/engine.h"
#include "library/common/main_interface.h"
#include "absl/synchronization/notification.h"

namespace Envoy {

class EngineTest : public testing::Test {};

TEST_F(EngineTest, EarlyExit) {
  const std::string config = "admin: {}";
  const std::string level = "debug";
  absl::Notification done;
  envoy_engine_callbacks cbs{[](void *context) -> void {
    auto* done = static_cast<absl::Notification*>(context);
    done->Notify();
  }, &done};

  run_engine(0, cbs, config.c_str(), level.c_str());

  stop_loop();

  ASSERT_TRUE(done.WaitForNotificationWithTimeout(absl::Seconds(1)));

  start_stream(0, {});
}
} // namespace Envoy
