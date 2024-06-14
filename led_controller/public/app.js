function fetchData() {
    fetch("/data.shtml")
        .then(response => response.text())
        .then(data => {
            const [volt, temp, onboardled, led] = data.trim().split("\n");

            const placeholders = {
                volt: "<!--#volt-->",
                temp: "<!--#temp-->",
                onboardled: "<!--#onboardled-->",
                led: "<!--#led-->"
            };

            document.getElementById("volt").innerText = (volt !== placeholders.volt) ? volt : "N/A";
            document.getElementById("temp").innerText = (temp !== placeholders.temp) ? temp + " °C" : "N/A";
            document.getElementById("onboardled").innerText = (onboardled !== placeholders.onboardled) ? onboardled : "N/A";
            document.getElementById("led").innerText = (led !== placeholders.led) ? led : "N/A";
        })
        .catch(error => console.error("Error fetching data:", error));
}

function toggleOnboardLED() {
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

function fetchWithTimeout(url, options, timeout = 30000) {
    return Promise.race([
        fetch(url, options),
        new Promise((_, reject) =>
            setTimeout(() => reject(new Error("Timeout")), timeout)
        )
    ]);
}
