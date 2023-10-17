// ======================================================================
// \title  Led.hpp
// \author xf104starfighter
// \brief  hpp file for Led component implementation class
// ======================================================================

#ifndef Led_HPP
#define Led_HPP

#include "Components/Led/LedComponentAc.hpp"
#include <Os/Mutex.hpp>
#include <Fw/Types/OnEnumAc.hpp>

namespace Components {

  class Led :
    public LedComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object Led
      //!
      Led(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object Led
      //!
      ~Led();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for TODO command handler
      //! Implementation for BLINKING_ON_OFF command handler
      //! Command to turn on or off the blinking LED
      void BLINKING_ON_OFF_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          Fw::On on_off /*!< 
          Indicates whether the blinking should be on or off
          */
      );

      Os::Mutex lock; //! Protects our data from thread race conditions
      Fw::On state; //! Keeps track if LED is on or off
      U64 transitions; //! The number of on/off transitions that have occurred from FSW boot up
      U32 count; //! Keeps track of how many ticks the LED has been on for
      bool blinking; //! Flag: if true then LED blinking will occur else no blinking will happen

    };

} // end namespace Components

#endif
