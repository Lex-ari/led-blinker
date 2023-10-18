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
    toDo()
  {
    // TODO
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
