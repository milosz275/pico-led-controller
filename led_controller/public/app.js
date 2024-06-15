let fetchController = new AbortController();

function fetchData() {
    fetch("/data.shtml")
        .then(response => response.text())
        .then(data => {
            const [volt, temp, onboardled, led, mode] = data.trim().split("\n");

            const placeholders = {
                volt: "<!--#volt-->",
                temp: "<!--#temp-->",
                onboardled: "<!--#onboardled-->",
                led: "<!--#led-->",
                mode: "<!--#mode-->"
            };

            document.getElementById("volt").innerText = (volt !== placeholders.volt) ? volt + " V" : "N/A";
            document.getElementById("temp").innerText = (temp !== placeholders.temp) ? temp + " °C" : "N/A";
            document.getElementById("onboardled").innerText = (onboardled !== placeholders.onboardled) ? onboardled : "N/A";
            document.getElementById("led").innerText = (led !== placeholders.led) ? led : "N/A";
            document.getElementById("mode").innerText = (mode !== placeholders.mode) ? mode : "N/A";

            const modeSelect = document.getElementById("modeSelect");
            if (mode !== placeholders.mode && modeSelect) {
                modeSelect.value = mode;
            } else {
                modeSelect.value = "rainbow-wheel";
            }
        })
        .catch(error => console.error("Error fetching data:", error));
}

function toggleOnboardLED() {
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
