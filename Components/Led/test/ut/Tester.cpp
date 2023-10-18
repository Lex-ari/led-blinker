// ======================================================================
// \title  Led.hpp
// \author xf104starfighter
// \brief  cpp file for Led test harness implementation class
// ======================================================================

#include "Tester.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  Tester ::
    Tester() :
      LedGTestBase("Tester", Tester::MAX_HISTORY_SIZE),
      component("Led")
  {
    this->initComponents();
    this->connectPorts();
  }

  Tester ::
    ~Tester()
  {

  }

  // ----------------------------------------------------------------------
  // Tests
  // ----------------------------------------------------------------------

  void Tester ::
    testBlinking()
  {
    // Ensure LED stays off when blinking is disabled
    // The Led component defaults to blinking off
    this->invoke_to_run(0,0); // invoke the 'run' port to simulate running one cycle
    ASSERT_EVENTS_LedState_SIZE(0); // ensure no LedState change events we emitted
    ASSERT_from_gpioSet_SIZE(0); // ensure gpio LED wasn't set
    ASSERT_TLM_LedTransitions_SIZE(0); // ensure no LedTransitions were recorded
  
    // Send command to enable blinking
    this->sendCmd_BLINKING_ON_OFF(0, 0, Fw::On::ON);
    this->component.doDispatch(); // Trigger execution of async command

    // Step through 3 run cycles to observe LED turning on and off 3 times
    // Cycle 1: LED initalization->On
    this->invoke_to_run(0,0);
    ASSERT_EVENTS_LedState_SIZE(1);
    ASSERT_EVENTS_LedState(0, Fw::On::ON);
    ASSERT_from_gpioSet_SIZE(1);
    ASSERT_from_gpioSet(0, Fw::Logic::HIGH);
    ASSERT_TLM_LedTransitions_SIZE(1);
    ASSERT_TLM_LedTransitions(0, 1);

    // Cycle 2: LED On->Off
    this->invoke_to_run(0,0);
    ASSERT_EVENTS_LedState_SIZE(2);
    ASSERT_EVENTS_LedState(1, Fw::On::OFF);
    ASSERT_from_gpioSet_SIZE(2);
    ASSERT_from_gpioSet(1, Fw::Logic::LOW);
    //TODO: Add assertions for LedTransitions telemetry

    // Cycle 3: LED Off->On
    this->invoke_to_run(0,0);
    //TODO: Write assertions for third cycle
  }

  void Tester ::
    testBlinkInterval()
  {
    // Enable LED Blinking
    this->sendCmd_BLINKING_ON_OFF(0, 0, Fw::On::ON);
    this->component.doDispatch(); // Trigger execution of async command

    // Adjust blink interval to 4 cycles
    U32 blinkInterval = 4;
    this->paramSet_BLINK_INTERVAL(blinkInterval, Fw::ParamValid::VALID);
    this->paramSend_BLINK_INTERVAL(0, 0);
    ASSERT_EVENTS_BlinkIntervalSet_SIZE(1);

    // TODO: Add logic to test adjusted blink interval
  }
  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------

  void Tester ::
    from_gpioSet_handler(
        const NATIVE_INT_TYPE portNum,
        const Fw::Logic &state
    )
  {
    this->pushFromPortEntry_gpioSet(state);
  }


} // end namespace Components
