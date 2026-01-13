#ifndef WEB_HEADER_H
#define WEB_HEADER_H

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>ESP32 Control</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body { font-family: Arial; padding: 20px; }
.card { padding: 15px; margin-bottom: 20px; background: #e8e8e8; border-radius: 10px; }
</style>
</head>

<body>
<h2>ESP32 Control Panel</h2>

<div class="card">
  <h3>Sliders</h3>
  Slider 1: <input type="range" id="s1" min="50" max="255" value="0" oninput="sendData()"><br><br>
  Slider 2: <input type="range" id="s2" min="50" max="255" value="0" oninput="sendData()"><br><br>
  Slider 3: <input type="range" id="s3" min="50" max="255" value="0" oninput="sendData()"><br><br>
  Slider 4: <input type="range" id="s4" min="50" max="255" value="0" oninput="sendData()"><br><br>
</div>

<div class="card">
  <h3>Switches</h3>
  Switch 1: <input type="checkbox" id="w1" onchange="sendData()"><br><br>
  Switch 2: <input type="checkbox" id="w2" onchange="sendData()"><br><br>
  Switch 3: <input type="checkbox" id="w3" onchange="sendData()"><br><br>
  Switch 4: <input type="checkbox" id="w4" onchange="sendData()"><br><br>
</div>

<script>
function sendData() {
  let url = "/set?s1=" + document.getElementById("s1").value +
            "&s2=" + document.getElementById("s2").value +
            "&s3=" + document.getElementById("s3").value +
            "&s4=" + document.getElementById("s4").value +
            "&w1=" + (document.getElementById("w1").checked ? 1 : 0) +
            "&w2=" + (document.getElementById("w2").checked ? 1 : 0) +
            "&w3=" + (document.getElementById("w3").checked ? 1 : 0) +
            "&w4=" + (document.getElementById("w4").checked ? 1 : 0);

  fetch(url);
}

// Load current ESP32 values on page load
window.onload = function() {
  fetch("/state")
    .then(response => response.json())
    .then(data => {
      document.getElementById("s1").value = data.s1;
      document.getElementById("s2").value = data.s2;
      document.getElementById("s3").value = data.s3;
      document.getElementById("s4").value = data.s4;

      document.getElementById("w1").checked = data.w1;
      document.getElementById("w2").checked = data.w2;
      document.getElementById("w3").checked = data.w3;
      document.getElementById("w4").checked = data.w4;
    });
};
</script>


</body>
</html>
)=====";

#endif
