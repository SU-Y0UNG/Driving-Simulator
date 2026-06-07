#pragma once
#ifndef BESTDRIVER_REPLAY_RECORDER_H
#define BESTDRIVER_REPLAY_RECORDER_H

#include "common_types.h"
#include "map_system.h"
#include <vector>

namespace bestdriver {

    struct ReplayFrame {
        float timestamp;
        VehicleState vehicle;
        VehicleControl control;
        std::vector<Penalty> penaltiesThisFrame;
        std::vector<NpcCar> npcCars;
        ReplayFrame() : timestamp(0) {}
    };

    class ReplayRecorder {
    public:
        ReplayRecorder(float recordInterval = 0.033f);
        void record(float elapsedTime, float dt, const VehicleState& vehicle, const VehicleControl& ctrl,
                    const std::vector<Penalty>& penalties, const std::vector<NpcCar>& npcs);
        const std::vector<ReplayFrame>& getFrames() const;
        void reset();
        void setRecordInterval(float interval);
        float getRecordInterval() const;
    private:
        std::vector<ReplayFrame> frames_;
        float recordInterval_;
        float timeSinceLastRecord_;
    };

} // namespace bestdriver

#endif
