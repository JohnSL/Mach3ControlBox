const int RED = 4;
const int GREEN = 2;
const int YELLOW = 3;
const int DebounceDelay = 50;

int lastState[10] = { 0 };
int finalState[10] = { 0 };
long lastTime[10] = { 0 };

void setup()
{
    pinMode(RED, INPUT_PULLUP);
    pinMode(GREEN, INPUT_PULLUP);
    pinMode(YELLOW, INPUT_PULLUP);
    Keyboard.begin();
}

void SendKey(int button, int sendState, char key, boolean useAlt = false)
{
    int oldState = lastState[button];
    int state = digitalRead(button);
    lastState[button] = state;

    if (state != oldState)
    {
        lastTime[button] = millis();
    }

    if (millis() - lastTime[button] < DebounceDelay || state == finalState[button])
        return;

    finalState[button] = state;
    if (state != sendState)
        return;

    if (useAlt)
        Keyboard.press(KEY_LEFT_ALT);
        
    Keyboard.press(key);
    Keyboard.releaseAll();
}

void loop()
{
    SendKey(RED, 1, 's', true);
    SendKey(GREEN, 0, 'r', true);
    SendKey(YELLOW, 0, ' ');
}

