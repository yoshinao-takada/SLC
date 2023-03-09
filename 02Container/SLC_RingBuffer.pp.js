const fs = require('fs');
const process = require('process');
const path = require('path');
const fname_cin = "SLC_RingBuffer.cin";
const fname_cin_header = "SLC_RingBuffer.cin0";
const fname_hin = "SLC_RingBuffer.hin";
const fname_hin_header = "SLC_RingBuffer.hin0";
const fname_c = "SLC_RingBuffer.c";
const fname_h = "SLC/SLC_RingBuffer.h";
const curdir = path.dirname(process.argv[1]);
const incdir = path.join(curdir, "../include");
const typeIDs = ["i32", "u8", "u16", "ptr"];

//--------------------------------------------------------------------------
// Main block
//--------------------------------------------------------------------------
CreateHeaderFile(fname_hin, fname_h);

CreateSourceFile(fname_cin, fname_c);

//--------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------
function ReadAllLines(filepath)
{
    let whole = fs.readFileSync(filepath, 'utf8');
    let textInput = whole.split('\n');
    return textInput;
}

function CreateHeaderFile(hin, h)
{
    let text = [];
    // 1) Generate file header
    const headerText = ReadAllLines(path.join(curdir, fname_hin_header));
    headerText.forEach((e) => { text.push(e); });

    // 2) Generate function signatures
    let regex = /<TypeID>/g;
    let templateText = ReadAllLines(path.join(curdir, hin));
    typeIDs.forEach(function(typeID) {
        templateText.forEach(function(templateLine) {
            text.push(templateLine.replace(regex, typeID));
        });
    });

    // 3) Generate file footer
    const footerText = [
        "#endif"
    ];
    footerText.forEach((e) => { text.push(e); });

    // 4) Save the file
    let whole = "";
    text.forEach(function(textLine) {
        whole = whole.concat(textLine + '\n');
    });
    fs.writeFileSync(path.join(incdir, h), whole, 'utf8');
}

function CreateSourceFile(cin, c)
{
    let text = [];
    // 1) Generate file header
    let headerText = ReadAllLines(path.join(curdir, fname_cin_header));
    headerText.forEach((e) => { text.push(e); });

    // 2) Generate definitions for each number types
    let templateText = ReadAllLines(path.join(curdir, cin));
    const regex = /<TypeID>/g;
    typeIDs.forEach(function(typeID) {
        templateText.forEach(function(templateLine) {
            text.push(templateLine.replace(regex, typeID));
        });
    });

    // 3) Generate file footer
    // do nothing

    // 4) Save the file
    let whole = '';
    text.forEach(function(textLine) {
        whole = whole.concat(textLine + '\n');
    });
    fs.writeFileSync(path.join(curdir, c), whole, 'utf8');
}