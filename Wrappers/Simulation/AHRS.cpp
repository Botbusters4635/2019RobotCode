//
// Created by abiel on 10/19/19.
//

#include "AHRS.h"

AHRS::AHRS(frc::SPI::Port){
	;
}

AHRS::AHRS(I2C::Port i2c_port_id){
	;
}

AHRS::AHRS(SerialPort::Port serial_port_id){
	;
}

AHRS::AHRS(SPI::Port spi_port_id, uint8_t update_rate_hz){
	;
}

AHRS::AHRS(SPI::Port spi_port_id, uint32_t spi_bitrate, uint8_t update_rate_hz){
	;
}

AHRS::AHRS(I2C::Port i2c_port_id, uint8_t update_rate_hz){
	;
}

AHRS::AHRS(SerialPort::Port serial_port_id, AHRS::SerialDataType data_type, uint8_t update_rate_hz){
	;
}

float  AHRS::GetPitch(){
	return 0.0;
}

float  AHRS::GetRoll(){
	return 0.0;
}

float  GetYaw(){
	return 0.0;
}

float AHRS::GetCompassHeading(){
	return 0.0;
}

void  AHRS::ZeroYaw(){
	;
}
bool AHRS::IsCalibrating(){
	return false;
}

bool AHRS::IsConnected(){
	return true;
}

double AHRS::GetByteCount(){
	return 0.0;
}

double AHRS::GetUpdateCount(){
	return 0.0;
}

long  AHRS::GetLastSensorTimestamp(){
	return 0;
}

float  AHRS::GetWorldLinearAccelX(){
	return 0.0;
}

float  AHRS::GetWorldLinearAccelY(){
	return 0.0;
}
float  AHRS::GetWorldLinearAccelZ(){
	return 0.0;
}

bool  AHRS::IsMoving(){
	return false;
}

bool  AHRS::IsRotating(){
	return false;
}

float  GetBarometricPressure(){
	return 0.0;
}

float  AHRS::GetAltitude(){
	return 0.0;
}

bool   AHRS::IsAltitudeValid(){
	return false;
}

float  AHRS::GetFusedHeading(){
	return 0.0;
}

bool  AHRS::IsMagneticDisturbance(){
	return false;
}

bool  AHRS::IsMagnetometerCalibrated(){
	return false;
}

float  AHRS::GetQuaternionW(){
	return 0.0;
}

float  AHRS::GetQuaternionX(){
	return 0.0;
}
float  AHRS::GetQuaternionY(){
	return 0.0;
}

float  AHRS::GetQuaternionZ(){
	return 0.0;
}

void   AHRS::ResetDisplacement(){
	;
}
void   AHRS::UpdateDisplacement( float accel_x_g, float accel_y_g,
                           int update_rate_hz, bool is_moving ){
	;
}

float  AHRS::GetVelocityX(){
	return 0.0;
}

float  AHRS::GetVelocityY(){
	return 0.0;
}

float  AHRS::GetVelocityZ(){
	return 0.0;
}

float  AHRS::GetDisplacementX(){
	return 0.0;
}

float  AHRS::GetDisplacementY(){
	return 0.0;
}

float  AHRS::GetDisplacementZ(){
	return 0.0;
}

double AHRS::GetAngle(){
	return 0.0;
}

double AHRS::GetRate(){
	return 0.0;
}

void   AHRS::SetAngleAdjustment(double angle){
	;
}

double GetAngleAdjustment(){
	return 0.0;
}

void  AHRS::Reset(){
	;
}

float  AHRS::GetRawGyroX(){
	return 0.0;
}
float  AHRS::GetRawGyroY(){
	return 0.0;
}
float  AHRS::GetRawGyroZ(){
	return 0.0;
}
float  AHRS::GetRawAccelX(){
	return 0.0;
}
float  AHRS::GetRawAccelY(){
	return 0.0;
}
float  AHRS::GetRawAccelZ(){
	return 0.0;
}
float  AHRS::GetRawMagX(){
	return 0.0;
}
float  AHRS::GetRawMagY(){
	return 0.0;
}
float  AHRS::GetRawMagZ(){
	return 0.0;
}
float  AHRS::GetPressure(){
	return 0.0;
}
float  AHRS::GetTempC(){
	return 0.0;
}

std::string AHRS::GetFirmwareVersion(){
	return "0.0";
}

bool AHRS::RegisterCallback( ITimestampedDataSubscriber *callback, void *callback_context){
	return false;
}

bool AHRS::DeregisterCallback( ITimestampedDataSubscriber *callback ){
	return false;
}

int AHRS::GetActualUpdateRate(){
	return 0;
}

int AHRS::GetRequestedUpdateRate(){
	return 0;
}

void AHRS::EnableLogging(bool enable){
	;
}

float AHRS::GetYaw(){
	return 0;
}

int16_t AHRS::GetGyroFullScaleRangeDPS(){
	return 0;
}
int16_t AHRS::GetAccelFullScaleRangeG(){
	return 0;
}

void AHRS::InitSendable(frc::SendableBuilder& builder){
	;
}

double AHRS::PIDGet(){
	return 0;
}