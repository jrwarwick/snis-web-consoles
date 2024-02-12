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
