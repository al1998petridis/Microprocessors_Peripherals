#include "Application.h"
#include "Gui/Gui.h"


Application::Application() :
  mTemperatureControllerTimer( this ),
  // cooling temperature 8 +/- 2 degrees, alarm at 14 degrees
  mTemperatureController( 8000, 2000, 14000 ),
  mVendingMode(),
  mGlobalState( mVendingMode, mMaintenanceMode )
{
  Platform::PowerSupervision::enableCallback();
  Platform::LightBarrier::enableCallback();
  Platform::FrontDoorProtection::enableCallback();
  Platform::ReturnMoneyButton::enableCallback();
  Platform::FilledUpButton::enableCallback();
  Platform::Product1Button::enableCallback();
  Platform::Product2Button::enableCallback();
  Platform::Product3Button::enableCallback();
  Platform::Product4Button::enableCallback();
  Platform::TemperatureSensor::enableCallback();
  mTemperatureControllerTimer.startPeriodic( Platform::OS::MilliSec<100>::value );
}


void Application::run() const
{
  for( ;; )
  {
    Platform::OS::processEvents();
    Platform::enterSleepMode();
  }
}

void Application::onTemperatureControllerTimerEvent( ThisType* t, u8 callCnt )
{
  redBlocks::unused( callCnt );
  t->mTemperatureController.runOnce();
}

