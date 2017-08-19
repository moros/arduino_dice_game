// Creation Crate Dice Game
// Push the button to roll the dice!

// Step1: define inputs/outputs and key variables
#define buttonPin 2
#define ledSet1 4
#define ledSet2 5
#define ledSet3 6
#define ledSet4 7

const unsigned long debounceDelay = 5;

// buttonState will determine if the button is on or off.
volatile int currentButtonState = LOW;
volatile int lastButtonState = LOW;
volatile boolean switchState = false;

void setup() {
	Serial.begin(9600);

	pinMode(ledSet1, OUTPUT);
	pinMode(ledSet2, OUTPUT);
	pinMode(ledSet3, OUTPUT);
	pinMode(ledSet4, OUTPUT);
	pinMode(buttonPin, INPUT);
	randomSeed(analogRead(0));

	attachInterrupt(0, changeSwitchStateIfNeeded, CHANGE);
}

void loop() {

	if (!switchState) {
		//Serial.println("button state is low.");
		return;
	}

	// here, we are rolling a number equal to 1 and less than 7 (1-6).
	int roll = random(1, 7);

	// each roll needs a certain combination of ledSets to turn on. 
	// fill in the blanks with the correct ledSets: ie, 'ledSet4'.
	switch (roll)
	{
		case 1:
			digitalWrite(ledSet3, HIGH);
			break;
		case 2:
			digitalWrite(ledSet1, HIGH);
			break;
		case 3:
			digitalWrite(ledSet1, HIGH);
			digitalWrite(ledSet3, HIGH);
			break;
		case 4:
			digitalWrite(ledSet2, HIGH);
			digitalWrite(ledSet4, HIGH);
			break;
		case 5:
			digitalWrite(ledSet2, HIGH);
			digitalWrite(ledSet3, HIGH);
			digitalWrite(ledSet4, HIGH);
			break;
		case 6:
			digitalWrite(ledSet1, HIGH);
			digitalWrite(ledSet2, HIGH);
			digitalWrite(ledSet4, HIGH);
			break;
	}

	delay(1500);
		
	digitalWrite(ledSet1, LOW);
	digitalWrite(ledSet2, LOW);
	digitalWrite(ledSet3, LOW);
	digitalWrite(ledSet4, LOW);

	delay(1500);
}

boolean debounce(int buttonPinValue, boolean last) {
	boolean current = digitalRead(buttonPinValue);
	if (last != current) {
		delay(debounceDelay);
		current = digitalRead(buttonPinValue);
	}

	return current;
}

void changeSwitchStateIfNeeded() {
	currentButtonState = debounce(buttonPin, lastButtonState);
	if (lastButtonState == LOW && currentButtonState == HIGH) {
		switchState = !switchState;
		Serial.println("switch state has changed.");
	}

	lastButtonState = currentButtonState;
}
