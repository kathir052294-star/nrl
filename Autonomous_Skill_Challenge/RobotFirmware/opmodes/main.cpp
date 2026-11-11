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
    return sequential({instant([]
                               { arm.setPosition(ARM_DOWN); }),

                       instant([]
                               { claw.setPosition(CLAW_OPEN); })});
}

static ActionPtr pickCore()
{
    return sequential({instant([]
                               { claw.setPosition(CLAW_CLOSED); }),

                       instant([]
                               { arm.setPosition(ARM_UP); })});
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
        lineActions.clearFault();
        lineActions.resetCounts();
        lineActions.clearRoute();

        runAction(
            lineActions.auto_()
                .leaveBox()
                .followToJunction()
                .right()
                .followToEnd()
                .then(pickCore())
                .uTurn()
                .followToJunction()
                .right()
                .followToJunction()
                .left()
                .followToEnd()
                .then(dropCore())
                .uTurn()
                .followToJunction()
                .left()
                .followToJunction()
                .right()
                .followToEnd()
                .then(pickCore())
                .uTurn()
                .followToJunction()
                .left()
                .followToJunction()
                .right()
                .followToEnd()
                .then(dropCore())
                .uTurn()
                .followToJunction()
                .left()
                .followToJunction()
                .followToJunction()
                .right()
                .followToEnd()
                .then(pickCore())
                .uTurn()
                .followToJunction()
                .right()
                .followToJunction()
                .left()
                .followToEnd()
                .then(dropCore())
                .uTurn()
                .followToJunction()
                .left()
                .followToJunction()
                .right()
                .followToEnd()
                .then(pickCore())
                .uTurn()
                .followToJunction()
                .left()
                .followToJunction()
                .right()
                .followToEnd()
                .then(dropCore())
                .uTurn()
                .followToJunction()
                .left()
                .followToJunction()
                .followToJunction()
                .right()
                .followToEnd()
                .then(pickCore())
                .uTurn()
                .followToJunction()
                .right()
                .followToJunction()
                .left()
                .followToEnd()
                .then(dropCore())
                .uTurn()
                .followToJunction()
                .left()
                .followToJunction()
                .right()
                .followToEnd()
                .then(pickCore())
                .uTurn()
                .followToJunction()
                .left()
                .followToJunction()
                .right()
                .followToEnd()
                .then(dropCore())
                .uTurn()
                .followToJunction()
                .left()
                .followToJunction()
                .followToBox()
                .stop()
                .build());
    }

    void loop() override {}

    void stop() override
    {
        drive.stop();
    }
};

REGISTER_OPMODE(main, "main", AUTO);
