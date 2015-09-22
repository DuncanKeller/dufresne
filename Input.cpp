#include "Input.h"


Input::Input(void)
{
}


Input::~Input(void)
{
}

void Input::Init()
{
	GameSystem::Init();

	for(int i = 0; i < MAX_GAMEPADS; i++)
	{
		gamepads[i].connected = false;
		gamepads[i].index = i;
	}

	
	int numjoys = SDL_NumJoysticks();

	// todo is there a way to tell which controller is which for xbox gamepads?
	for(int i = 0; i < numjoys; i++)
	{
		SDL_JoystickOpen(i);
		gamepads[i].connected = true;
	}
}

void Input::ClearButttonState(ButtonState* btn)
{
	btn->buttonDown = false;
	//btn->lastFrameDown = false;
	btn->tapped = false;
}

void Input::GamepadDisconnected(Gamepad *pad)
{
	// todo pause game / send message to game code
}

void Input::ClearGamepad(Gamepad* pad)
{
	ClearButttonState(&pad->a);
	ClearButttonState(&pad->b);
	ClearButttonState(&pad->dpadDown);
	ClearButttonState(&pad->dpadLeft);
	ClearButttonState(&pad->dpadRight);
	ClearButttonState(&pad->dpadUp);
	ClearButttonState(&pad->leftShoulder);
	ClearButttonState(&pad->leftStickButton);
	ClearButttonState(&pad->rightShoulder);
	ClearButttonState(&pad->rightStickButton);
	ClearButttonState(&pad->select);
	ClearButttonState(&pad->start);
	ClearButttonState(&pad->x);
	ClearButttonState(&pad->y);
	
	pad->leftStick.x = 0.f;
	pad->rightStick.x = 0.f;
	pad->leftStick.y = 0.f;
	pad->rightStick.y = 0.f;
	pad->leftTrigger = 0.f;
	pad->rightTrigger = 0.f;
}

void Input::ClearKeyboard(Keyboard* keys)
{
	for(int i = 0; i < MAX_KEYS_ON_KEYBOARD; i++)
	{
		ClearButttonState(&keys->buttonArray[i]);
	}
}

void Input::ClearMouse(Mouse* mouse)
{
	ClearButttonState(&mouse->leftButton);
	ClearButttonState(&mouse->middleButton);
	ClearButttonState(&mouse->rightButton);
	mouse->position.x = 0.f;
	mouse->position.y = 0.f;
	mouse->mouseWheel = 0;
}

void Input::ProcessButton(ButtonState* btn, bool buttonDown)
{
	btn->buttonDown = buttonDown;
	if(!btn->lastFrameDown)
		btn->tapped = true;
}

