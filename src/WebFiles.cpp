namespace WebFiles 
{
    const char* slider_picker_html =
        "<!doctype html>\n"
        "<html>\n"
        "    <head>\n"
        "        <title>Control</title>\n"
        "        <meta charset=\"UTF-8\">\n"
        "        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
        "        <link rel=\"stylesheet\" type=\"text/css\" href=\"slider.css\">\n"
        "    </head>\n"
        "    <body>\n"
        "        <h1 style=\"font: 1em sans-serif; font-size: xx-large; text-align: center;\">Color</p>\n"
        "        <div>\n"
        "            <input type=\"range\" min=\"0\" max=\"255\" value=\"0\" id=\"red\" name=\"red\" class=\"slider red\">\n"
        "        </div>\n"
        "        <div>\n"
        "            <input type=\"range\" min=\"0\" max=\"255\" value=\"0\" id=\"green\" name=\"green\" class=\"slider green\">\n"
        "        </div>\n"
        "        <div>\n"
        "            <input type=\"range\" min=\"0\" max=\"255\" value=\"0\" id=\"blue\" name=\"blue\" class=\"slider blue\">\n"
        "        </div>\n"
        "        <script src=\"main.js\"></script>\n"
        "    </body>\n"
        "</html>"
        "";

    const char* slider_css =
        ".slidecontainer {\n"
        "    width: 100%;\n"
        "}\n"
        ".slider {\n"
        "    -webkit-appearance: none;\n"
        "    width: 100%;\n"
        "    height: 25px;\n"
        "    background: #d3d3d3;\n"
        "    outline: none;\n"
        "    opacity: 0.7;\n"
        "    -webkit-transition: .2s;\n"
        "    transition: opacity .2s;\n"
        "}\n"
        ".slider:hover {\n"
        "    opacity: 1;\n"
        "}\n"
        ".slider::-webkit-slider-thumb {\n"
        "    -webkit-appearance: none;\n"
        "    appearance: none;\n"
        "    width: 25px;\n"
        "    height: 25px;\n"
        "    background: #583c3c;\n"
        "    cursor: pointer;\n"
        "}\n"
        ".slider::-moz-range-thumb {\n"
        "    width: 25px;\n"
        "    height: 25px;\n"
        "    background: #583c3c;\n"
        "    cursor: pointer;\n"
        "}\n"
        ".slider.red::-moz-range-thumb {\n"
        "    background-color: #ff0000;\n"
        "}\n"
        ".slider.red::-webkit-slider-thumb {\n"
        "    background-color: #ff0000;\n"
        "}\n"
        ".slider.green::-moz-range-thumb {\n"
        "    background-color: #00ff00;\n"
        "}\n"
        ".slider.green::-webkit-slider-thumb {\n"
        "    background-color: #00ff00;\n"
        "}\n"
        ".slider.blue::-moz-range-thumb {\n"
        "    background-color: #0000ff;\n"
        "}\n"
        ".slider.blue::-webkit-slider-thumb {\n"
        "    background-color: #0000ff;\n"
        "}"
        "";

    const char* main_js =
        "(function () {\n"
        "    let rSlider = document.getElementById(\"red\");\n"
        "    let gSlider = document.getElementById(\"green\");\n"
        "    let bSlider = document.getElementById(\"blue\");\n"
        "\n"
        "    let color = {\n"
        "        red: 0,\n"
        "        green: 0,\n"
        "        blue: 0\n"
        "    };\n"
        "\n"
        "    let colorHasChanged = false;\n"
        "\n"
        "    rSlider.oninput = changeHandler;\n"
        "    gSlider.oninput = changeHandler;\n"
        "    bSlider.oninput = changeHandler;\n"
        "\n"
        "    setValues(color);\n"
        "    \n"
        "    function updateValues() {\n"
        "        fetch(\"/led/get\")\n"
        "            .then(res => res.json())\n"
        "            .then(out => { \n"
        "                console.log(out);\n"
        "                setValues(out);\n"
        "            })\n"
        "            .catch(err => { throw err });\n"
        "    }\n"
        "\n"
        "    function setValues(newColor) {\n"
        "        color.red = newColor.red;\n"
        "        color.blue = newColor.blue;\n"
        "        color.green = newColor.green;\n"
        "        rSlider.value = newColor.red.toString();\n"
        "        gSlider.value = newColor.green.toString();\n"
        "        bSlider.value = newColor.blue.toString();\n"
        "    }\n"
        "    \n"
        "    function sendValues() {\n"
        "        if (colorHasChanged)\n"
        "        {\n"
        "            let xhr = new XMLHttpRequest();\n"
        "            xhr.open('POST', \"/led/set\", true);\n"
        "            xhr.setRequestHeader(\"Content-Type\", \"application/json\");\n"
        "            let data = JSON.stringify(color);\n"
        "            xhr.send(data);\n"
        "\n"
        "            colorHasChanged = false;\n"
        "        }\n"
        "    }\n"
        "\n"
        "    function changeHandler(e) {\n"
        "        let newValue = e.target.value;\n"
        "        let name = e.target.id;\n"
        "        if (parseInt(newValue) !== color[name]) {\n"
        "            color[name] = parseInt(newValue);\n"
        "            colorHasChanged = true;\n"
        "        }\n"
        "    }\n"
        "    \n"
        "    updateValues();\n"
        "\n"
        "    setInterval(updateValues, 5000);\n"
        "    setInterval(sendValues, 120);\n"
        "})();"
        "";

};