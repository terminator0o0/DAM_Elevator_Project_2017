$('#myCarousel').carousel({
  interval: 3000
}).on('slide.bs.carousel', function () {
  document.getElementById('bg-video').pause();
})