#include "config.h"

#include "SharedTimer.h"
#include "Headless.h"

#include <wtf/Assertions.h>
#include <wtf/CurrentTime.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

namespace WebCore {

static void (*sharedTimerFiredFunction)();
static bool initialized = false;

static double delayTime = 0;

void runSharedTimerFiredFunction(void)
{
    	sharedTimerFiredFunction();
}

void setSharedTimerFiredFunction(void (*f)())
{
    	sharedTimerFiredFunction = f;
}

void setSharedTimerFireTime(double fireTime)
{
    ASSERT(sharedTimerFiredFunction);
    Headless::set_timer_callback( runSharedTimerFiredFunction, fireTime);
}

void stopSharedTimer()
{
    Headless::set_timer_callback( 0, 0);
}

}
