#ifndef UI_INDEX_H
#define UI_INDEX_H

const char* html = R"html(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 WEB REMOTE</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css">
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
    <script async src="https://docs.opencv.org/master/opencv.js" type="text/javascript"></script>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Press+Start+2P&display=swap');

        :root {
            --primary-dark: #2D1B36;
            --secondary-dark: #1A0F20;
            --accent-purple: #6B2F8A;
            --highlight-purple: #8A3DAD;
            --text-light: #E0D6E4;
            --text-dark: #1A0F20;
            --detect-button: #9C27B0;
            --detect-button-hover: #BA68C8;
            --reset-button: #673AB7;
            --reset-button-hover: #7E57C2;
        }

        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }

        html, body {
            font-family: 'Press Start 2P', sans-serif;
            color: var(--text-light);
            margin: 0;
            background-color: var(--secondary-dark);
            min-height: 100vh;
        }

        h1 {
            font-size: clamp(1rem, 2.5vw, 1.4rem);
            color: var(--text-light);
            text-align: center;
            padding: 15px;
            background-color: var(--accent-purple);
            margin: 0;
        }

        h2 {
            color: var(--text-light);
            font-size: clamp(0.7rem, 2vw, 0.9rem);
            margin: 0 0 10px 0;
        }

        .topnav {
            background-color: var(--accent-purple);
            position: sticky;
            top: 0;
            z-index: 100;
        }

        .fun-mode {
            animation: pulse 1s infinite;
            box-shadow: 0px 0px 20px rgba(138, 61, 173, 0.4);
        }

        .container {
            margin: 15px auto;
            max-width: 1280px;
            width: 90%
        }

        @keyframes pulse {
            0%, 100% { opacity: 1; }
            50% { opacity: 0.5; }
        }

        .glow-on-hover:hover {
            box-shadow: 0 5px 15px rgba(107, 47, 138, 0.6), 0 5px 15px rgba(138, 61, 173, 0.4);
        }

        .tab a { color: var(--highlight-purple) !important; }
        ul.tabs { border-radius: 12px; }
        .tab a.active {
            background-color: var(--primary-dark) !important;
            color: var(--highlight-purple) !important;
        }
        .indicator { background-color: var(--highlight-purple) !important; }

        .control-card {
            background: linear-gradient(145deg, var(--primary-dark), var(--secondary-dark));
            border-radius: 12px;
            padding: 20px;
            margin-bottom: 20px;
            margin-top: 20px;
            box-shadow: 5px 5px 15px rgba(0, 0, 0, 0.6), -5px -5px 15px rgba(0, 0, 0, 0.3);
        }

        .joint-control {
            margin: inherit;
        }

        .joint-section {
            align-content: space-evenly;
        }

        .collection-item {
            border-radius: 12px;
            background-color: transparent !important;
            border-bottom: none !important;
            margin: 5px !important;
        }

        .collection {
            border: none;
        }

        .btn-floating, .btn {
            background-color: var(--detect-button);
            border-radius: 8px;
        }

        .btn:hover, .btn-floating:hover {
            background-color: var(--detect-button-hover);
        }

        .movement-grid {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 10px;
            max-width: 300px;
            margin: 20px auto;
        }

        .center-align i {
            color: var(--text-light);
        }

        .tooltip:hover::after {
            content: attr(data-tooltip);
            color: var(--text-light);
            background: var(--primary-dark);
            padding: 6px 10px;
            position: absolute;
            font-size: 0.8em;
            transform: translateY(-100%);
            white-space: nowrap;
        }

        .button-group {
        display: flex;
        flex-wrap: wrap;
        gap: 10px;
        justify-content: center;
    }

    .movement-btn {
        display: inline-flex;
        align-items: center;
        justify-content: center;
        gap: 8px;
        min-width: 120px;
        padding: 0 20px;
        /* height: 57px; */
    }

    .movement-btn i {
        margin: 0;
        font-size: 20px;
    }

    .movement-btn span {
        font-size: 14px;
    }

    button, input[type="button"] {
        font-family: 'Press Start 2P', sans-serif;
        color: var(--text-light);
        background-color: var(--accent-purple);
        padding: 12px 20px;
        border-radius: 5px;
        margin: 5px;
        font-size: clamp(0.6rem, 1.5vw, 0.8rem);
        border: none;
        cursor: pointer;
        transition: background-color 0.3s ease;
    }

    button:hover, input[type="button"]:hover {
        background-color: var(--highlight-purple);
    }
    </style>
