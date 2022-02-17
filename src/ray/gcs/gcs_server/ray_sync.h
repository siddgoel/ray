// Copyright 2022 The Ray Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <memory>

namespace ray {
namespace sync {

class RaySync {
 public:
  RaySync(std::unique_ptr<ray::gcs::GrpcBasedResourceBroadcaster> braodcaster,
          std::unique_ptr<ray::gcs::GcsResourceReportPoller> poller)
      : broadcaster_(std::move(braodcaster)), poller_(std::move(poller)) {}

  void Start();
  void Stop();

  void AddNode(const rpc::GcsNodeInfo &node_info) {
    broadcaster_->HandleNodeAdded(node_info)
        gcs_resource_report_poller_->HandleNodeAdded(node_info);
  }

  void RemoveNode() {
    broadcaster_->HandleNodeRemoved(*node);
    gcs_resource_report_poller_->HandleNodeRemoved(*node);
  }

  std::string DebugString() { return broadcaster_->DebugString(); }

 private:
  std::unique_ptr<ray::gcs::GrpcBasedResourceBroadcaster> broadcaster_;
  std::unique_ptr<ray::gcs::GcsResourceReportPoller> poller_;
};

}  // namespace sync
}  // namespace ray
