#include "NRL.h"

static HexaServo claw{{.signalPin = SERVO_2, .startAngle = 0.0f}};

#define CLAW_BTN BTN_LB // the red button, change if it's a different one
static const float CLAW_OPEN = 0.0f;
static const float CLAW_CLOSED = 90.0f;

class ClawTest : public NRLOpMode
{
public:
    void init() override
    {
        claw.begin();
        claw.setPosition(CLAW_OPEN);
    }
    void loop() override
    {
        claw.setPosition(gamepad1.pressed(CLAW_BTN) ? CLAW_CLOSED : CLAW_OPEN);
    }

    void stop() override
    {
        claw.setPosition(CLAW_OPEN);
    }
};

REGISTER_OPMODE(ClawTest, "Claw Test", TELEOP);