let fetchController = new AbortController();

function fetchData() {
    fetch("/data.shtml")
        .then(response => response.text())
        .then(data => {
            const [volt, temp, gpio, led, mode] = data.trim().split("\n");

            const placeholders = {
                volt: "<!--#volt-->",
                temp: "<!--#temp-->",
                gpio: "<!--#gpio-->",
                led: "<!--#led-->",
                mode: "<!--#mode-->"
            };

            document.getElementById("volt").innerText = (volt !== placeholders.volt) ? volt + " V" : "N/A";
            document.getElementById("temp").innerText = (temp !== placeholders.temp) ? temp + " °C" : "N/A";
            document.getElementById("gpio").innerText = (gpio !== placeholders.gpio) ? gpio : "N/A";
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

        document.getElementById("elapsed").innerText = `${formattedElapsedTime}`;
    }, 1000);
}

function fetchTimestamp() {
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
                tmElement.innerText = formattedDate;
                tmElement.setAttribute("data-timestamp", tm);
                updateElapsedTime();
            } else {
                document.getElementById("tm").innerText = "N/A";
            }
        })
        .catch(error => console.error("Error fetching data:", error));
}

document.addEventListener("DOMContentLoaded", fetchTimestamp);

document.addEventListener("DOMContentLoaded", function() {
    const currentYear = new Date().getFullYear();
    const copyrightElement = document.getElementById("copyright");
    copyrightElement.innerHTML = `© ${currentYear} ` + copyrightElement.innerHTML;
});
