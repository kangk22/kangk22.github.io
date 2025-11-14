const BAUD_RATE = 9600; // This should match the baud rate in your Arduino sketch

let port, connectBtn; // Declare global variables

function setup() {
  setupSerial(); // Run our serial setup function (below)

  // Create a canvas that is the size of our browser window.
  // windowWidth and windowHeight are p5 variables
  createCanvas(windowWidth, windowHeight);

  // p5 text settings. BOLD and CENTER are constants provided by p5.
  // See the "Typography" section in the p5 reference: https://p5js.org/reference/
  textFont("system-ui", 50);
  textStyle(BOLD);
  textAlign(CENTER, CENTER);
}

function draw() {
  angleMode(DEGREES);
  translate(windowWidth/2, windowHeight/2 -100);
  
  background(100, 240, 255);
  let rot = map(mouseX, 0, windowWidth, -180, 180);
  rotate(rot);
  fill('orange');
  strokeWeight(0);
  triangle(
    0, 
    75,
    0, 
    -75,
    150, 
    0
  );
  fill('yellow');
  circle(0, 180, 280);
  circle(0, 0, 200);

  fill('black');
  rect(0, 320, 10, 40);
  rect(0, 350, 80, 10);
  
  fill('white');
  strokeWeight(2);
  circle(10, -2, 75);
  strokeWeight(0);
  fill('lightgreen');
  circle(19, -2, 55);
  fill('black');
  circle(24, -2, 35);
  fill('white');
  circle(10, -5, 12);
}

function setupSerial() {
  port = createSerial();

  // Check to see if there are any ports we have used previously
  let usedPorts = usedSerialPorts();
  if (usedPorts.length > 0) {
    // If there are ports we've used, open the first one
    port.open(usedPorts[0], BAUD_RATE);
  }

  // create a connect button
  connectBtn = createButton("Connect to Arduino");
  connectBtn.position(5, 5); // Position the button in the top left of the screen.
  connectBtn.mouseClicked(onConnectButtonClicked); // When the button is clicked, run the onConnectButtonClicked function
}

function checkPort() {
  if (!port.opened()) {
    // If the port is not open, change button text
    connectBtn.html("Connect to Arduino");
    // Set background to gray
    background("gray");
    return false;
  } else {
    // Otherwise we are connected
    connectBtn.html("Disconnect");
    return true;
  }
}

function onConnectButtonClicked() {
  // When the connect button is clicked
  if (!port.opened()) {
    // If the port is not opened, we open it
    port.open(BAUD_RATE);
  } else {
    // Otherwise, we close it!
    port.close();
  }
}
