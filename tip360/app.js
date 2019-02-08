

const url = 'data';

function update() {
    fetch(url).then(function(response) {
      return response.json();
    }).then(function(data) {
      console.log(data);
      const meter = document.getElementById('soundlevel');
      meter.value = data['sensor1'];
    }).catch(function() {
      console.log("Booo");
    });
}


setInterval(update, 500);

