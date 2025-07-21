/**
 * Decode base 64 pararm url sent by
 * damnmcode en linea URL
 * @param {*} encodeData 
 * @returns 
 */
const decodeData = (encodeData) => {
    const buff = Buffer.from(encodeData, 'base64');
    const str = buff.toString('utf-8');

    let dataSplit = str.split(':');
    return dataSplit;
};

module.exports = {
    decodeData,
}