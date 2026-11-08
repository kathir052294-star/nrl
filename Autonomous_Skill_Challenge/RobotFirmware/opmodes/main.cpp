#include "NRL.h"

// change angles as needed
constexpr float ARM_UP = 45.0f;
constexpr float ARM_DOWN = 115.0f;
constexpr float CLAW_OPEN = 125.0f;
constexpr float CLAW_CLOSED = 155.0f;

static HexaDCMotor leftMotor{{.dirPin = MOTOR_L_DIR, .pwmPin = MOTOR_L_PWM}};
static HexaDCMotor rightMotor{{.dirPin = MOTOR_R_DIR, .pwmPin = MOTOR_R_PWM, .flipped = true}};

static HexaServo arm{{.signalPin = SERVO_1, .startAngle = ARM_DOWN, .settleMs = 0}};
static HexaServo claw{{.signalPin = SERVO_2, .startAngle = CLAW_OPEN, .settleMs = 0}};

static TankDrive drive(leftMotor, rightMotor);
static DriveActions driveActions(drive);

static HexaLineArray line{hexaLineConfig()};
static LineActions lineActions(drive, line);

static ActionPtr dropCore()
{
    arm.setPosition(ARM_DOWN);
    claw.setPosition(CLAW_OPEN);
}

static ActionPtr pickCore()
{
    claw.setPosition(CLAW_CLOSED);
    arm.setPosition(ARM_UP);
}

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
        int count;
        // driveActions.drive;
        while (true)
        {
            count = __builtin_popcount(line.mask()); // gets how many of the sensors are returning black(1)
            if (2 <= count <= 4)
            {
                break;
            }
        }
    }

    void loop() override
    {
        int corenum = 1;
        lineActions.clearFault();
        lineActions.resetCounts();
        lineActions.clearRoute();
    }

    void stop() override
    {
        // Runs once on STOP — stop your motors/servos here.
    }
};

REGISTER_OPMODE(main, "main", AUTO);
