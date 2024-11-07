let fetchController = new AbortController();

function fetchData() {
    fetch("/data.shtml")
        .then(response => response.text())
        .then(data => {
            const [volt, temp, gpio, led, mode, color, brightness] = data.trim().split("\n");

            const placeholders = {
                volt: "<!--#volt-->",
                temp: "<!--#temp-->",
                gpio: "<!--#gpio-->",
                led: "<!--#led-->",
                mode: "<!--#mode-->",
                color: "<!--#color-->",
                brightness: "<!--#bright-->"
            };

            document.getElementById("volt").innerText = (volt !== placeholders.volt) ? volt + " V" : "N/A";
            document.getElementById("temp").innerText = (temp !== placeholders.temp) ? temp + " °C" : "N/A";
            document.getElementById("gpio").innerText = (gpio !== placeholders.gpio) ? gpio : "N/A";
            document.getElementById("led").innerText = (led !== placeholders.led) ? led : "N/A";
            document.getElementById("mode").innerText = (mode !== placeholders.mode) ? mode : "N/A";
            document.getElementById("color").innerText = (color !== placeholders.color) ? color : "N/A";
            document.getElementById("brightness").innerText = (brightness !== placeholders.brightness) ? brightness : "N/A";

            const modeSelect = document.getElementById("modeSelect");
            if (mode !== placeholders.mode && modeSelect) {
                modeSelect.value = mode;
            } else {
                modeSelect.value = "rainbow-wheel";
            }
            const colorSelect = document.getElementById("colorSelect");
            if (color !== placeholders.color && colorSelect) {
                colorSelect.value = color;
            } else {
                colorSelect.value = "blue";
            }
            const rangeSlider = document.getElementById("rangeSlider");
            if (brightness !== placeholders.brightness && rangeSlider) {
                rangeSlider.value = brightness;
            } else {
                rangeSlider.value = "100";
            }
            const numberInput = document.getElementById("numberInput");
            if (brightness !== placeholders.brightness && numberInput) {
                numberInput.value = brightness;
            } else {
                numberInput.value = "100";
            }
        })
        .catch(error => console.error("Error fetching data:", error));
}

function toggleGpio() {
    fetchController.abort();
    fetchController = new AbortController();
    fetch("/onboard_led?toggle")
        .then(response => {
            if (!response.ok) {
                throw new Error("Network response was not ok");
            }
            return response.text();
        })
        .then(data => {
            console.log("Toggle onboard LED:", data);
            fetchData();
        })
        .catch(error => console.error("Error toggling onboard LED:", error));
}

function toggleLEDStrip() {
    fetchController.abort();
    fetchController = new AbortController();
    fetch("/led?toggle")
        .then(response => {
            if (!response.ok) {
                throw new Error("Network response was not ok");
            }
            return response.text();
        })
        .then(data => {
            console.log("Toggle LED strip:", data);
            fetchData();
        })
        .catch(error => console.error("Error toggling LED strip:", error));
}

setInterval(fetchData, 5000);

document.addEventListener("DOMContentLoaded", fetchData);

function changeLEDMood(mood) {
    fetchController.abort();
    fetchController = new AbortController();
    const url = `/mode?${encodeURIComponent(mood)}`;
    fetch(url)
    .then(response => {
        if (response.ok) {
            console.log(`LED mood changed to ${mood}`);
            fetchData();
        } else {
            console.error("Failed to change LED mood");
        }
    })
    .catch(error => console.error("Error:", error));
}

function changeLEDColor(color) {
    fetchController.abort();
    fetchController = new AbortController();
    const url = `/color?${encodeURIComponent(color)}`;
    fetch(url)
    .then(response => {
        if (response.ok) {
            console.log(`LED color changed to ${color}`);
            fetchData();
        } else {
            console.error("Failed to change LED color");
        }
    })
    .catch(error => console.error("Error:", error));
}

function updateElapsedTime() {
    const tmElement = document.getElementById("tm");
    const timestamp = tmElement.getAttribute("data-timestamp");
    if (!timestamp) return;

    const timestampDate = new Date(timestamp).getTime();

    setInterval(() => {
        const now = Date.now();
        let elapsed = now - timestampDate;

        const hours = Math.floor(elapsed / (1000 * 60 * 60));
        elapsed -= hours * (1000 * 60 * 60);
        const minutes = Math.floor(elapsed / (1000 * 60));
        elapsed -= minutes * (1000 * 60);
        const seconds = Math.floor(elapsed / 1000);

        const formattedElapsedTime = [
            hours.toString().padStart(2, "0"),
            minutes.toString().padStart(2, "0"),
            seconds.toString().padStart(2, "0")
        ].join(":");

        if (formattedElapsedTime.includes("NaN")) {
            document.getElementById("elapsed").innerText = "Couldn't calculate";
        } else {
            document.getElementById("elapsed").innerText = `${formattedElapsedTime}`;
        }
    }, 1000);
}

