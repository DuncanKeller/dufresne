#pragma once

#include "../Core/STDUNC.h"
#include "SDL.h"
#include "../Entity/Entity.h"

const int MAX_KEYS_ON_KEYBOARD = 106;

struct ButtonState
{
	bool buttonDown;
	bool lastFrameDown;
	bool tapped;
};

struct Gamepad
{
	bool connected;
	unsigned int index;

	float leftTrigger;
	float rightTrigger;

	vec2 leftStick;
	vec2 rightStick;
	
	ButtonState leftStickButton;
	ButtonState rightStickButton;
	
	ButtonState dpadUp;
	ButtonState dpadDown;
	ButtonState dpadLeft;
	ButtonState dpadRight;

	
	ButtonState a;
	ButtonState b;
	ButtonState x;
	ButtonState y;
	
	ButtonState start;
	ButtonState select;
	
	ButtonState leftShoulder;
	ButtonState rightShoulder;
};

struct Keyboard
{
	union
	{
		ButtonState buttonArray[MAX_KEYS_ON_KEYBOARD];
		struct
		{
			ButtonState esc;
			ButtonState f1;
			ButtonState f2;
			ButtonState f3; 
			ButtonState f4;
			ButtonState f5;
			ButtonState f6;
			ButtonState f7;
			ButtonState f8;
			ButtonState f9;
			ButtonState f10;
			ButtonState f11;
			ButtonState f12;
			ButtonState fLock;
			ButtonState prtScrn;
			ButtonState scrLk;
			ButtonState pauseBreak;

			ButtonState insert;
			ButtonState home;
			ButtonState pgUp;
			ButtonState pgDown;
			ButtonState deleteKey;
			ButtonState end;
	
			ButtonState tilde;
			ButtonState n1;
			ButtonState n2;
			ButtonState n3;
			ButtonState n4;
			ButtonState n5;
			ButtonState n6;
			ButtonState n7;
			ButtonState n8;
			ButtonState n9;
			ButtonState n0;
			ButtonState minus;
			ButtonState plus;
			ButtonState backspace;

			ButtonState tab;
			ButtonState q;
			ButtonState w;
			ButtonState e;
			ButtonState r;
			ButtonState t;
			ButtonState y;
			ButtonState u;
			ButtonState i;
			ButtonState o;
			ButtonState p;
			ButtonState leftBracket;
			ButtonState rightBracket;
			ButtonState backslash;

			ButtonState capsLock;
			ButtonState a;
			ButtonState s;
			ButtonState d;
			ButtonState f;
			ButtonState g;
			ButtonState h;
			ButtonState j;
			ButtonState k;
			ButtonState l;
			ButtonState semicolon;
			ButtonState quotes;
			ButtonState enter;

			ButtonState leftShift;
			ButtonState z;
			ButtonState x;
			ButtonState c;
			ButtonState v;
			ButtonState b;
			ButtonState n;
			ButtonState m;
			ButtonState lessThan;
			ButtonState greaterThan;
			ButtonState forwardSlash;
			ButtonState rightShift;

			ButtonState leftCtrl;
			ButtonState windowsKey;
			ButtonState leftAlt;
			ButtonState spacebar;
			ButtonState rightAlt;
			ButtonState rightCtrl;

			ButtonState arrowUp;
			ButtonState arrowDown;
			ButtonState arrowLeft;
			ButtonState arrowRight;

			ButtonState specialEquals;
			ButtonState specialLeftParen;
			ButtonState specialRightParen;

			ButtonState numlock;
			ButtonState numpadSlash;
			ButtonState numpadAsterisk;
			ButtonState numpadMinus;
			ButtonState numpadPlus;
			ButtonState numpadEnter;
			ButtonState numpadDecimal;
			ButtonState numpad0;
			ButtonState numpad1;
			ButtonState numpad2;
			ButtonState numpad3;
			ButtonState numpad4;
			ButtonState numpad5;
			ButtonState numpad6;
			ButtonState numpad7;
			ButtonState numpad8;
			ButtonState numpad9;
		};
	};
};

struct Mouse
{
	ButtonState leftButton;
	ButtonState middleButton;
	ButtonState rightButton;
	
	vec2 position;
	int mouseWheel;
};

class Input :
	public Entity
{
public:
	static const int MAX_JOY_AXIS = 32767;
	static const int MAX_GAMEPADS = 4;
	Gamepad gamepads[MAX_GAMEPADS]; // todo better solution than just [4] gamepads?
	Keyboard keyboard;
	Mouse mouse;

	Input(void);
	virtual ~Input(void);
	void ClearButttonState(ButtonState*);
	void ClearGamepad(Gamepad*);
	void ClearKeyboard(Keyboard*);
	void ClearMouse(Mouse*);

	void GamepadDisconnected(Gamepad*);

	void HandleKeyboard(SDL_Keycode keycode, bool pressed);
	void ProcessButton(ButtonState*, bool);

	virtual void Init();
	virtual void Update();
};

extern Input input;

//todo
// seems to act like text editor, with pauses when holding key... what's up wit dat?