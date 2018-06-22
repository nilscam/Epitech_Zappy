/*
** EPITECH PROJECT, 2018
** MyEventReceiver
** File description:
** MyEventReceiver
*/

#ifndef MYEVENTRECEIVER_HPP
#define MYEVENTRECEIVER_HPP

#include <irrlicht/irrlicht.h>

class MyEventReceiver : public irr::IEventReceiver
{
public:
	virtual bool OnEvent(const irr::SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT){
			// If mouse cursor moved
			if (event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN) {
				_isMouseClick = true;
			} else {
				_isMouseClick = false;
			}
		}
		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	virtual bool isMouseClick() const
	{
		return _isMouseClick;
	}

	MyEventReceiver()
	{
		for (irr::u32 i=0; i< irr::KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	bool _isMouseClick;
};

#endif //MYEVENTRECEIVER_HPP