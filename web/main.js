(function () {
    let rSlider = document.getElementById("red");
    let gSlider = document.getElementById("green");
    let bSlider = document.getElementById("blue");

    let color = {
        red: 0,
        green: 0,
        blue: 0
    };

    let colorHasChanged = false;

    rSlider.oninput = changeHandler;
    gSlider.oninput = changeHandler;
    bSlider.oninput = changeHandler;

    setValues(color);
    
    function updateValues() {
        fetch("/led/get")
            .then(res => res.json())
            .then(out => { 
                console.log(out);
                setValues(out);
            })
            .catch(err => { throw err });
    }

    function setValues(newColor) {
        color.red = newColor.red;
        color.blue = newColor.blue;
        color.green = newColor.green;
        rSlider.value = newColor.red.toString();
        gSlider.value = newColor.green.toString();
        bSlider.value = newColor.blue.toString();
    }
    
    function sendValues() {
        if (colorHasChanged)
        {
            let xhr = new XMLHttpRequest();
            xhr.open('POST', "/led/set", true);
            xhr.setRequestHeader("Content-Type", "application/json");
            let data = JSON.stringify(color);
            xhr.send(data);

            colorHasChanged = false;
        }
    }

    function changeHandler(e) {
        let newValue = e.target.value;
        let name = e.target.id;
        if (parseInt(newValue) !== color[name]) {
            color[name] = parseInt(newValue);
            colorHasChanged = true;
        }
    }
    
    updateValues();

    setInterval(updateValues, 5000);
    setInterval(sendValues, 120);
})();