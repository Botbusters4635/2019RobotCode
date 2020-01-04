//
// Created by Abiel on 9/11/18.
//

#ifndef BOTBUSTERSREBIRTH_TOGGLEBUTTON_H
#define BOTBUSTERSREBIRTH_TOGGLEBUTTON_H

#include "EctoButton.h"

class ToggleButton : public EctoButton {
public:
    ToggleButton(bool defaultState = false);

protected:
	void calculateOutput() override;

private:
	bool previousStatus = false;
};


#endif //BOTBUSTERSREBIRTH_TOGGLEBUTTON_H
