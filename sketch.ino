const int	diodaON = 12;
const int	diodaTrybR = 11;
const int	diodaTrybG = 10;
const int	diodaTrybB = 9;
const int	diodaMoc1 = 8;
const int	diodaMoc2 = 7;
const int	diodaMoc3 = 6;
const int	diodaMoc4 = 5;
const int	peltierGrzanie = 4;
const int	mocWentylatora = 3;
const int	peltierChlodzenie = 2;

const int	sensorPin1 = A0; // Pin do podłączenia pierwszego czujnika
const int	buttonPower = A1;
const int	buttonMode = A2;
const int	buttonMoc = A3;

int			currentPower = 1; // Aktualna moc, domyślnie 1
int			currentMode = 1;
bool		devicePOWER = false;

int			previousPowerButtonState = LOW;
int			previousModeButtonState = LOW;
int			previousMocButtonState = LOW;

// Pin do sterowania pierwszym przekaźnikiem

void	setup(void)
{
	// put your setup code here, to run once:
	pinMode(diodaON, OUTPUT);
	pinMode(diodaTrybR, OUTPUT);
	pinMode(diodaTrybG, OUTPUT);
	pinMode(diodaTrybB, OUTPUT);
	pinMode(diodaMoc1, OUTPUT);
	pinMode(diodaMoc2, OUTPUT);
	pinMode(diodaMoc3, OUTPUT);
	pinMode(diodaMoc4, OUTPUT);
	pinMode(peltierGrzanie, OUTPUT);
	pinMode(mocWentylatora, OUTPUT);
	pinMode(peltierChlodzenie, OUTPUT);
	pinMode(sensorPin1, INPUT);
	pinMode(buttonPower, INPUT_PULLUP);
	pinMode(buttonMode, INPUT_PULLUP);
	pinMode(buttonMoc, INPUT_PULLUP);
	int currentPower = 0; // Aktualna moc, domyślnie 1
  int currentMode = 1;
}

void	loop(void)
{
	int	powerButtonState;
	int	modeButtonState;
	int	mocButtonLevel;

	// Odczytaj stan przycisków
	powerButtonState = digitalRead(buttonPower);
	modeButtonState = digitalRead(buttonMode);
	mocButtonLevel = digitalRead(buttonMoc);
	// Sprawdź, czy stan przycisku uległ zmianie
	if (powerButtonState == LOW)
		// Wlacznie/wylacznie urzadzenia jesli przycisk nacisniety
	{
		// Odwróć stan urządzenia (ON/OFF)
		devicePOWER = !devicePOWER;
		digitalWrite(diodaON, devicePOWER ? HIGH : LOW);
		if (devicePOWER)
		{
			currentPower = 1;
			setPowerIndicators(currentPower);
      currentMode = 2;
      setModeIndicator(currentMode);
		}
		// Poczekaj, aby uniknąć efektu drgania przycisku
		delay(100);
	}
	if (devicePOWER) // Jesli wlaczone obsluguj przyciski
	{
		if (modeButtonState == LOW)// Jesli przycisk trybu zmienil stan to zmien tryb
		{
			currentMode++;
			if (currentMode > 2)
			{
				currentMode = 1;
			}
			setModeIndicator(currentMode);
      delay(100);
		}
		if (mocButtonLevel == LOW)
			// Jesli przycisk mocy nacisniety to zmien moc
		{
			// Przycisk mocy został naciśnięty
			// Inkrementuj aktualną moc
			currentPower++;
			delay(100);
			// Jeśli moc osiągnie 5, wróć do 1
			if (currentPower > 4)
			{
				currentPower = 1;
			}
			setPowerIndicators(currentPower);
			// Dodaj kod obsługi dla zmienionej mocy
			// Na przykład, ustaw diody mocy zgodnie z aktualną mocą
		}
	}
	else // Jesli wylaczone to wylacz wszystko
	{
		currentPower = 0;
    setModeIndicator(currentMode = 0);
		setPowerIndicators(currentPower);

	}
	// Poczekaj, aby uniknąć efektu drgania przycisku
	delay(100);
}

void	setPowerIndicators(int currentPower)
{
	digitalWrite(diodaMoc1, LOW);
	digitalWrite(diodaMoc2, LOW);
	digitalWrite(diodaMoc3, LOW);
	digitalWrite(diodaMoc4, LOW);
	// Włącz odpowiednie diody mocy w zależności od wartości currentPower
	switch (currentPower)
	{
	case 1:
		digitalWrite(diodaMoc1, HIGH);
		break ;
	case 2:
		digitalWrite(diodaMoc1, HIGH);
		digitalWrite(diodaMoc2, HIGH);
		break ;
	case 3:
		digitalWrite(diodaMoc1, HIGH);
		digitalWrite(diodaMoc2, HIGH);
		digitalWrite(diodaMoc3, HIGH);
		break ;
	case 4:
		digitalWrite(diodaMoc1, HIGH);
		digitalWrite(diodaMoc2, HIGH);
		digitalWrite(diodaMoc3, HIGH);
		digitalWrite(diodaMoc4, HIGH);
		break ;
	default:
		// Jeśli przez jakiś przypadek currentPower nie jest w zakresie 1-4
		// tutaj możesz dodać kod obsługi
		break ;
	}
}

void	setModeIndicator(int currentMode)
{
	digitalWrite(diodaTrybR, LOW);
	digitalWrite(diodaTrybG, LOW);
	digitalWrite(diodaTrybB, LOW);

	// Włącz odpowiednie diody mocy w zależności od wartości currentPower
	switch (currentMode)
	{
	case 1:
		digitalWrite(diodaTrybR, HIGH);
		break ;
	case 2:
		digitalWrite(diodaTrybB, HIGH);
		break ;

	default:
		// Jeśli przez jakiś przypadek currentPower nie jest w zakresie 1-4
		// tutaj możesz dodać kod obsługi
		break ;
	}
}














			/* 			// Przycisk trybu zmienił stan
						if ()
						{
							// Przycisk został wciśnięty
						}
						else
						{
						previousModeButtonState = modeButtonState;
						} */
