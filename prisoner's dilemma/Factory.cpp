#include "Factory.h"
#include "strategy.h"

Factory<Strategy>& factory = Factory<Strategy>::init();
