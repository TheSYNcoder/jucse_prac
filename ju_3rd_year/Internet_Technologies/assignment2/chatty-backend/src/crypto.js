
const crypto = require('crypto');

const { publicKey , privateKey } = crypto.generateKeyPair("rsà", {
    modulusLength : 2048
});

const encryptData = ( data)  => {

    return  crypto.publicEncrypt(
        {
            key: publicKey,
            padding: crypto.constants.RSA_PKCS1_OAEP_PADDING,
            oaepHash: "sha256",
        },
        Buffer.from(data)
    )
}

const decryptData = (data) => {
    return crypto.privateDecrypt(
        {
            key: privateKey,
            padding: crypto.constants.RSA_PKCS1_OAEP_PADDING,
            oaepHash: "sha256",
        },
        data
    ).toString();
}


module.exports={
    publicKey : publicKey,
    privateKey : privateKey,
    encryptData : encryptData,
    decryptData : decryptData
};




