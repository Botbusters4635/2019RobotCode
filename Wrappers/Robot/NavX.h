/*
Creates a singleton class for NavX sensor
 */
#ifndef BOTBUSTERSREBIRTH_NAVXSINGLETON_H
#define BOTBUSTERSREBIRTH_NAVXSINGLETON_H

#include <mutex>
#include <AHRS.h>

/**
 * Creates a singleton class for NavX sensor
 * @param spi_port_id SPI Port (normally SPI::kMXP [When connected using the MXP port])
 */
class NavX : public AHRS {

private:
	explicit NavX();

	NavX(const NavX &);

	NavX &operator=(const NavX &);

public:
	static NavX &getInstance() {
		static NavX singletonInstance;
		return singletonInstance;
	}
};

#endif
