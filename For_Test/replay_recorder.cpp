#include "replay_recorder.h"
#include <algorithm>

namespace bestdriver {

ReplayRecorder::ReplayRecorder(float ri) : recordInterval_(ri > 0.001f ? ri : 0.001f), timeSinceLastRecord_(0) {}

void ReplayRecorder::record(float elapsed, float dt, const VehicleState& v, const VehicleControl& c,
                            const std::vector<Penalty>& p, const std::vector<NpcCar>& npcs) {
    if (dt < 0) dt = 0;
    timeSinceLastRecord_ += dt;
    bool hasPen = !p.empty();
    bool should = frames_.empty() || hasPen || timeSinceLastRecord_ >= recordInterval_;
    if (!should) return;
    ReplayFrame f; f.timestamp=elapsed; f.vehicle=v; f.control=c; f.penaltiesThisFrame=p; f.npcCars=npcs;
    frames_.push_back(f);
    timeSinceLastRecord_ = 0;
}

const std::vector<ReplayFrame>& ReplayRecorder::getFrames() const { return frames_; }
void ReplayRecorder::reset() { frames_.clear(); timeSinceLastRecord_=0; }
void ReplayRecorder::setRecordInterval(float i) { recordInterval_ = i > 0.01f ? i : 0.01f; }
float ReplayRecorder::getRecordInterval() const { return recordInterval_; }

} // namespace bestdriver