void Input::Update()
{
	GameSystem::Update();
	SDL_Event event;

	int deadzone = 3000;

	// todo clear keyboard and mouse
	for(int i = 0; i < MAX_GAMEPADS; i++)
	{
		ClearGamepad(&gamepads[i]);
	}

	ClearKeyboard(&keyboard);
	ClearMouse(&mouse);

	int jNum = -1;
	while( SDL_PollEvent( &event ) )
	{
		switch( event.type )
		{
			case SDL_JOYDEVICEADDED: // todo disconnect and reconnect shakey... needs testing
				gamepads[event.jdevice.which].connected = true;
			break;
			case SDL_JOYDEVICEREMOVED:
				gamepads[event.jdevice.which].connected = false;
				GamepadDisconnected(&gamepads[event.jdevice.which]);
			break;
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym )
                {
					case SDLK_BACKSPACE:
						ProcessButton(&keyboard.backspace, true);
					break;
					case SDLK_TAB:
						ProcessButton(&keyboard.tab, true);
					break;
					case SDLK_RETURN:
						ProcessButton(&keyboard.enter, true);
					break;
					case SDLK_PAUSE:
						ProcessButton(&keyboard.pauseBreak, true);
					break;
					case SDLK_ESCAPE:
						ProcessButton(&keyboard.esc, true);
					break;
					case SDLK_SPACE:
						ProcessButton(&keyboard.spacebar, true);
					break;
					case SDLK_QUOTEDBL:
						ProcessButton(&keyboard.quotes, true);
					break;
					case SDLK_QUOTE:
						ProcessButton(&keyboard.quotes, true);
					break;
					case SDLK_PLUS:
						ProcessButton(&keyboard.plus, true);
					break;
					case SDLK_EQUALS:
						ProcessButton(&keyboard.plus, true);
					break;
					case SDLK_MINUS:
						ProcessButton(&keyboard.minus, true);
					break;
					case SDLK_UNDERSCORE:
						ProcessButton(&keyboard.minus, true);
					break;
					case SDLK_SLASH:
						ProcessButton(&keyboard.forwardSlash, true);
					break;
					case SDLK_QUESTION:
						ProcessButton(&keyboard.forwardSlash, true);
					break;
					case SDLK_0:
						ProcessButton(&keyboard.n0, true);
					break;
					case SDLK_RIGHTPAREN:
						ProcessButton(&keyboard.n0, true);
					break;
					case SDLK_1:
						ProcessButton(&keyboard.n1, true);
					break;
					case SDLK_EXCLAIM:
						ProcessButton(&keyboard.n1, true);
					break;
					case SDLK_2:
						ProcessButton(&keyboard.n2, true);
					break;
					case SDLK_AT:
						ProcessButton(&keyboard.n2, true);
					break;
					case SDLK_3:
						ProcessButton(&keyboard.n3, true);
					break;
					case SDLK_HASH:
						ProcessButton(&keyboard.n3, true);
					break;
					case SDLK_4:
						ProcessButton(&keyboard.n4, true);
					break;
					case SDLK_DOLLAR:
						ProcessButton(&keyboard.n4, true);
					break;
					case SDLK_5:
						ProcessButton(&keyboard.n5, true);
					break;
					case SDLK_PERCENT:
						ProcessButton(&keyboard.n5, true);
					break;
					case SDLK_6:
						ProcessButton(&keyboard.n6, true);
					break;
					case SDLK_CARET:
						ProcessButton(&keyboard.n6, true);
					break;
					case SDLK_7:
						ProcessButton(&keyboard.n7, true);
					break;
					case SDLK_AMPERSAND:
						ProcessButton(&keyboard.n7, true);
					break;
					case SDLK_8:
						ProcessButton(&keyboard.n8, true);
					break;
					case SDLK_ASTERISK:
						ProcessButton(&keyboard.n8, true);
					break;
					case SDLK_9:
						ProcessButton(&keyboard.n9, true);
					break;
					case SDLK_LEFTPAREN:
						ProcessButton(&keyboard.n9, true);
					break;
					case SDLK_COLON:
						ProcessButton(&keyboard.semicolon, true);
					break;
					case SDLK_SEMICOLON:
						ProcessButton(&keyboard.semicolon, true);
					break;
					case SDLK_LESS:
						ProcessButton(&keyboard.lessThan, true);
					break;
					case SDLK_COMMA:
						ProcessButton(&keyboard.lessThan, true);
					break;
					case SDLK_GREATER:
						ProcessButton(&keyboard.greaterThan, true);
					break;
					case SDLK_PERIOD:
						ProcessButton(&keyboard.greaterThan, true);
					break;
					case SDLK_LEFTBRACKET:
						ProcessButton(&keyboard.leftBracket, true);
					break;
					case SDLK_BACKSLASH:
						ProcessButton(&keyboard.backslash, true);
					break;
					case SDLK_RIGHTBRACKET:
						ProcessButton(&keyboard.rightBracket, true);
					break;
					case SDLK_BACKQUOTE:
						ProcessButton(&keyboard.tilde, true);
					break;
					case SDLK_a:
						ProcessButton(&keyboard.a, true);
					break;
					case SDLK_b:
						ProcessButton(&keyboard.b, true);
					break;
					case SDLK_c:
						ProcessButton(&keyboard.c, true);
					break;
					case SDLK_d:
						ProcessButton(&keyboard.d, true);
					break;
					case SDLK_e:
						ProcessButton(&keyboard.e, true);
					break;
					case SDLK_f:
						ProcessButton(&keyboard.f, true);
					break;
					case SDLK_g:
						ProcessButton(&keyboard.g, true);
					break;
					case SDLK_h:
						ProcessButton(&keyboard.h, true);
					break;
					case SDLK_i:
						ProcessButton(&keyboard.i, true);
					break;
					case SDLK_j:
						ProcessButton(&keyboard.j, true);
					break;
					case SDLK_k:
						ProcessButton(&keyboard.k, true);
					break;
					case SDLK_l:
						ProcessButton(&keyboard.l, true);
					break;
					case SDLK_m:
						ProcessButton(&keyboard.m, true);
					break;
					case SDLK_n:
						ProcessButton(&keyboard.n, true);
					break;
					case SDLK_o:
						ProcessButton(&keyboard.o, true);
					break;
					case SDLK_p:
						ProcessButton(&keyboard.p, true);
					break;
					case SDLK_q:
						ProcessButton(&keyboard.q, true);
					break;
					case SDLK_r:
						ProcessButton(&keyboard.r, true);
					break;
					case SDLK_s:
						ProcessButton(&keyboard.s, true);
					break;
					case SDLK_t:
						ProcessButton(&keyboard.t, true);
					break;
					case SDLK_u:
						ProcessButton(&keyboard.u, true);
					break;
					case SDLK_v:
						ProcessButton(&keyboard.v, true);
					break;
					case SDLK_w:
						ProcessButton(&keyboard.w, true);
					break;
					case SDLK_x:
						ProcessButton(&keyboard.x, true);
					break;
					case SDLK_y:
						ProcessButton(&keyboard.y, true);
					break;
					case SDLK_z:
						ProcessButton(&keyboard.z, true);
					break;
					case SDLK_DELETE:
						ProcessButton(&keyboard.deleteKey, true);
					break;
					case SDLK_KP_0:
						ProcessButton(&keyboard.numpad0, true);
					break;
					case SDLK_KP_1:
						ProcessButton(&keyboard.numpad1, true);
					break;
					case SDLK_KP_2:
						ProcessButton(&keyboard.numpad2, true);
					break;
					case SDLK_KP_3:
						ProcessButton(&keyboard.numpad3, true);
					break;
					case SDLK_KP_4:
						ProcessButton(&keyboard.numpad4, true);
					break;
					case SDLK_KP_5:
						ProcessButton(&keyboard.numpad5, true);
					break;
					case SDLK_KP_6:
						ProcessButton(&keyboard.numpad6, true);
					break;
					case SDLK_KP_7:
						ProcessButton(&keyboard.numpad7, true);
					break;
					case SDLK_KP_8:
						ProcessButton(&keyboard.numpad8, true);
					break;
					case SDLK_KP_9:
						ProcessButton(&keyboard.numpad9, true);
					break;
					case SDLK_KP_PERIOD:
						ProcessButton(&keyboard.numpadDecimal, true);
					break;
					case SDLK_KP_DIVIDE:
						ProcessButton(&keyboard.numpadSlash, true);
					break;
					case SDLK_KP_MULTIPLY:
						ProcessButton(&keyboard.numpadAsterisk, true);
					break;
					case SDLK_KP_MINUS:
						ProcessButton(&keyboard.numpadMinus, true);
					break;
					case SDLK_KP_PLUS:
						ProcessButton(&keyboard.numpadPlus, true);
					break;
					case SDLK_KP_ENTER:
						ProcessButton(&keyboard.numpadEnter, true);
					break;
					case SDLK_UP:
						ProcessButton(&keyboard.arrowUp, true);
					break;
					case SDLK_DOWN:
						ProcessButton(&keyboard.arrowDown, true);
					break;
					case SDLK_RIGHT:
						ProcessButton(&keyboard.arrowRight, true);
					break;
					case SDLK_LEFT:
						ProcessButton(&keyboard.arrowLeft, true);
					break;
					case SDLK_INSERT:
						ProcessButton(&keyboard.insert, true);
					break;
					case SDLK_HOME:
						ProcessButton(&keyboard.home, true);
					break;
					case SDLK_END:
						ProcessButton(&keyboard.end, true);
					break;
					case SDLK_PAGEUP:
						ProcessButton(&keyboard.pgUp, true);
					break;
					case SDLK_PAGEDOWN:
						ProcessButton(&keyboard.pgDown, true);
					break;
					case SDLK_F1:
						ProcessButton(&keyboard.f1, true);
					break;
					case SDLK_F2:
						ProcessButton(&keyboard.f2, true);
					break;
					case SDLK_F3:
						ProcessButton(&keyboard.f3, true);
					break;
					case SDLK_F4:
						ProcessButton(&keyboard.f4, true);
					break;
					case SDLK_F5:
						ProcessButton(&keyboard.f5, true);
					break;
					case SDLK_F6:
						ProcessButton(&keyboard.f6, true);
					break;
					case SDLK_F7:
						ProcessButton(&keyboard.f7, true);
					break;
					case SDLK_F8:
						ProcessButton(&keyboard.f8, true);
					break;
					case SDLK_F9:
						ProcessButton(&keyboard.f9, true);
					break;
					case SDLK_F10:
						ProcessButton(&keyboard.f10, true);
					break;
					case SDLK_F11:
						ProcessButton(&keyboard.f11, true);
					break;
					case SDLK_F12:
						ProcessButton(&keyboard.f12, true);
					break;
					case SDLK_NUMLOCKCLEAR:
						ProcessButton(&keyboard.numlock, true);
					break;
					case SDLK_CAPSLOCK:
						ProcessButton(&keyboard.capsLock, true);
					break;
					case SDLK_SCROLLLOCK:
						ProcessButton(&keyboard.scrLk, true);
					break;
					case SDLK_RSHIFT:
						ProcessButton(&keyboard.rightShift, true);
					break;
					case SDLK_LSHIFT:
						ProcessButton(&keyboard.leftShift, true);
					break;
					case SDLK_RCTRL:
						ProcessButton(&keyboard.rightCtrl, true);
					break;
					case SDLK_LCTRL:
						ProcessButton(&keyboard.leftCtrl, true);
					break;
					case SDLK_RALT:
						ProcessButton(&keyboard.rightAlt, true);
					break;
					case SDLK_LALT:
						ProcessButton(&keyboard.leftAlt, true);
					break;
					case SDLK_LGUI:
						ProcessButton(&keyboard.windowsKey, true);
					break;
					case SDLK_RGUI:
						ProcessButton(&keyboard.windowsKey, true);
					break;
					case SDLK_PRINTSCREEN:
						ProcessButton(&keyboard.prtScrn, true);
					break;
				}
				break;
			case SDL_JOYAXISMOTION: 
				jNum = event.jaxis.which;
				if ( ( event.jaxis.value < -deadzone ) || (event.jaxis.value > deadzone ) ) 
				{
					if( event.jaxis.axis == 0)  // left xaaxis
					{
						gamepads[jNum].leftStick.x = event.jaxis.value / (float)MAX_JOY_AXIS;
					}
					else if( event.jaxis.axis == 1) // left yaxis
					{
						gamepads[jNum].leftStick.y = event.jaxis.value / (float)MAX_JOY_AXIS;
					}
					else if( event.jaxis.axis == 2) // right yaxis
					{
						gamepads[jNum].rightStick.x = event.jaxis.value / (float)MAX_JOY_AXIS;
					}
					else if( event.jaxis.axis == 3) // right yaxis
					{
						gamepads[jNum].rightStick.y = event.jaxis.value / (float)MAX_JOY_AXIS;
					}
					else if( event.jaxis.axis == 4) // left trig
					{
						gamepads[jNum].leftTrigger = event.jaxis.value / (float)MAX_JOY_AXIS;
					}
					else if( event.jaxis.axis == 5) // right trig
					{
						gamepads[jNum].rightTrigger = event.jaxis.value / (float)MAX_JOY_AXIS;
					}
				}
				break;
			case SDL_JOYBUTTONDOWN: 
			{
				jNum = event.jbutton.which;
				//if ( event.jbutton.button == 0 ) 
				int buttNum = event.jbutton.button;
				switch(buttNum)
				{
					case 10:
						ProcessButton(&gamepads[jNum].a, true);
						break;
					case 11:
						ProcessButton(&gamepads[jNum].b, true);
						break;
					case 12:
						ProcessButton(&gamepads[jNum].x, true);
						break;
					case 13:
						ProcessButton(&gamepads[jNum].y, true);
						break;
					case 0:
						ProcessButton(&gamepads[jNum].dpadUp, true);
						break;
					case 1:
						ProcessButton(&gamepads[jNum].dpadUp, true);
						break;
					case 2:
						ProcessButton(&gamepads[jNum].dpadLeft, true);
						break;
					case 3:
						ProcessButton(&gamepads[jNum].dpadRight, true);
						break;
					case 4:
						ProcessButton(&gamepads[jNum].start, true);
						break;
					case 5:
						ProcessButton(&gamepads[jNum].select, true);
						break;
					case 8:
						ProcessButton(&gamepads[jNum].leftShoulder, true);
						break;
					case 9:
						ProcessButton(&gamepads[jNum].rightShoulder, true);
						break;
					case 6:
						ProcessButton(&gamepads[jNum].leftStickButton, true);
						break;
					case 7:
						ProcessButton(&gamepads[jNum].rightStickButton, true);
						break;
				}
			}
			break;
			case SDL_MOUSEBUTTONDOWN: 
				switch(event.button.button)
				{
					case SDL_BUTTON_LEFT:
						ProcessButton(&mouse.leftButton, true);
						break;
					case SDL_BUTTON_RIGHT:
						ProcessButton(&mouse.rightButton, true);
						break;
					case SDL_BUTTON_MIDDLE:
						ProcessButton(&mouse.middleButton, true);
						break;
				}
			break;
			case SDL_MOUSEMOTION:
				mouse.position.x = event.motion.xrel;
				mouse.position.y = event.motion.yrel;
			break;

		}
	}

	// set previous inputs
	for(int i = 0; i < MAX_GAMEPADS; i++)
	{
		gamepads[jNum].a.lastFrameDown = gamepads[jNum].a.buttonDown;
		gamepads[jNum].b.lastFrameDown = gamepads[jNum].b.buttonDown;
		gamepads[jNum].x.lastFrameDown = gamepads[jNum].x.buttonDown;
		gamepads[jNum].y.lastFrameDown = gamepads[jNum].y.buttonDown;
		gamepads[jNum].start.lastFrameDown = gamepads[jNum].start.buttonDown;
		gamepads[jNum].select.lastFrameDown = gamepads[jNum].select.buttonDown;
		gamepads[jNum].leftShoulder.lastFrameDown = gamepads[jNum].leftShoulder.buttonDown;
		gamepads[jNum].rightShoulder.lastFrameDown = gamepads[jNum].rightShoulder.buttonDown;
		gamepads[jNum].leftStickButton.lastFrameDown = gamepads[jNum].leftStickButton.buttonDown;
		gamepads[jNum].rightStickButton.lastFrameDown = gamepads[jNum].rightStickButton.buttonDown;
		gamepads[jNum].dpadUp.lastFrameDown = gamepads[jNum].dpadUp.buttonDown;
		gamepads[jNum].dpadDown.lastFrameDown = gamepads[jNum].dpadDown.buttonDown;
		gamepads[jNum].dpadLeft.lastFrameDown = gamepads[jNum].dpadLeft.buttonDown;
		gamepads[jNum].dpadRight.lastFrameDown = gamepads[jNum].dpadRight.buttonDown;
	}
	for(int i= 0; i < MAX_KEYS_ON_KEYBOARD; i++)
	{
		keyboard.buttonArray[i].lastFrameDown = keyboard.buttonArray[i].buttonDown;
	}
	mouse.leftButton.lastFrameDown = mouse.leftButton.buttonDown;
	mouse.rightButton.lastFrameDown = mouse.rightButton.buttonDown;
	mouse.middleButton.lastFrameDown = mouse.middleButton.buttonDown;

}

// todo
// poll for connect joytsticks and enable or disable them as needed