/*
 * bmx055.cpp
 *
 *  Created on: 2018��5��30��
 *      Author: shuixiang
 */

#include "i2c.h"

#include "bmx055.hpp"

namespace hustac {

BMX055 bmx055_camera(&hi2c1, false, false, false);

}

