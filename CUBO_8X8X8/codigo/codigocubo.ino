#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pines de control para los registros de desplazamiento
#define DATA_PIN 12
#define LATCH_PIN 10
#define CLOCK_PIN 11

// Pines para controlar las capas (a través del ULN2803)
int layerPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

// Matriz para definir las posiciones encendidas por capa
byte cube[8][8];

// Variables para rutinas
unsigned long lastUpdate;
const unsigned long routineDuration = 5000; // Duración de cada rutina en ms
int currentRoutine = 0;

void setup() {
  // Inicializar pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;) ; // Detener si la pantalla no está conectada
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();

  // Configurar pines como salida
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(layerPins[i], OUTPUT);
    digitalWrite(layerPins[i], LOW);
  }

  lastUpdate = millis();
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long elapsed = currentMillis - lastUpdate;

  if (elapsed >= routineDuration) {
    lastUpdate = currentMillis;
    currentRoutine = (currentRoutine + 1) % 5; // Cambiar rutina
  }

  displayRoutineInfo(elapsed);
  executeRoutine(currentRoutine);
}

// Muestra información en la pantalla OLED
void displayRoutineInfo(unsigned long elapsed) {
  display.clearDisplay();
  display.setCursor(0, 0);

  display.print("Rutina: ");
  display.println(currentRoutine + 1);

  display.print("Transcurrido: ");
  display.print(elapsed / 1000);
  display.println(" s");

  display.print("Restante: ");
  display.print((routineDuration - elapsed) / 1000);
  display.println(" s");

  display.display();
}

// Ejecuta la rutina correspondiente
void executeRoutine(int routine) {
  switch (routine) {
    case 0:
      routine1();
      break;
    case 1:
      routine2();
      break;
    case 2:
      routine3();
      break;
    case 3:
      routine4();
      break;
    case 4:
      routine5();
      break;
  }
}

void routine1() {
  clearCube();
  for (int z = 0; z < 8; z++) {
    for (int x = 0; x < 8; x++) {
      cube[z][x] = 0xAA; // Alternar LEDs encendidos
    }
    displayCube();
    delay(50);
  }
}

void routine2() {
  clearCube();
  for (int z = 0; z < 8; z++) {
    for (int x = 0; x < 8; x++) {
      cube[z][x] = (x % 2 == 0) ? 0xFF : 0x00; // Barrido por filas
    }
    displayCube();
    delay(50);
  }
}

void routine3() {
  clearCube();
  for (int z = 0; z < 8; z++) {
    for (int x = 0; x < 8; x++) {
      cube[z][x] = (z % 2 == 0) ? 0x0F : 0xF0; // Barrido por columnas
    }
    displayCube();
    delay(50);
  }
}

void routine4() {
  clearCube();
  for (int z = 0; z < 8; z++) {
    for (int x = 0; x < 8; x++) {
      cube[z][x] = 0xFF; // Encender completamente una capa
    }
    displayCube();
    delay(100);
    clearCube();
    displayCube();
    delay(100);
  }
}

void routine5() {
  clearCube();
  for (int z = 0; z < 8; z++) {
    for (int x = 0; x < 8; x++) {
      cube[z][x] = random(0, 256); // Encendido aleatorio
    }
    displayCube();
    delay(50);
  }
}

void displayCube() {
  for (int z = 0; z < 8; z++) {
    digitalWrite(layerPins[z], HIGH);
    for (int x = 0; x < 8; x++) {
      shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, cube[z][x]);
    }
    digitalWrite(LATCH_PIN, HIGH);
    digitalWrite(LATCH_PIN, LOW);
    delay(2);
    digitalWrite(layerPins[z], LOW);
  }
}

void clearCube() {
  for (int z = 0; z < 8; z++) {
    for (int x = 0; x < 8; x++) {
      cube[z][x] = 0;
    }
  }
}