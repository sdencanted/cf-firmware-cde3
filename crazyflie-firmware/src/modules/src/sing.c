/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie Firmware
 *
 * Copyright (C) 2011-2016 Bitcraze AB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Health modules that is trying to find problems such as unbalanced
 * propellers or a bad power path/battery.
 *
 * Propeller test is done by spinning the each propeller after one another
 * while measuring the vibrations with the accelerometer.
 *
 * The battery test is done by doing a quick burst of all the motors while
 * measuring the maximum voltage sag. The sag is pretty constant over the
 * battery voltage range but usually a tiny bit higher at full voltage. The
 * result is heavily dependent on what components are monunted so needs
 * returning if anything is different/changed.
 *
 */
#define DEBUG_MODULE "SING"

#include "config.h"
#include "log.h"
#include "param.h"
#include "debug.h"
#include "motors.h"
#include "sensors.h"
#include "pm.h"

#include "static_mem.h"
static bool startSing=false;
static uint16_t duration,frequency_0,frequency_1,frequency_2,frequency_3;

bool shallWeSing()
{
    if (startSing != false) {
        startSing = false;
        return true;
    }
    return false;
}
void doSing(){
    motorsPlayTones(duration,frequency_0,frequency_1,frequency_2,frequency_3);
}
PARAM_GROUP_START(sing)
PARAM_ADD(PARAM_UINT8, s, &startSing)
PARAM_ADD(PARAM_UINT16, d, &duration)
PARAM_ADD(PARAM_UINT16, f0, &frequency_0)
PARAM_ADD(PARAM_UINT16, f1, &frequency_1)
PARAM_ADD(PARAM_UINT16, f2, &frequency_2)
PARAM_ADD(PARAM_UINT16, f3, &frequency_3)
PARAM_GROUP_STOP(sing)
