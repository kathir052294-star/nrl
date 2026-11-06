#include "NRL.h"

float ARM_START_ANGLE = 90.0f;  // change as needed
float CLAW_START_ANGLE = 90.0f; // change as needef

static HexaDCMotor leftMotor{{.dirPin = MOTOR_L_DIR, .pwmPin = MOTOR_L_PWM}};
static HexaDCMotor rightMotor{{.dirPin = MOTOR_R_DIR, .pwmPin = MOTOR_R_PWM, .flipped = true}};

static HexaServo arm{{.signalPin = SERVO_1, .startAngle = ARM_START_ANGLE, .settleMs = 0}};
static HexaServo claw{{.signalPin = SERVO_2, .startAngle = CLAW_START_ANGLE, .settleMs = 0}};

static TankDrive drive(leftMotor, rightMotor);
static DriveActions driveActions(drive);

static HexaLineArray line{hexaLineConfig()};
static LineActions navigation(drive, line);

class main : public NRLOpMode
{
public:
    void init() override
    {
        leftMotor.begin();
        rightMotor.begin();

        line.begin();

        arm.setRampRate(100.0f);
        arm.begin();

        claw.setRampRate(200.0f);
        claw.begin();
    }

    void start() override
    {
    }

    void loop() override
    {
        while (true)
        {
        }
    }

    void stop() override
    {
        // Runs once on STOP — stop your motors/servos here.
    }
};

REGISTER_OPMODE(main, "main", AUTO);
