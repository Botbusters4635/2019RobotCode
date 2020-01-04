#include "NavX.h"
#include "frc/smartdashboard/SmartDashboard.h"

NavX::NavX() : AHRS(SPI::kMXP) {
	Reset();
	ResetDisplacement();
	ZeroYaw();
	SmartDashboard::PutString("NavXFirmwareVersion", GetFirmwareVersion());
}