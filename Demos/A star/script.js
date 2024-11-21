// Initialize the map
const map = L.map('map').setView([0, 0], 13);

// Add OpenStreetMap tiles
L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
  maxZoom: 19,
  attribution: '© OpenStreetMap contributors',
}).addTo(map);

// Add a marker for user location
const userMarker = L.marker([0, 0]).addTo(map).bindPopup('You are here!');

// Locate user on button click
document.getElementById('locate').addEventListener('click', () => {
  if (navigator.geolocation) {
    navigator.geolocation.getCurrentPosition((position) => {
      const lat = position.coords.latitude;
      const lon = position.coords.longitude;

      // Update map and marker position
      map.setView([lat, lon], 15);
      userMarker.setLatLng([lat, lon]).openPopup();
    }, (error) => {
      alert(`Error getting location: ${error.message}`);
    });
  } else {
    alert('Geolocation is not supported by your browser.');
  }
});
