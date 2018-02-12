// CONTENT_BEGIN

// get textarea
function gta() {
  return document.getElementById('mv')
}

// monitor pause flag
mp = 0;

// pause / play
function pp(o) {
  mp = mp ? 0: 1;
  if (mp) {
    o.textContent = "▶";
  } else {
    o.textContent = "⏸";
    rr();
  }
}

// log clean
function cl() {
  gta().textContent = ""
}

// receive request
function rr() {
  if (mp) {return;}
  // console.log( 'recv_req()');
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function() {
    switch (xhr.readyState) {
      case 0:
        // initial state
        // console.log( 'uninitialized!' );
        break;
      case 1:
        // Data transmission in progress
        // console.log( 'loading...' );
        break;
      case 2:
        // Pending response
        // console.log( 'loaded.' );
        break;
      case 3:
        // Receiving data
        // console.log( 'interactive... '+xhr.responseText.length+' bytes.' );
        break;
      case 4:
        // Data reception complete
        if( xhr.status == 200 || xhr.status == 304 ) {
          var d = xhr.responseText;
          if (d.length != 0) {
            // console.log('COMPLETE! :' + data);
            var t = gta();
            t.textContent += d;
            t.scrollTop = t.scrollHeight;
            rrd(0.5 * 1000);
          } else {
            rrd(1.0 * 1000);
          }
        } else {
          console.log( 'Failed. HttpStatus: '+xhr.statusText );
          rrd(1.0 * 1000);
        }
        break;
    }
  };

  xhr.ontimeout = function(ev) {
    rrd(3.0 * 1000);
  }

  xhr.open("POST", "/smi", false);
  xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
  xhr.send("M=R");
};

// sleep
const sp = msec => new Promise(resolve => setTimeout(resolve, msec));

// delay receive request
async function rrd(st) {
  await sp(st);
  rr();
}

// send
function sd() {
  console.log("send() - " + document.getElementById("mi").value);
  var xhr = new XMLHttpRequest();
  xhr.open("POST", "/smi", false);
  xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
  xhr.send("M=S&D=" + escape(document.getElementById("mi").value));
}

// start receive request
rr();

// CONTENT_END