const selector = document.querySelector("#firmware");
const viewBtn = document.getElementById("viewConnections");
const infoBox = document.getElementById("connectionsInfo");

const conexiones = {
  "firmwares/prueba/manifest.json": `
    <b>🔌 Verificar ESP32</b><br>
    • GPIO 2 → LED de prueba<br>
    • GPIO 4 → Sensor digital<br>
    • 3.3V → Alimentación<br>
    • GND → Común
  `,
  "firmwares/jammer/manifest1.json": `
    <b>📡 Jammer con Botón</b><br>
    • GPIO 15 → Transmisor RF<br>
    • GPIO 18 → Botón físico<br>
    • GPIO 23 → LED indicador<br>
    • 5V / GND → Fuente externa<br>
    ⚠️ Evitá usar GPIO 0, 2 o 12 al inicio.
  `
};

// Mostrar botón según el firmware
selector.addEventListener("change", () => {
  const value = selector.value;
  if (conexiones[value]) {
    viewBtn.style.display = "inline-block";
    infoBox.style.display = "none";
  } else {
    viewBtn.style.display = "none";
    infoBox.style.display = "none";
  }
});

// Mostrar/ocultar conexiones
viewBtn.addEventListener("click", () => {
  const value = selector.value;
  if (infoBox.style.display === "none") {
    infoBox.innerHTML = conexiones[value] || "No hay información disponible.";
    infoBox.style.display = "block";
  } else {
    infoBox.style.display = "none";
  }
});
