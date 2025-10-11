// Prueba básica de funcionamiento del ESP32
// Verifica conexión, carga de programa y puerto serie

void setup() {
  // Inicia el puerto serie a 115200 baudios
  Serial.begin(115200);
  delay(1000); // Espera un segundo para estabilizar
  Serial.println();
  Serial.println("✅ ESP32 funcionando correctamente!");
  Serial.println("Si lees este mensaje, la carga fue exitosa.");
  Serial.println("-------------------------------------------");
  Serial.println("Probando parpadeo de LED interno...");
  
  // El pin 2 suele tener un LED integrado (según el modelo)
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);  // LED encendido
  delay(500);
  digitalWrite(2, LOW);   // LED apagado
  delay(500);

  // Mensaje periódico por monitor serie
  Serial.println("ESP32 activo...");
}
