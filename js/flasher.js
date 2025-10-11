// === CONTROL DEL FLASHER ===
const btn = document.querySelector("#flashBtn");
const selector = document.querySelector("#firmware");
const status = document.querySelector("#status");
const progressBar = document.querySelector("#progress-bar");

selector.addEventListener("change", () => {
  btn.setAttribute("manifest", selector.value);
});
btn.setAttribute("manifest", selector.value);

btn.addEventListener("install-click", () => {
  status.textContent = "🔌 Conectando al ESP32...";
  progressBar.style.width = "10%";
});

btn.addEventListener("installing", () => {
  status.textContent = "⚙️ Flasheando firmware...";
  progressBar.style.width = "60%";
});

btn.addEventListener("install-complete", () => {
  status.textContent = "✅ Instalación completada con éxito!";
  progressBar.style.width = "100%";
});

btn.addEventListener("install-error", () => {
  status.textContent = "❌ Error durante la instalación. Revisá la conexión.";
  progressBar.style.width = "0%";
});

// === FONDO MATRIX ===
const canvas = document.getElementById("matrix");
const ctx = canvas.getContext("2d");
canvas.height = window.innerHeight;
canvas.width = window.innerWidth;

const binary = "01";
const fontSize = 16;
const columns = canvas.width / fontSize;
const drops = [];
for (let x = 0; x < columns; x++) drops[x] = 1;

function draw() {
  ctx.fillStyle = "rgba(0, 0, 0, 0.05)";
  ctx.fillRect(0, 0, canvas.width, canvas.height);
  ctx.fillStyle = "#00ff80";
  ctx.font = fontSize + "px monospace";

  for (let i = 0; i < drops.length; i++) {
    const text = binary[Math.floor(Math.random() * binary.length)];
    ctx.fillText(text, i * fontSize, drops[i] * fontSize);
    if (drops[i] * fontSize > canvas.height && Math.random() > 0.975) drops[i] = 0;
    drops[i]++;
  }
}

setInterval(draw, 33);
window.addEventListener("resize", () => {
  canvas.height = window.innerHeight;
  canvas.width = window.innerWidth;
});