function fetchTimestamp(retryCount = 3) {
    fetch("/timestamp.shtml")
        .then(response => response.text())
        .then(data => {
            const [tm] = data.trim().split("\n");

            const placeholders = {
                tm: "<!--#tm-->"
            };

            if (tm !== placeholders.tm) {
                const date = new Date(tm);
                const formattedDate = [
                    date.getDate().toString().padStart(2, "0"),
                    (date.getMonth() + 1).toString().padStart(2, "0"),
                    date.getFullYear().toString().slice(-2)
                ].join("-") + " " +
                [
                    date.getHours().toString().padStart(2, "0"),
                    date.getMinutes().toString().padStart(2, "0"),
                    date.getSeconds().toString().padStart(2, "0")
                ].join(":");

                const tmElement = document.getElementById("tm");

                if (formattedDate.includes("NaN")) {
                    tmElement.innerText = "Couldn't load";
                } else {
                    tmElement.innerText = formattedDate;
                    tmElement.setAttribute("data-timestamp", tm);
                    updateElapsedTime();
                }
            } else {
                document.getElementById("tm").innerText = "N/A";
            }
        })
        .catch(error => {
            console.error("Error fetching data:", error);
            if (retryCount > 0) {
                console.log(`Retrying... Attempts left: ${retryCount - 1}`);
                setTimeout(() => fetchTimestamp(retryCount - 1), 1000);
            }
        });
}

document.addEventListener("DOMContentLoaded", fetchTimestamp);

let estimatedTotalPowerConsumption = 0;

function updateEstimatedPowerConsumption() {
    const ledNum = 120;
    const ledPower = 0.06; // 60 mA
    const brightness = document.getElementById("brightness").innerText;
    document.getElementById("consumption").innerText = (ledNum * ledPower * brightness / 100).toFixed(2) + " W";
    
    estimatedTotalPowerConsumption += ledNum * ledPower * brightness / 100;
    document.getElementById("totalConsumption").innerText = (estimatedTotalPowerConsumption / 1000).toFixed(2) + " kWh";
}

setInterval(updateEstimatedPowerConsumption, 1000);

document.addEventListener("DOMContentLoaded", function() {
    const currentYear = new Date().getFullYear();
    const copyrightElement = document.getElementById("copyright");
    copyrightElement.innerHTML = `© ${currentYear} ` + copyrightElement.innerHTML;
});

document.addEventListener("DOMContentLoaded", function() {
    const rangeSlider = document.getElementById("rangeSlider");
    const numberInput = document.getElementById("numberInput");

    function syncInputs(source, target) {
        target.value = source.value;
        debouncedChangeLEDBrightness(source.value);
    }

    rangeSlider.addEventListener("input", function() {
        syncInputs(rangeSlider, numberInput);
    });

    numberInput.addEventListener("input", function() {
        syncInputs(numberInput, rangeSlider);
    });
});

let debounceTimer;

function debounce(func, delay) {
    return function(args) {
        clearTimeout(debounceTimer);
        debounceTimer = setTimeout(() => func(args), delay);
    };
}

function changeLEDBrightness(brightness) {
    fetchController.abort();
    fetchController = new AbortController();
    const url = `/brightness?${encodeURIComponent(brightness)}`;
    fetch(url, { signal: fetchController.signal })
    .then(response => {
        if (response.ok) {
            console.log(`LED brightness changed to: ${brightness}`);
            fetchData();
        } else {
            console.error("Failed to change LED brightness");
        }
    })
    .catch(error => console.error("Error:", error));
}

function loadDarkMode() {
    let darkMode = localStorage.getItem("dark");
    if (darkMode === null) {
        darkMode = window.matchMedia("(prefers-color-scheme: dark)").matches;
    } else {
        darkMode = JSON.parse(darkMode);
    }
    document.documentElement.classList.toggle("dark", darkMode);
}

document.addEventListener("DOMContentLoaded", loadDarkMode);

function toggleDarkMode() {
    document.documentElement.classList.toggle("dark");
    let darkMode = document.documentElement.classList.contains("dark");
    localStorage.setItem("dark", JSON.stringify(darkMode));
}

function refreshPage() {
    location.reload();
}

function clearDarkmodePreference() {
    localStorage.removeItem("dark");
    refreshPage();
}

const debouncedChangeLEDBrightness = debounce(changeLEDBrightness, 500);
