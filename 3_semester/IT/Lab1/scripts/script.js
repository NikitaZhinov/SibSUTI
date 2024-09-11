function getSounds() {
    let fs = require('fs');
    let files = fs.readdirSunc('memes');
    for (let i = 0; i < files.length; i++) {
        console.log(files[i]);
    }
}
getSounds();

function stopAll() {
    let memes =document.getElementsByClassName("Meme");
    for (let i = 0; i < memes.length; i++) {
        memes[i].pause();
    }
}

document.getElementById('memeButton-aaaaaaa-zhenshchina').onclick = function() {
    stopAll();
    document.getElementById('memeAudio-aaaaaaa-zhenshchina').play();
};

document.getElementById('memeButton-aguliatsiia').onclick = function() {
    stopAll();
    document.getElementById('memeAudio-aguliatsiia').play();
};

document.getElementById('memeButton-among').onclick = function() {
    stopAll();
    document.getElementById('memeAudio-among').play();
};
