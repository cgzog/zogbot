// RobotBuilder Version: 4.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Subsystem.
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/DigitalInput.h>

#include "Constants.h"

#ifndef ZOGBOT
#include <ctre/phoenix.h>
#else   // ZOGBOT
#include <rev/CANSparkMax.h>
#endif  // ZOGBOT


/**
 *
 *
 * @author ExampleAuthor
 */
class Drivetrain: public frc2::SubsystemBase {
private:
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities

#ifndef ZOGBOT        //normal Porterbots build does not have this defined
    WPI_VictorSPX m_leftFrontController{Porterbots::CAN_ID::kMotorLeftFrontID};
    WPI_VictorSPX m_leftRearController{Porterbots::CAN_ID::kMotorLeftRearID};
    frc::MotorControllerGroup m_leftSideMotors{m_leftFrontController, m_leftRearController};

    WPI_VictorSPX m_rightFrontController{Porterbots::CAN_ID::kMotorRightFrontID};
    WPI_VictorSPX m_rightRearController{Porterbots::CAN_ID::kMotorRightRearID};
    frc::MotorControllerGroup m_rightSideMotors{m_rightFrontController, m_rightRearController};    
#else   // ZOGBOT
// only using 2 SparkMax controllers but we'll end up with the same motor controllers
// defined so the code will all be the same (pretty much)
    rev::CANSparkMax m_leftFrontController{Porterbots::CAN_ID::kMotorLeftFrontID, rev::CANSparkMax::MotorType::kBrushless};
    frc::MotorControllerGroup m_leftSideMotors{m_leftFrontController};

    rev::CANSparkMax m_rightFrontController{Porterbots::CAN_ID::kMotorRightFrontID, rev::CANSparkMax::MotorType::kBrushless};
    frc::MotorControllerGroup m_rightSideMotors{m_rightFrontController};   
#endif  // ZOGBOT

    frc::DifferentialDrive m_robotDrive{m_leftFrontController, m_rightFrontController};

    // line sensors live here since they are integral to the drive system and only used by the drive system
    frc::DigitalInput m_rightLineSensor{Porterbots::LineDetection::kRightLineSensor};
    frc::DigitalInput m_leftLineSensor{Porterbots::LineDetection::kLeftLineSensor};

    bool    m_lineAlignCompleted;

public:
    Drivetrain();

    // a few different types of drive mode
    //
    // tank and arcade are very specific drive modes in regards to the joystick operations
    //
    // the "Drive" routine can wrap either mode allow us to switch the drive mode of the robot
    // from tank to arcade mode if we liike and leave all of the operator interaction code using
    // usintg the "Drive" routine
    //
    // some of the command-controlled drive operations might be easier o handle using one drive
    // mode or the other so they would likely call the mode they prefer directly
    void Drive(double input1, double input2);
    void TankDrive(double left, double right);
    void ArcadeDrive(double speed, double turn);

    // returns an indication from a specific sensor for line detection
    bool IsLineDetected(int sensor);

    void Periodic() override;
    void SimulationPeriodic() override;
};

