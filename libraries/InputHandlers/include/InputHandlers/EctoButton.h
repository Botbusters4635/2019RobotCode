//
// Created by Abiel on 9/11/18.
//

#ifndef BOTBUSTERSREBIRTH_ECTOBUTTON_H
#define BOTBUSTERSREBIRTH_ECTOBUTTON_H

#include <mutex>

class EctoButton {
public:
	/**
	 * Pass the raw button input to this
	 * @param status
	 */
	void updateStatus(bool status);

	/**
	 * Returns the processed input
	 * @return
	 */
	bool get() const;

protected:
	virtual void calculateOutput();

	bool inValue = false;
	bool outValue = false;

private:
	mutable std::mutex buttonMutex;
};

#endif //BOTBUSTERSREBIRTH_ECTOBUTTON_H
