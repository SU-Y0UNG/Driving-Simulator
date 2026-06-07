#pragma once
#ifndef BESTDRIVER_RENDERER_H
#define BESTDRIVER_RENDERER_H

#include "common_types.h"
#include "map_system.h"
#include "replay_recorder.h"
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <utility>
#include <string>

namespace bestdriver {

    class Renderer {
    public:
        Renderer();
        ~Renderer();

        bool init();
        bool isOpen() const;
        bool processEvents();

        void beginFrame(sf::Time dt);
        void endFrame();
        void drawCourseSelectUi(int& selectedCourse, bool& confirmed, bool& back);

        sf::RenderWindow& window();
        const sf::RenderWindow& window() const;

        float getZoom() const;
        void setZoom(float zoom);
        float recommendZoom(const MapSystem& map, float fillRatio = 0.90f) const;


        void drawWorld(const MapSystem& map,
            const VehicleState& vehicle,
            const Trail* trail = nullptr,
            const std::vector<TrafficSignal>* signals = nullptr,
            const std::vector< std::pair<Vec2, Penalty> >* penaltyMarkers = nullptr,
            const ParkingSlot* targetSlot = nullptr,
            const std::vector<Checkpoint>* checkpoints = nullptr);

        void drawMenuUi(int selectedIndex,
            bool& roadARequested,
            bool& roadBRequested,
            bool& parallelParkingRequested,
            bool& tParkingRequested,
            bool& quitRequested);
        void drawDrivingUi(const VehicleState& vehicle,
            int cpDone, int cpTotal,
            int penalty, float elapsed,
            int collisions,
            const std::string& warning,
            float warnTime,
            bool courseMode,
            bool& menuRequested);
        void drawResultUi(const std::string& title,
            float elapsed,
            int cpDone, int cpTotal,
            int penalty,
            int collisions,
            const std::vector<Penalty>& penaltyLog,
            bool disqualified,
            bool passed,
            const std::string& disqualifyReason,
            int finalScore,
            bool canReplay,
            bool& restartRequested,
            bool& replayRequested,
            bool& menuRequested,
            bool& quitRequested);

        void drawResultDetailUi(const std::string& title,
            int finalScore,
            bool disqualified,
            bool passed,
            const std::string& disqualifyReason,
            const std::vector<Penalty>& penaltyLog,
            bool& nextToMenuRequested,
            bool& replayRequested,
            bool& backRequested,
            bool canReplay);

        void drawCollisionUi(bool& restartRequested,
            bool& menuRequested,
            bool& quitRequested);

        void drawCollisionDetailUi(const std::string& title,
            const std::string& collisionReason,
            const std::vector<Penalty>& penaltyLog,
            bool& backRequested,
            bool& nextToMenuRequested);

        void drawReplayUi(float currentTime,
            float totalTime,
            float& playSpeed,
            bool paused,
            int frameIndex,
            int totalFrames,
            bool& togglePlay,
            bool& menuRequested,
            bool& restartRequested,
            bool& prevPenaltyRequested,
            bool& nextPenaltyRequested,
            int& requestedFrameIndex);

    private:
        sf::RenderWindow window_;
        bool initialized_;
        float zoom_;
        float pixelsPerCell_;

        void applyWorldView(const MapSystem& map, const VehicleState& focus);
        void resetUiView();

        void drawMapCells(const MapSystem& map);
        void drawCheckpoints(const std::vector<Checkpoint>& checkpoints);
        void drawTrail(const Trail& trail);
        void drawPenaltyMarkers(const std::vector< std::pair<Vec2, Penalty> >& penaltyMarkers);
        void drawSignals(const std::vector<TrafficSignal>& signals);
        void drawTargetSlot(const ParkingSlot& slot);
        void drawVehicle(const VehicleState& vehicle);
        void drawTile(TileID id, float px, float py);
        void drawNpcCars(const MapSystem& map);
        void drawMapCellsLegacy(const MapSystem& map);

        static sf::Color colorForRawCell(int rawCell);
        sf::Vector2f worldToPixels(const Vec2& p) const;
    };

} // namespace bestdriver

#endif