</head>
<body>
    <div class="topnav">
        <h1>Robot Control Madness</h1>
    </div>
    <div class="container">
        <div class="row">
            <div class="col s12">
                <div class="nav-tabs">
                    <ul class="tabs">
                        <li class="tab col s4"><a class="active" href="#BodyControl">
                            <i class="material-icons left">directions_car</i> Body Control
                        </a></li>
                        <li class="tab col s4"><a href="#ArmControl">
                            <i class="material-icons left">build</i> Arm Control
                        </a></li>
                        <li class="tab col s4"><a href="#EyeControl">
                            <i class="material-icons left">visibility</i> Eye Control
                        </a></li>
                    </ul>
                </div>

                <div id="BodyControl">
                    <div class="control-card">
                        <h5 class="center-align">Movement Control</h5>
                        <div class="movement-grid">
                            <button class="btn-floating waves-effect waves-light" onclick="sendCommand('rl')">
                                <i class="material-icons">rotate_left</i>
                            </button>
                            <button class="btn-floating waves-effect waves-light" onclick="sendCommand('mv')">
                                <i class="material-icons">arrow_upward</i>
                            </button>
                            <button class="btn-floating waves-effect waves-light" onclick="sendCommand('rr')">
                                <i class="material-icons">rotate_right</i>
                            </button>

                            <button class="btn-floating waves-effect waves-light" onclick="sendCommand('lt')">
                                <i class="material-icons">arrow_back</i>
                            </button>
                            <button class="btn-floating waves-effect waves-light" onclick="sendCommand('st')">
                                <i class="material-icons">stop</i>
                            </button>
                            <button class="btn-floating waves-effect waves-light" onclick="sendCommand('rt')">
                                <i class="material-icons">arrow_forward</i>
                            </button>

                            <div></div>
                            <button class="btn-floating waves-effect waves-light" onclick="sendCommand('bk')">
                                <i class="material-icons">arrow_downward</i>
                            </button>
                            <div></div>
                        </div>

                        <div class="divider"></div>

                        <div class="speed-control center-align">
                            <h5>Speed Control</h5>
                            <p class="slider-label">Speed: <span id="speedValue">128</span></p>
                            <p class="range-field">
                                <input type="range" min="0" max="255" value="128"
                                    oninput="document.getElementById('speedValue').innerHTML = this.value"
                                    onchange="sendCommand('spd ' + this.value)" />
                            </p>
                        </div>

                        <div class="divider"></div>

                        <div class="center-align">
                            <h5>Obstacle Avoidance</h5>
                            <button class="btn waves-effect waves-light" onclick="sendCommand('oa on')">
                                <i class="material-icons left">security</i>Enable OA
                            </button>
                            <button class="btn waves-effect waves-light" onclick="sendCommand('oa off')">
                                <i class="material-icons left">security</i>Disable OA
                            </button>
                            <button class="btn waves-effect waves-light" onclick="sendCommand('oa nav')">
                                <i class="material-icons left">explore</i>Auto Navigate
                            </button>
                        </div>
                    </div>
                </div>

                <div id="ArmControl">
                    <div class="control-card">
                        <h5 class="center-align">Joint Control</h5>
                        <div class="joint-control">
                            <div class="joint-section">
                                <h6>Base</h6>
                                <button class="btn waves-effect waves-light" onclick="sendCommand('b -')">
                                    <i class="material-icons">arrow_back</i>
                                </button>
                                <button class="btn waves-effect waves-light" onclick="sendCommand('b +')">
                                    <i class="material-icons">arrow_forward</i>
                                </button>
                            </div>

                            <div class="joint-section">
                                <h6>Shoulder</h6>
                                <button class="btn waves-effect waves-light" onclick="sendCommand('s -')">
                                    <i class="material-icons">arrow_downward</i>
                                </button>
                                <button class="btn waves-effect waves-light" onclick="sendCommand('s +')">
                                    <i class="material-icons">arrow_upward</i>
                                </button>
                            </div>

                            <div class="joint-section">
                                <h6>Elbow</h6>
                                <button class="btn waves-effect waves-light" onclick="sendCommand('e -')">
                                    <i class="material-icons">arrow_downward</i>
                                </button>
                                <button class="btn waves-effect waves-light" onclick="sendCommand('e +')">
                                    <i class="material-icons">arrow_upward</i>
                                </button>
                            </div>

                            <div class="joint-section">
                                <h6>Gripper</h6>
                                <button class="btn waves-effect waves-light" onclick="sendCommand('g o')">
                                    <i class="material-icons">pan_tool</i> Open
                                </button>
                                <button class="btn waves-effect waves-light" onclick="sendCommand('g c')">
                                    <i class="material-icons">power_settings_new</i> Close
                                </button>
                            </div>
                        </div>

                        <div class="divider"></div>

                        <div class="center-align">
                            <h5>Pre-defined Movements</h5>
                            <div class="collection">
                                <div class="collection-item button-group">
                                    <button class="btn waves-effect waves-light movement-btn" onclick="sendCommand('m h')">
                                        <i class="material-icons">home</i>
                                        <span>Home</span>
                                    </button>
                                    <button class="btn waves-effect waves-light movement-btn" onclick="sendCommand('m s')">
                                        <i class="material-icons">search</i>
                                        <span>Scan</span>
                                    </button>
                                    <button class="btn waves-effect waves-light movement-btn" onclick="sendCommand('m p')">
                                        <i class="material-icons">pan_tool</i>
                                        <span>Pick</span>
                                    </button>
                                    <button class="btn waves-effect waves-light movement-btn" onclick="sendCommand('m d')">
                                        <i class="material-icons">get_app</i>
                                        <span>Drop</span>
                                    </button>
                                    <button class="btn waves-effect waves-light movement-btn" onclick="sendCommand('m w')">
                                        <i class="material-icons">waving_hand</i>
                                        <span>Wave</span>
                                    </button>
                                </div>
                            </div>
                        </div>

                        <div class="divider"></div>

                        <div class="center-align">
                            <h5>Position Memory</h5>
                            <div class="collection">
                                <div class="collection-item">
                                    <button class="btn waves-effect waves-light" onclick="sendCommand('m pos 1')">
                                        <i class="material-icons left">save</i>Save Pos 1
                                    </button>
                                    <button class="btn waves-effect waves-light" onclick="sendCommand('m save 1')">
                                        <i class="material-icons left">replay</i>Load Pos 1
                                    </button>
                                </div>
                                <div class="collection-item">
                                    <button class="btn waves-effect waves-light" onclick="sendCommand('m pos 2')">
                                        <i class="material-icons left">save</i>Save Pos 2
                                    </button>
                                    <button class="btn waves-effect waves-light" onclick="sendCommand('m save 2')">
                                        <i class="material-icons left">replay</i>Load Pos 2
                                    </button>
                                </div>
                                <div class="collection-item">
                                    <button class="btn waves-effect waves-light" onclick="sendCommand('m pos 3')">
                                        <i class="material-icons left">save</i>Save Pos 3
                                    </button>
                                    <button class="btn waves-effect waves-light" onclick="sendCommand('m save 3')">
                                        <i class="material-icons left">replay</i>Load Pos 3
                                    </button>
                                </div>
                            </div>
                        </div>

                        <div class="divider"></div>

                        <div class="center-align">
                            <h5>Command Recording</h5>
                            <div class="collection">
                                <div class="collection-item">
                                    <button class="btn waves-effect waves-light" onclick="sendCommand('stream')">
                                        <i class="material-icons left">fiber_manual_record</i>Start Recording
                                    </button>
                                    <button class="btn waves-effect waves-light" onclick="sendCommand('done')">
                                        <i class="material-icons left">stop</i>Stop Recording
                                    </button>
                                </div>
                                <div class="collection-item">
                                    <button class="btn waves-effect waves-light" onclick="sendCommand('play')">
                                        <i class="material-icons left">play_arrow</i>Play Recording
                                    </button>
                                    <button class="btn waves-effect waves-light" onclick="sendCommand('clear')">
                                        <i class="material-icons left">clear</i>Clear Recording
                                    </button>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                <div id="EyeControl">
                        <div class="control-card">
                            <div class="button-group">
                                <button class="btn-large waves-effect waves-light movement-btn" id="colorDetect">
                                    <i class="material-icons">colorize</i>
                                    <span>Color Detection</span>
                                </button>
                                <button class="btn-large waves-effect waves-light movement-btn" id="restart">
                                    <i class="material-icons">refresh</i>
                                    <span>Reset Board</span>
                                </button>
                            </div>
                        </div>

                        <div class="container">
                            <div class="row">
                                <div class="col s12 m6">
                                    <div class="control-card">
                                        <h5><i class="material-icons">tune</i> Camera Settings</h5>
                                        <div class="input-field">
                                            <p class="range-field">
                                                <label>Quality</label>
                                                <input type="range" id="quality" min="10" max="63" value="10">
                                            </p>
                                            <p class="range-field">
                                                <label>Brightness</label>
                                                <input type="range" id="brightness" min="-2" max="2" value="0">
                                            </p>
                                            <p class="range-field">
                                                <label>Contrast</label>
                                                <input type="range" id="contrast" min="-2" max="2" value="0">
                                            </p>
                                        </div>
                                    </div>

                                    <div class="control-card">
                                        <h5><i class="material-icons">palette</i> RGB Color Trackbars</h5>
                                        <div class="input-field">
                                            <div class="row">
                                                <div class="col s6">
                                                    <p class="range-field">
                                                        <label>R min: <span id="RMINdemo"></span></label>
                                                        <input type="range" id="rmin" min="0" max="255" value="0">
                                                    </p>
                                                </div>
                                                <div class="col s6">
                                                    <p class="range-field">
                                                        <label>R max: <span id="RMAXdemo"></span></label>
                                                        <input type="range" id="rmax" min="0" max="255" value="50">
                                                    </p>
                                                </div>
                                            </div>
                                            <div class="row">
                                                <div class="col s6">
                                                    <p class="range-field">
                                                        <label>G min: <span id="GMINdemo"></span></label>
                                                        <input type="range" id="gmin" min="0" max="255" value="0">
                                                    </p>
                                                </div>
                                                <div class="col s6">
                                                    <p class="range-field">
                                                        <label>G max: <span id="GMAXdemo"></span></label>
                                                        <input type="range" id="gmax" min="0" max="255" value="50">
                                                    </p>
                                                </div>
                                            </div>
                                            <div class="row">
                                                <div class="col s6">
                                                    <p class="range-field">
                                                        <label>B min: <span id="BMINdemo"></span></label>
                                                        <input type="range" id="bmin" min="0" max="255" value="0">
                                                    </p>
                                                </div>
                                                <div class="col s6">
                                                    <p class="range-field">
                                                        <label>B max: <span id="BMAXdemo"></span></label>
                                                        <input type="range" id="bmax" min="0" max="255" value="50">
                                                    </p>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div class="control-card">
                                        <h5><i class="material-icons">gps_fixed</i> Color Probe</h5>
                                        <div class="input-field">
                                            <div class="row">
                                                <div class="col s6">
                                                    <p class="range-field">
                                                        <label>X probe: <span id="X_PROBEdemo"></span></label>
                                                        <input type="range" id="x_probe" min="0" max="400" value="200">
                                                    </p>
                                                </div>
                                                <div class="col s6">
                                                    <p class="range-field">
                                                        <label>Y probe: <span id="Y_PROBEdemo"></span></label>
                                                        <input type="range" id="y_probe" min="0" max="296" value="148">
                                                    </p>
                                                </div>
                                            </div>
                                        </div>
                                    </div>

                                    <div class="control-card">
                                        <div class="button-group">
                                            <button class="btn waves-effect waves-light" id="invertButton">
                                                <i class="material-icons">invert_colors</i>
                                                <span>Invert</span>
                                                <span class="badge" id="INVERTdemo"></span>
                                            </button>
                                            <button class="btn waves-effect waves-light" id="contourButton">
                                                <i class="material-icons">gesture</i>
                                                <span>Show Contour</span>
                                                <span class="badge" id="CONTOURdemo"></span>
                                            </button>
                                            <button class="btn waves-effect waves-light" id="trackButton">
                                                <i class="material-icons">track_changes</i>
                                                <span>Tracking</span>
                                                <span class="badge" id="TRACKdemo"></span>
                                            </button>
                                        </div>
                                    </div>

                                    <div class="control-card">
                                        <div class="row">
                                            <div class="col s6">
                                                <h6><i class="material-icons">location_searching</i> XCM: <span id="XCMdemo"></span></h6>
                                            </div>
                                            <div class="col s6">
                                                <h6><i class="material-icons">location_searching</i> YCM: <span id="YCMdemo"></span></h6>
                                            </div>
                                        </div>
                                    </div>
                                </div>

                                <div class="col s12 m6">
                                    <div class="control-card">
                                        <h5><i class="material-icons">filter_center_focus</i> Image Mask</h5>
                                        <canvas id="imageMask" class="responsive-img"></canvas>
                                    </div>
                                    <div class="control-card">
                                        <h5><i class="material-icons">image</i> Image Canvas</h5>
                                        <canvas id="imageCanvas" class="responsive-img"></canvas>
                                    </div>
                                    <div class="control-card">
                                        <canvas id="textCanvas" width="480" height="180" class="responsive-img"></canvas>
                                        <iframe id="ifr" style="display:none"></iframe>
                                        <div id="message"></div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <img id="ShowImage" src="" style="display:none" alt="Captured Image" crossorigin="anonymous">
    <div class="modal"></div>
    <script>
        var colorDetect = document.getElementById('colorDetect');
        var ShowImage = document.getElementById('ShowImage');
        var canvas = document.createElement('canvas'); // Create canvas dynamically
        canvas.id = 'canvas';
        canvas.style.display = 'none'; // Keep canvas hidden
        document.body.appendChild(canvas);
        var context = canvas.getContext("2d");
        var imageMask = document.getElementById("imageMask");
        var imageMaskContext = imageMask.getContext("2d");
        var imageCanvas = document.getElementById("imageCanvas");
        var imageContext = imageCanvas.getContext("2d");
        var txtcanvas = document.getElementById("textCanvas");
        var ctx = txtcanvas.getContext("2d");
        var message = document.getElementById('message');
        var ifr = document.getElementById('ifr');
        var myTimer;
        var restartCount=0;
        const modelPath = 'https://ruisantosdotme.github.io/face-api.js/weights/';
        let currentStream;
        let displaySize = { width:400, height: 296 }
        let faceDetection;

        let b_tracker = false;
        let x_cm = 0;
        let y_cm = 0;

        let b_invert = false;

        let b_contour = false;

        var RMAX=50;
        var RMIN=0;
        var GMAX=50;
        var GMIN=0;
        var BMAX=50;
        var BMIN=0;
        var THRESH_MIN=120;
        var X_PROBE=200;
        var Y_PROBE=196;
        var R=0;
        var G=0;
        var B=0;
        var A=0;

        colorDetect.onclick = function (event) {
        clearInterval(myTimer);
        myTimer = setInterval(function(){error_handle();},5000);
        ShowImage.src=location.origin+'/?colorDetect='+Math.random();
        }

        var Module = {
            onRuntimeInitialized() {
                onOpenCvReady();
            }
        };

        // Add OpenCV.js script tag dynamically
        var script = document.createElement('script');
        script.src = 'opencv.js'; // Make sure opencv.js is in the same directory
        script.onload = function() {
            cv['onRuntimeInitialized']=()=>{
                console.log("OpenCV IS READY!!!");
                onOpenCvReady();
            }
        };
        document.head.appendChild(script);


        function onOpenCvReady() {
            console.log("OpenCV initialized");
            drawReadyText();
            // Initialize other components or start processing here
            colorDetect.style.display = "block";
            if (ShowImage.complete && ShowImage.naturalHeight !== 0) {
                ShowImage.onload(); // Call onload manually if image has already loaded
            }
        }

        var errCount = 0;
        function error_handle() {
            errCount++;
            if (errCount <= 2) {
                message.innerHTML = "Error loading image. <br> Retrying " + errCount + " of 2";
                setTimeout(function(){colorDetect.click();},5000);
            } else {
                message.innerHTML = "Error loading image. <br> Please check ESP32-CAM.";
            }
        }

        ShowImage.onload = function () {
            console.log("Image Loaded");
            errCount = 0;
            clearInterval(myTimer);

            // Set canvas dimensions to match image
            canvas.width = ShowImage.width;
            canvas.height = ShowImage.height;
            imageCanvas.width = ShowImage.width;
            imageCanvas.height = ShowImage.height;
            imageMask.width = ShowImage.width;
            imageMask.height = ShowImage.height;

            context.drawImage(ShowImage, 0, 0, ShowImage.width, ShowImage.height);
            DetectImage();
        };
        restart.onclick = function (event) {
        fetch(location.origin+'/?restart=stop');
        }
        quality.onclick = function (event) {
        fetch(document.location.origin+'/?quality='+this.value+';stop');
        }
        brightness.onclick = function (event) {
        fetch(document.location.origin+'/?brightness='+this.value+';stop');
        }
        contrast.onclick = function (event) {
        fetch(document.location.origin+'/?contrast='+this.value+';stop');
        }
        async function DetectImage() {
        //alert("DETECT IMAGE");
        console.log("DETECT IMAGE");

        /***************opencv********************************/
        /* Marks the creation of the src and its characteristics. rows, cols, etc. */
        let src = cv.imread(ShowImage);
        arows = src.rows;
        acols = src.cols;
        aarea = arows*acols;
        adepth = src.depth();
        atype = src.type();
        achannels = src.channels();
        console.log("rows = " + arows);
        console.log("cols = " + acols);
        console.log("pic area = " + aarea);
        console.log("depth = " + adepth);
        console.log("type = " + atype);
        console.log("channels = " + achannels);

        /******************COLOR DETECT******************************/

        //ANN:6
        var RMAXslider = document.getElementById("rmax");
        var RMAXoutput = document.getElementById("RMAXdemo");
        RMAXoutput.innerHTML = RMAXslider.value;
        RMAXslider.oninput = function(){
        RMAXoutput.innerHTML = this.value;
        RMAX = parseInt(RMAXoutput.innerHTML,10);
        console.log("RMAX=" + RMAX);
        }

        console.log("RMAX=" + RMAX);

        var RMINslider = document.getElementById("rmin");
        var RMINoutput = document.getElementById("RMINdemo");
        RMINoutput.innerHTML = RMINslider.value;
        RMINslider.oninput = function(){
        RMINoutput.innerHTML = this.value;
        RMIN = parseInt(RMINoutput.innerHTML,10);
        console.log("RMIN=" + RMIN);
        }
        console.log("RMIN=" + RMIN);

        var GMAXslider = document.getElementById("gmax");
        var GMAXoutput = document.getElementById("GMAXdemo");
        GMAXoutput.innerHTML = GMAXslider.value;
        GMAXslider.oninput = function(){
        GMAXoutput.innerHTML = this.value;
        GMAX = parseInt(GMAXoutput.innerHTML,10);
        }
        console.log("GMAX=" + GMAX);

        var GMINslider = document.getElementById("gmin");
        var GMINoutput = document.getElementById("GMINdemo");
        GMINoutput.innerHTML = GMINslider.value;
        GMINslider.oninput = function(){
        GMINoutput.innerHTML = this.value;
        GMIN = parseInt(GMINoutput.innerHTML,10);
        }
        console.log("GMIN=" + GMIN);

        var BMAXslider = document.getElementById("bmax");
        var BMAXoutput = document.getElementById("BMAXdemo");
        BMAXoutput.innerHTML = BMAXslider.value;
        BMAXslider.oninput = function(){
        BMAXoutput.innerHTML = this.value;
        BMAX = parseInt(BMAXoutput.innerHTML,10);
        }
        console.log("BMAX=" + BMAX);

        var BMINslider = document.getElementById("bmin");
        var BMINoutput = document.getElementById("BMINdemo");
        BMINoutput.innerHTML = BMINslider.value;
        BMINslider.oninput = function(){
        BMINoutput.innerHTML = this.value;
        BMIN = parseInt(BMINoutput.innerHTML,10);
        }
        console.log("BMIN=" + BMIN);

        var THRESH_MINslider = document.getElementById("thresh_min");
        var THRESH_MINoutput = document.getElementById("THRESH_MINdemo");
        THRESH_MINoutput.innerHTML = THRESH_MINslider.value;
        THRESH_MINslider.oninput = function(){
        THRESH_MINoutput.innerHTML = this.value;
        THRESH_MIN = parseInt(THRESH_MINoutput.innerHTML,10);
        }
        console.log("THRESHOLD MIN=" + THRESH_MIN);

        var X_PROBEslider = document.getElementById("x_probe");
        var X_PROBEoutput = document.getElementById("X_PROBEdemo");
        X_PROBEoutput.innerHTML = X_PROBEslider.value;
        X_PROBEslider.oninput = function(){
        X_PROBEoutput.innerHTML = this.value;
        X_PROBE = parseInt(X_PROBEoutput.innerHTML,10);
        }
        console.log("X_PROBE=" + X_PROBE);

        var Y_PROBEslider = document.getElementById("y_probe");
        var Y_PROBEoutput = document.getElementById("Y_PROBEdemo");
        Y_PROBEoutput.innerHTML = Y_PROBEslider.value;
        Y_PROBEslider.oninput = function(){
        Y_PROBEoutput.innerHTML = this.value;
        Y_PROBE = parseInt(Y_PROBEoutput.innerHTML,10);
        }
        console.log("Y_PROBE=" + Y_PROBE);

        document.getElementById('trackButton').onclick = function(){
        b_tracker = (true && !b_tracker)
        console.log("TRACKER = " + b_tracker );
        var TRACKoutput = document.getElementById("TRACKdemo");
        TRACKoutput.innerHTML = b_tracker;
        //var XCMoutput = document.getElementById("XCMdemo");
        //XCMoutput.innerHTML = x_cm;

        }

        document.getElementById('invertButton').onclick = function(){
        b_invert = (true && !b_invert)
        console.log("TRACKER = " + b_invert );
        var INVERToutput = document.getElementById("INVERTdemo");
        INVERToutput.innerHTML = b_invert;
        }

        document.getElementById('contourButton').onclick = function(){
        b_contour = (true && !b_contour)
        console.log("TRACKER = " + b_contour );
        var CONTOURoutput = document.getElementById("CONTOURdemo");
        CONTOURoutput.innerHTML = b_contour;
        }

        let tracker = 0;

        var TRACKoutput = document.getElementById("TRACKdemo");
        TRACKoutput.innerHTML = b_tracker;
        var XCMoutput = document.getElementById("XCMdemo");
        var YCMoutput = document.getElementById("YCMdemo");

        XCMoutput.innerHTML = 0;
        YCMoutput.innerHTML = 0;

        var INVERToutput = document.getElementById("INVERTdemo");
        INVERToutput.innerHTML = b_invert;

        var CONTOURoutput = document.getElementById("CONTOURdemo");
        CONTOURoutput.innerHTML = b_contour;

        let M00Array = [0,];
        let orig = new cv.Mat();
        let mask = new cv.Mat();
        let mask1 = new cv.Mat();
        let mask2 = new cv.Mat();
        let contours = new cv.MatVector();
        let hierarchy = new cv.Mat();
        let rgbaPlanes = new cv.MatVector();

        let color = new cv.Scalar(0,0,0);

        clear_canvas();

        orig = cv.imread(ShowImage);
        cv.split(orig,rgbaPlanes);  //SPLIT
        let BP = rgbaPlanes.get(2);  // SELECTED COLOR PLANE
        let GP = rgbaPlanes.get(1);
        let RP = rgbaPlanes.get(0);
        cv.merge(rgbaPlanes,orig);

        let row = Y_PROBE //180 //275 //225 //150 //130
        let col = X_PROBE //100 //10 //100 //200 //300
        drawColRowText(acols,arows);

        console.log("ISCONTINUOUS = " + orig.isContinuous());

        R = src.data[row * src.cols * src.channels() + col * src.channels()];
        G = src.data[row * src.cols * src.channels() + col * src.channels() + 1];
        B = src.data[row * src.cols * src.channels() + col * src.channels() + 2];
        A = src.data[row * src.cols * src.channels() + col * src.channels() + 3];
        console.log("RDATA = " + R);
        console.log("GDATA = " + G);
        console.log("BDATA = " + B);
        console.log("ADATA = " + A);

        drawRGB_PROBE_Text();

        /*************draw probe point*********************/
        let point4 = new cv.Point(col,row);
        cv.circle(src,point4,5,[255,255,255,255],2,cv.LINE_AA,0);
        /***********end draw probe point*********************/

        let high = new cv.Mat(src.rows,src.cols,src.type(),[RMAX,GMAX,BMAX,255]);
        let low = new cv.Mat(src.rows,src.cols,src.type(),[RMIN,GMIN,BMIN,0]);

        cv.inRange(src,low,high,mask1);
        //inRange(source image, lower limit, higher limit, destination image)

        cv.threshold(mask1,mask,THRESH_MIN,255,cv.THRESH_BINARY);
        //threshold(source image,destination image,threshold,255,threshold method);

        if(b_invert==true){
            cv.bitwise_not(mask,mask2);
        }
        /********************start contours******************************************/
            if(b_tracker == true){
                try{
                    if(b_invert==false){
                    cv.findContours(mask,contours,hierarchy,cv.RETR_CCOMP,cv.CHAIN_APPROX_SIMPLE);
                    //findContours(source image, array of contours found, hierarchy of contours
                        // if contours are inside other contours, method of contour data retrieval,
                        //algorithm method)
                    }
                    else{
                    cv.findContours(mask2,contours,hierarchy,cv.RETR_CCOMP,cv.CHAIN_APPROX_SIMPLE);
                    }
                    console.log("CONTOUR_SIZE = " + contours.size());

                    //draw contours
                    if(b_contour==true){
                        for(let i = 0; i < contours.size(); i++){
                        cv.drawContours(src,contours,i,[0,0,0,255],2,cv.LINE_8,hierarchy,100)
                        }
                    }

                    /* Marks the beginning of finding the moments of the contours found */

                    let cnt;
                    let Moments;
                    let M00;
                    let M10;


                    for(let k = 0; k < contours.size(); k++){
                        cnt = contours.get(k);
                        Moments = cv.moments(cnt,false);
                        M00Array[k] = Moments.m00;
                        // cnt.delete();
                    }

                    let max_area_arg = MaxAreaArg(M00Array);
                    console.log("MAXAREAARG = "+max_area_arg);

                    //let TestArray = [0,0,0,15,4,15,2];
                    //let TestArray0 = [];
                    //let max_test_area_arg = MaxAreaArg(TestArray0);
                    //console.log("MAXTESTAREAARG = "+max_test_area_arg);

                    let ArgMaxArea = MaxAreaArg(M00Array);
                    if(ArgMaxArea >= 0){
                        cnt = contours.get(MaxAreaArg(M00Array));  //use the contour with biggest MOO
                        //cnt = contours.get(54);
                        Moments = cv.moments(cnt,false);
                        M00 = Moments.m00;
                        M10 = Moments.m10;
                        M01 = Moments.m01;
                        x_cm = M10/M00;    // 75 for circle_9.jpg
                        y_cm = M01/M00;    // 41 for circle_9.jpg

                        XCMoutput.innerHTML = Math.round(x_cm);
                        YCMoutput.innerHTML = Math.round(y_cm);

                        console.log("M00 = "+M00);
                        console.log("XCM = "+Math.round(x_cm));
                        console.log("YCM = "+Math.round(y_cm));

                        //fetch(document.location.origin+'/?xcm='+Math.round(x_cm)+';stop');
                        fetch(document.location.origin+'/?cm='+Math.round(x_cm)+';'+Math.round(y_cm)+';stop');

                        console.log("M00ARRAY = " + M00Array);

                        //**************min area bounding rect********************
                        //let rotatedRect=cv.minAreaRect(cnt);
                        //let vertices = cv.RotatedRect.points(rotatedRect);

                        //for(let j=0;j<4;j++){
                        //    cv.line(src,vertices[j],
                        //        vertices[(j+1)%4],[0,0,255,255],2,cv.LINE_AA,0);
                        //}
                        //***************end min area bounding rect*************************************


                        //***************bounding rect***************************
                        let rect = cv.boundingRect(cnt);
                        let point1 = new cv.Point(rect.x,rect.y);
                        let point2 = new cv.Point(rect.x+rect.width,rect.y+rect.height);

                        cv.rectangle(src,point1,point2,[0,0,255,255],2,cv.LINE_AA,0);
                        //*************end bounding rect***************************


                        //*************draw center point*********************
                        let point3 = new cv.Point(x_cm,y_cm);
                        cv.circle(src,point3,2,[0,0,255,255],2,cv.LINE_AA,0);
                        //***********end draw center point*********************

                    }//end if(ArgMaxArea >= 0)
                    else{
                        if(ArgMaxArea==-1){
                        console.log("ZERO ARRAY LENGTH");
                        }
                        else{              //ArgMaxArea=-2
                        console.log("DUPLICATE MAX ARRAY-ELEMENT");
                        }
                    }

                    cnt.delete();
                    /******************end contours  note cnt line one up*******************************************/
                    drawXCM_YCM_Text();

                }//end try

            catch{
            console.log("ERROR TRACKER NO CONTOUR");
            clear_canvas();
            drawErrorTracking_Text();
            }
        }//end b_tracking if statement

        else{
            XCMoutput.innerHTML = 0;
            YCMoutput.innerHTML = 0;
        }

        if(b_invert==false){
            cv.imshow('imageMask', mask);
        }
        else{
            cv.imshow('imageMask', mask2);
        }
        //cv.imshow('imageMask', R);
        cv.imshow('imageCanvas', src);

        src.delete();
        high.delete();
        low.delete();
        orig.delete();
        mask1.delete();
        mask2.delete();
        mask.delete();
        contours.delete();
        hierarchy.delete();
        RP.delete();

        /********************END COLOR DETECT****************************/

        /***************end opencv******************************/

        setTimeout(function(){colorDetect.click();},500);

        }//end detectimage

        function MaxAreaArg(arr){
            if (arr.length == 0) {
                return -1;
            }

            var max = arr[0];
            var maxIndex = 0;
            var dupIndexCount = 0; //duplicate max elements?

            if(arr[0] >= .90*aarea){
                max = 0;
            }

            for (var i = 1; i < arr.length; i++) {
                if (arr[i] > max && arr[i] < .99*aarea) {
                    maxIndex = i;
                    max = arr[i];
                    dupIndexCount = 0;
                }
                else if(arr[i]==max && arr[i]!=0){
                    dupIndexCount++;
                }
            }

            if(dupIndexCount==0){
                return maxIndex;
            }

            else{
                return -2;
            }
        }//end MaxAreaArg

        function clear_canvas(){
            ctx.clearRect(0,0,txtcanvas.width,txtcanvas.height);
            ctx.rect(0,0,txtcanvas.width,txtcanvas.height);
            ctx.fillStyle="red";
            ctx.fill();
        }

        function drawReadyText(){
            ctx.fillStyle = 'black';
            ctx.font = '20px serif';
            ctx.fillText('OpenCV.JS READY',txtcanvas.width/4,txtcanvas.height/10);
        }

        function drawColRowText(x,y){
            ctx.fillStyle = 'black';
            ctx.font = '20px serif';
            ctx.fillText('ImageCols='+x,0,txtcanvas.height/10);
            ctx.fillText('ImageRows='+y,txtcanvas.width/2,txtcanvas.height/10);
        }

        function drawRGB_PROBE_Text(){
            ctx.fillStyle = 'black';
            ctx.font = '20px serif';
            ctx.fillText('Rp='+R,0,2*txtcanvas.height/10);
            ctx.fillText('Gp='+G,txtcanvas.width/4,2*txtcanvas.height/10);
            ctx.fillText('Bp='+B,txtcanvas.width/2,2*txtcanvas.height/10);
            ctx.fillText('Ap='+A,3*txtcanvas.width/4,2*txtcanvas.height/10);
        }

        function drawXCM_YCM_Text(){
            ctx.fillStyle = 'black';
            ctx.font = '20px serif';
            ctx.fillText('XCM='+Math.round(x_cm),0,3*txtcanvas.height/10);
            ctx.fillText('YCM='+Math.round(y_cm),txtcanvas.width/4,3*txtcanvas.height/10);
        }

        function drawErrorTracking_Text(){
            ctx.fillStyle = 'black';
            ctx.font = '20px serif';
            ctx.fillText('ERROR TRACKING-NO CONTOUR',0,3*txtcanvas.height/10);
        }
    </script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/js/materialize.min.js"></script>
    <script>
        document.addEventListener('DOMContentLoaded', function() {
            var tabs = document.querySelectorAll('.tabs');
            M.Tabs.init(tabs);
        });

        function sendCommand(cmd) {
            fetch('/command?cmd=' + cmd)
                .then(response => response.text())
                .then(data => {
                    console.log(data);
                    M.toast({html: 'Command sent: ' + cmd, classes: 'rounded green'});
                })
                .catch(error => {
                    console.error('Error:', error);
                    M.toast({html: 'Error sending command', classes: 'rounded red'});
                });
        }
    </script>
</body>
</html>
)html";

#endif // UI_INDEX_H