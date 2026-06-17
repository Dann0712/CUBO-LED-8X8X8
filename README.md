# CUBO-LED-8X8X8
# Cubo LED 8x8x8 + Monitor OLED (Simulación en Proteus)

¡Bienvenido a este proyecto de simulación electrónica! Este repositorio contiene todos los archivos necesarios para ejecutar y visualizar el funcionamiento de un cubo LED tridimensional de 8x8x8 controlado por un Arduino. Además, incluye un monitor OLED que muestra estadísticas en tiempo real sobre las animaciones ejecutadas.

El proyecto está diseñado para ser **"Plug and Play"**: clona el repositorio, carga el código y observa la simulación en acción.

---

## 🚀 ¿Qué hace este proyecto?
El sistema simula el circuito electrónico y la lógica de programación para controlar un cubo de 512 LEDs (8 capas de 64 LEDs cada una) mediante la técnica de multiplexación masiva. El microcontrolador ejecuta de manera cíclica **5 rutinas o patrones de animación diferentes**, cambiando automáticamente cada 5 segundos.

📺 **Monitoreo en Vivo:** Mientras el cubo brilla, una pantalla OLED muestra de manera dinámica la rutina actual en ejecución, los segundos transcurridos y la cuenta regresiva para el siguiente cambio de animación.

---

## 🛠️ Componentes del Circuito (Simulados)
El diseño en Proteus está estructurado con los siguientes elementos de hardware:
* **Microcontrolador:** Arduino (Uno o compatible) como cerebro del sistema.
* **Control de Capas (Z):** Circuito Integrado Darlington **ULN2803** conectado a los pines digitales `2` al `9` para conmutar la potencia de los niveles.
* **Control de Filas/Columnas (X-Y):** **Registros de desplazamiento** en cascada (conectados a los pines `10`, `11` y `12`) para expandir las salidas digitales mediante `shiftOut`.
* **Interfaz Visual:** Pantalla **OLED SSD1306** (128x64) comunicada por protocolo I2C (`Wire`).
* **Matriz:** 512 diodos LED interconectados en formato tridimensional.

---

## 🔄 Descripción de las Rutinas Integradas
Cada patrón visual dura **5000 ms (5 segundos)** y genera los siguientes efectos:
1. **Rutina 1 (Alternado):** Enciende los LEDs de forma intercalada simulando un patrón de tablero de ajedrez.
2. **Rutina 2 (Barrido por Filas):** Movimientos horizontales secuenciales fila por fila.
3. **Rutina 3 (Barrido por Columnas):** Movimientos verticales que dividen visualmente el cubo por bloques.
4. **Rutina 4 (Parpadeo de Capas):** Enciende y apaga niveles completos de manera intermitente.
5. **Rutina 5 (Efecto Aleatorio / Lluvia):** Genera destellos de luz al azar en todo el volumen del cubo usando la función `random()`.

---

## 📚 Librerías de Arduino Requeridas
Antes de compilar, asegúrate de tener instaladas las siguientes librerías desde el Gestor de Librerías del Arduino IDE:
* `Adafruit_GFX.h`
* `Adafruit_SSD1306.h`
* `Wire.h` (Librería nativa de Arduino)

---

## 🔧 Instrucciones de Ejecución Paso a Paso

1. **Descarga el Proyecto:** Descarga o clona este repositorio en tu ordenador.
2. **Prepara el Código:** Abre el archivo `.ino` en tu Arduino IDE, asegúrate de tener las librerías instaladas y compila el proyecto.
3. **Obtén el Archivo Binario:** 
   * En Arduino IDE, ve a *Programa* > *Exportar Binario Compilado*.
   * Esto generará un archivo `.hex` en la misma carpeta donde guardaste el código.
4. **Carga la Simulación:** Abre el archivo de diseño electrónico en **Proteus**.
5. **Vincula el Firmware:** Haz doble clic sobre la placa Arduino dentro de Proteus. En el campo *Program File*, haz clic en la carpeta y selecciona el archivo `.hex` generado en el paso anterior.
6. **¡Dale Play!** Presiona el botón de **Play (Ejecutar)** en la esquina inferior izquierda de Proteus y observa cómo el cubo cobra vida mientras la pantalla OLED mide los tiempos.
