#ifndef WEB_HEADER_H
#define WEB_HEADER_H

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>Smart Lighting Control</title>
<meta name="viewport" content="width=device-width, initial-scale=1">

<style>
:root {
  --bg: #2f3237;
  --card: #f4f4f4;
  --accent: #3aa0ff;
  --text-dark: #333;
}

body {
  margin: 0;
  font-family: Arial, sans-serif;
  background: var(--bg);
  color: white;
}

.header {
  padding: 20px;
  font-size: 22px;
  font-weight: bold;
}

.grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(180px, 1fr));
  gap: 15px;
  padding: 20px;
}

.card {
  background: var(--card);
  color: var(--text-dark);
  border-radius: 14px;
  padding: 15px;
}

.card h3 {
  margin: 0 0 10px;
  font-size: 16px;
}

/* Toggle switch */
.switch {
  position: relative;
  display: inline-block;
  width: 46px;
  height: 24px;
}

.switch input {
  opacity: 0;
}

.slider-toggle {
  position: absolute;
  cursor: pointer;
  background: #ccc;
  border-radius: 24px;
  top: 0; left: 0; right: 0; bottom: 0;
  transition: 0.3s;
}

.slider-toggle:before {
  position: absolute;
  content: "";
  height: 18px;
  width: 18px;
  left: 3px;
  bottom: 3px;
  background: white;
  border-radius: 50%;
  transition: 0.3s;
}

input:checked + .slider-toggle {
  background: var(--accent);
}

input:checked + .slider-toggle:before {
  transform: translateX(22px);
}

/* Brightness slider */
input[type=range] {
  width: 100%;
  margin-top: 10px;
}

/* Footer */
.footer {
  background: var(--card);
  color: var(--text-dark);
  margin: 20px;
  padding: 20px;
  border-radius: 14px;
}

button {
  background: var(--accent);
  border: none;
  color: white;
  padding: 10px 20px;
  border-radius: 8px;
  font-size: 14px;
  cursor: pointer;
}
</style>
</head>

<body>

<div class="header">Smart Lighting Control</div>

<div class="grid">
  <!-- LED 1 -->
  <div class="card">
    <h3>LED 1</h3>
    <label class="switch">
      <input type="checkbox" id="w1" onchange="sendData()">
      <span class="slider-toggle"></span>
    </label>
    <input type="range" id="s1" min="10" max="255" oninput="sendData()">
  </div>

  <!-- LED 2 -->
  <div class="card">
    <h3>LED 2</h3>
    <label class="switch">
      <input type="checkbox" id="w2" onchange="sendData()">
      <span class="slider-toggle"></span>
    </label>
    <input type="range" id="s2" min="10" max="255" oninput="sendData()">
  </div>

  <!-- LED 3 -->
  <div class="card">
    <h3>LED 3</h3>
    <label class="switch">
      <input type="checkbox" id="w3" onchange="sendData()">
      <span class="slider-toggle"></span>
    </label>
    <input type="range" id="s3" min="10" max="255" oninput="sendData()">
  </div>

  <!-- LED 4 -->
  <div class="card">
    <h3>LED 4</h3>
    <label class="switch">
      <input type="checkbox" id="w4" onchange="sendData()">
      <span class="slider-toggle"></span>
    </label>
    <input type="range" id="s4" min="10" max="255" oninput="sendData()">
  </div>
</div>

<div class="footer">
  <button onclick="allOff()">MASTER ON / OFF</button>
  <br><br>
  Master Brightness
  <input type="range" min="10" max="255" oninput="masterBrightness(this.value)">
</div>

<script>
function sendData() {
  let url = "/set?s1=" + s1.value +
            "&s2=" + s2.value +
            "&s3=" + s3.value +
            "&s4=" + s4.value +
            "&w1=" + (w1.checked ? 1 : 0) +
            "&w2=" + (w2.checked ? 1 : 0) +
            "&w3=" + (w3.checked ? 1 : 0) +
            "&w4=" + (w4.checked ? 1 : 0);
  fetch(url);
}

function allOff() {
  [w1,w2,w3,w4].forEach(w => w.checked = false);
  sendData();
}

function masterBrightness(val) {
  [s1,s2,s3,s4].forEach(s => s.value = val);
  sendData();
}

window.onload = () => {
  fetch("/state")
    .then(r => r.json())
    .then(d => {
      s1.value=d.s1; s2.value=d.s2; s3.value=d.s3; s4.value=d.s4;
      w1.checked=d.w1; w2.checked=d.w2; w3.checked=d.w3; w4.checked=d.w4;
    });
};
</script>

</body>
</html>

)=====";

#endif
