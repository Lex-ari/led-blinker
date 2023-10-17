// ======================================================================
// \title  Led.cpp
// \author xf104starfighter
// \brief  cpp file for Led component implementation class
// ======================================================================


#include <Components/Led/Led.hpp>
#include <FpConfig.hpp>

namespace Components {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  Led ::Led(const char* const compName) : LedComponentBase(compName),
    state(Fw::On::OFF),
    transitions(0),
    count(0),
    blinking(false)
  {}

  Led ::
    ~Led()
  {

  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void Led ::
    BLINKING_ON_OFF_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        Fw::On on_off
    )
  {
    // Create a variable to represent the command response
    auto cmdResp = Fw::CmdResponse::OK;

    // Verify if on_off is a valid argument.
    // Note: isValid is an autogenerate helper function for enums defined in fpp.
    if(!on_off.isValid())
    {
      //Event that indicates we received invalid arg
      this->log_WARNING_LO_InvalidBlinkArgument(on_off);

      // Update command response with a validation error
      cmdResp = Fw::CmdResponse::VALIDATION_ERROR;
    }
    else
    {
      this->count = 0; // Reset count on any successful command
      this->lock.lock();
      this->blinking = Fw::On::ON == on_off; // Update blinking state
      this->lock.unlock();

      //Event that reports the state we set to blinking.
      this->log_ACTIVITY_HI_SetBlinkingState(on_off);

      // TODO: Report the blinking state via a telemetry channel.
      // NOTE: This telemetry channel will be added during the "Telemetry" exercise.
    }

    // Provide command response
    this->cmdResponse_out(opCode,cmdSeq,cmdResp);
  }

} // end namespace Components
