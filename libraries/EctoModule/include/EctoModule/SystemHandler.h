//
// Created by alberto on 7/07/19.
//

#ifndef BOTBUSTERS_REBIRTH_COMPONENTHANDLER_H
#define BOTBUSTERS_REBIRTH_COMPONENTHANDLER_H

#include "System.h"
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>
#include <fmt/format.h>

typedef boost::accumulators::accumulator_set<double, boost::accumulators::features<boost::accumulators::tag::rolling_mean, boost::accumulators::tag::min, boost::accumulators::tag::max>> TimeAccumulator;

class TimingData {
public:
    TimingData(size_t windowSize = 100) :
            updateRobotTime(boost::accumulators::tag::rolling_window::window_size = windowSize),

            updateDisabledTime(boost::accumulators::tag::rolling_window::window_size = windowSize),

            updateTeleopTime(boost::accumulators::tag::rolling_window::window_size = windowSize),

            updateAutoTime(boost::accumulators::tag::rolling_window::window_size = windowSize),

            updateTestTime(boost::accumulators::tag::rolling_window::window_size = windowSize) {
        ;
    }

    /**
     * Formats data into a nice string to print out
     * @return
     */
    std::string getData() const {
        std::stringstream data;
        data << fmt::format("Robot Init: {}sec Update Min: {}sec Update Max: {}sec Update Average: {}sec", initRobotTime,
                            boost::accumulators::min(updateRobotTime), boost::accumulators::max(updateRobotTime),
                            boost::accumulators::rolling_mean(updateRobotTime)) << std::endl;

        data << fmt::format("Disabled Init: {}sec Update Min: {}sec Update Max: {}sec Update Average: {}sec", initDisabledTime,
                            boost::accumulators::min(updateDisabledTime), boost::accumulators::max(updateDisabledTime),
                            boost::accumulators::rolling_mean(updateDisabledTime)) << std::endl;

        data << fmt::format("Teleop Init: {}sec Update Min: {}sec Update Max: {}sec Update Average: {}sec", initTeleopTime,
                            boost::accumulators::min(updateTeleopTime), boost::accumulators::max(updateTeleopTime),
                            boost::accumulators::rolling_mean(updateTeleopTime)) << std::endl;

        data << fmt::format("Auto Init: {}sec Update Min: {}sec Update Max: {}sec Update Average: {}sec", initAutoTime,
                            boost::accumulators::min(updateAutoTime), boost::accumulators::max(updateAutoTime),
                            boost::accumulators::rolling_mean(updateAutoTime)) << std::endl;

        data << fmt::format("Test Init: {} Update Min: {} Update Max: {} Update Average: {}", initTestTime,
                            boost::accumulators::min(updateTestTime), boost::accumulators::max(updateTestTime),
                            boost::accumulators::rolling_mean(updateTestTime));

        return data.str();
    }

    double initRobotTime;
    TimeAccumulator updateRobotTime;

    double initDisabledTime;
    TimeAccumulator updateDisabledTime;

    double initTeleopTime;
    TimeAccumulator updateTeleopTime;

    double initAutoTime;
    TimeAccumulator updateAutoTime;

    double initTestTime;
    TimeAccumulator updateTestTime;
};

class SystemHandler : public System {
    /***
     * I should have been SystemMuckamuck but I was oppressed, as I was too advanced for my time
     * The revolution stats today.
     */
public:
    explicit SystemHandler(const std::string &name = "SystemHandler");

    void initRobot() override;

    void updateRobot() override;

    void initDisabled() override;

    void updateDisabled() override;

    void initTeleop() override;

    void updateTeleop() override;

    void initAuto() override;

    void updateAuto() override;

    void initTest() override;

    void updateTest() override;

    bool addSubsystem(System &newSystem);

    bool addSubsystem(const std::shared_ptr<System> &newSystem);

    std::vector<std::pair<std::string, TimingData>> getTimingData() const;

private:
    struct SystemData {
        std::shared_ptr<System> subsystem;
        TimingData timingData;
    };

    std::vector<SystemData> systems;
};


#endif //BOTBUSTERS_REBIRTH_COMPONENTHANDLER_H
