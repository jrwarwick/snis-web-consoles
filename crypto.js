// probably need some kind of answer for numbers!
// 1234567890
// -+#$?\/_:.
function rot13(c) {
    if (c) {
	    return c.replace(/([a-m])|([n-z])/ig, function($0,$1,$2) {
		return String.fromCharCode($1 ? $1.charCodeAt(0) + 13 : $2 ? $2.charCodeAt(0) - 13 : 0) || $0;
	    });
    } else {
	    return ""
    }
}

function alt_rot13(c) {
	//32-126
	for (let i = 0; i < c.length; i++) {
		
	}
}

function decrypt_effect(elid) {
	let tgtxtEl=document.getElementById(elid)
	let cryptxt = "";
	if (tgtxtEl.tagName == "TEXTAREA") { //extract this into a get/set?
		cryptxt = tgtxtEl.value;
	} else {
		cryptxt = tgtxtEl.innerText;
	}
	let tgtxt= rot13(cryptxt);
	if (tgtxtEl.tagName == "TEXTAREA") {
		tgtxtEl.value = cryptxt;
	} else {
		tgtxtEl.innerText = cryptxt;
	}
	console.log(cryptxt);
	let done = ""
	let cseq = ['a','Z','3','8','5','u','R','K','0','2','T','s','J','x','L','b','q','7','6','#','h','H','1','v','N','N','X','5','-','9','G','g','+','B','F','s','A','w'];
	for (let ci = 0 ; ci < tgtxt.length  ; ci++) {
		cseq[cseq.length - 1] = tgtxt[ci];
		for (let i = 0 ; i < cseq.length ; i++) { 
			let cde = done + cseq[i] + cryptxt.slice(ci+1); //tgtxt+cseq[i];
			//console.log(cde);
			setTimeout(()=>{
				if (tgtxtEl.tagName == "TEXTAREA") {
					tgtxtEl.value = cde;
				} else {
					tgtxtEl.innerText=cde;
				}
				//todo: a span with brighter color on the most recently decoded letter. "locked in"
			},500*ci+i*(500/cseq.length));
		}
		done += tgtxt[ci];
		console.log(done);
	}
	//TODO:finish up flash-confirm looking thing for the whole line. and a "decryption complete" message/tone/etc.
}

decrypt_effect("YYYY-MM-DD.HH:MI");

function decrypt_effect2(elid) {
	//TODO: rewrite this: have an array of integers that are index of "progress", one element for each letter in text. Randomly apply a random stepsize forward for a random selection of 
	//character positions, until all all are all the way there. kind of looks like parallel threads of execution, kind of
	let cseq = ['a','Z','3','8','5','u','R','K','0','2','T','s','J','x','L','b','q','7','6','#','h','H','1','v','N','N','X','5','-','9','G','g','+','B','F','s','A','w'];
	let tgtxtEl=document.getElementById(elid)
	let cryptxt = "";
	let plaintxt = "";
	if (tgtxtEl.tagName == "TEXTAREA") { //extract this into a get/set?
		plaintxt = cryptxt = tgtxtEl.value;
	} else {
		plaintxt = cryptxt = tgtxtEl.innerText;
	}
	let decryptProgress = [];
	for (let i = 0; i < cryptxt.length; i++) {
		decryptProgress[i] = Math.floor(Math.random() * cseq.length);
	}
	let tgtxt= rot13(cryptxt);
	if (tgtxtEl.tagName == "TEXTAREA") {
		tgtxtEl.value = cryptxt;
	} else {
		tgtxtEl.innerText = cryptxt;
	}
	console.log(cryptxt);
	let iteration = 0;
	let maxIteration = 10000;
	function progression() {
		//"decrypt" just a portion of the message at a time, for effect
		for (let i = 0; i < Math.max(2,Math.floor(cryptxt.length / 12)) ; i++) {
			let charpos = Math.floor(Math.random() * cryptxt.length);
			if (decryptProgress[charpos] ) {
				decryptProgress[charpos] -= 1;
			}
		}
		//console.log(txtInprogress);
		if (!decryptProgress.join().match(/^[0,]+$/) && iteration < maxIteration) {
			setTimeout(()=>{
				let txtInprogress = "" 
				for (let i = 0; i < cryptxt.length; i++) {
					//actually this doesn't make sense, it is uniform character right before "success" txtInprogress += cseq[decryptProgress[i]];
					if (decryptProgress[i]) {
						txtInprogress += cseq[Math.floor(Math.random() * cseq.length)];
					} else {
						txtInprogress += plaintxt[i];
					}
				}
				if (tgtxtEl.tagName == "TEXTAREA") {
					tgtxtEl.value = txtInprogress;
				} else {
					tgtxtEl.innerText=txtInprogress;
				}
				//todo: a span with brighter color on the most recently decoded letter. "locked in"
				if ((iteration % 200)==0) {
					console.log(iteration);
				}
				progression();
			},50+iteration / cryptxt.length + cryptxt.length / 10 / iteration);
			//},100+iteration*(500/cseq.length));
		}
		iteration += 1;
	}
	progression();

	//TODO:finish up flash-confirm looking thing for the whole line. and a "decryption complete" message/tone/etc.
}

decrypt_effect("YYYY-MM-DD.HH:MI");
