// CONTENT_BEGIN

// console.log("### abcdefg 1");
// console.log(document.getElementById('sm'));
// console.log(document.getElementById('sm').querySelector("a").innerText);

if (document.getElementById('sm').querySelector("a").innerText == "{sb}") {
  document.getElementById('sm').innerHTML = "";
}

function c(l) {
  var re = /^(.+)<span/;
  var matches = l.innerHTML.match(re);
  document.getElementById('s').value = matches[1];
  document.getElementById('p').focus();
}

// open event mask
function oem() {
  document.body.style.pointerEvents = 'none';
  document.getElementById('em').style.display = 'flex';
}

// close event mask
function cem() {
  document.body.style.pointerEvents = 'all';
  document.getElementById('em').style.display = 'none';
}


// CONTENT_END
